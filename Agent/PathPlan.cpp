//A* search method
#include "PathPlan.h"
#include <iostream>
#include <exception>
#include <math.h>


using namespace Agentspace;



vector<Node::Direction> PathPlan::findPath(Coordinate& start, vector<Coordinate> goals,Grid& KnownWorld)
{
	//std::cout<<"RUNNING"<<std::endl;


list<Node*>::iterator delIter = Leaves.begin();
	while(delIter!= Leaves.end())
    {
        delete *delIter;
        delIter++;
    }
Leaves.clear();

/*
std::cout<<"s"<<start<<std::endl;
		for(int i=0; i<goals.size(); i++)
        {
           std::cout<<"g"<<goals[i]<<std::endl;
        }
*/
KnownWorld.clearGridViewed();

	Node* NodePoint =NULL;
	Node* goalPoint=NULL;
	Leaves.push_back(new Node(start));
	while(1)//loop till broken
	{


		//std::cout<<"loop"<<std::endl;
		list<Node*>::iterator searchItor, BestItor;
		unsigned BestManhattanDistance_plusLevel=-1; //initial worst case, closes to infinity possible

		//find best node in list
		for(searchItor = Leaves.begin(); searchItor!= Leaves.end(); searchItor++)
		{

			(*searchItor)->findHeuristic(goals);

			//if its less its better, even if it does have unknonws
			if((*searchItor)->getHeuristic()<BestManhattanDistance_plusLevel)
			{
				BestItor=searchItor;
				BestManhattanDistance_plusLevel=(*searchItor)->getHeuristic();
			}
			//else if((*searchItor)->getHeuristic()==BestManhattanDistance_plusLevel && KnownWorld[Coordinate((*searchItor)->getState().getRow(), (*searchItor)->getState().getColumn())].hasContent(ContentType::Unknown))
			//{
			//	BestItor=searchItor;
			//	BestManhattanDistance_plusLevel=(*searchItor)->getHeuristic();
			//}


		}
		//std::cout<<"best"<<(*BestItor)->getState()<<" H:"<<(*BestItor)->getHeuristic()<<" Lvl:"<<(*BestItor)->getLevel()<<" Leaves:"<<Leaves.size()<<std::endl;
		NodePoint=(*BestItor);
		Leaves.erase(BestItor); //pop cosen of the choice list

		goalPoint=explore(KnownWorld, NodePoint); //explore node for children
		if(goalPoint!=NULL)//found goal
		{
			break;
		}
		if(!Leaves.size())//nothing in list, all paths explored without result
		{
			throw string("Error, Path finder out of leaves");
		}

	}



	//unravel, so we can go from current direction, to goal
	vector<Node::Direction> actionList; //list of directions
	while(goalPoint!=NULL) //directionlist from goal to root, take and put in action list
	{
		actionList.push_back(goalPoint->getAction());

		//Node::printDirection(goalPoint->getAction());
		//cout<<goalPoint->getState()<<endl;;
		Node*temp = goalPoint;
		goalPoint=goalPoint->getParent();
        delete temp;
	}



	return actionList;





}

Node* PathPlan::AddNode(Coordinate toAdd, Grid& grid, Node* toExplore, Node::Direction dir, bool standard_explore)
{

    if(standard_explore && grid[toAdd].hasContent(ContentType::Goal))
    {
//        cout<<"Goal found"<<endl;
        if(toExplore->getParent()!=NULL)
        {
            return new Node(toExplore, toAdd, dir);
        }
        //else{                cout<<"only root"<<endl;}
    }

   if (!(grid[toAdd].hasContent(ContentType::Object)) && !grid[toAdd].getViewed())
    {
        Leaves.push_back(new Node(toExplore, toAdd, dir));
        grid[toAdd].setViewed(true);
        toExplore->Inc_children();
       // cout<<" -"<<toAdd<<endl;
    }

   return NULL;
}


Node* PathPlan::explore(Grid& grid, Node* toExplore, bool standard_explore)
{
    //cout<<"exploring"<<endl;
	Coordinate state = toExplore->getState();
	  // cout<<state<<endl;

	if(!standard_explore && !grid[state].hasContent(ContentType::Unknown) && !(grid[state].hasContent(ContentType::Wall)) )
    {
        return toExplore;
    }
   // else cout<<state;


    Node* temp;

    int DirectionCount=0;
    Node::Direction  directionToAdd[] ={Node::UpLeft, Node::Up, Node::UpRight, Node::Left, Node::Right,  Node::DownLeft, Node::Down,  Node::DownRight};

    Coordinate coordToTest;
    for(int i=-1; i<2; i++)
    {
         for(int j=-1; j<2; j++)
        {
            try
            {
                if(!(i==0 && j==0))
                {
                    coordToTest= Coordinate(state.getRow()+i, state.getColumn()+j);
                    temp=AddNode(coordToTest, grid,toExplore, directionToAdd[DirectionCount], standard_explore);
                    if(temp != NULL)
                    {
                        return temp;
                    }
                }
                else{DirectionCount--;}
            }
            catch(std::out_of_range){}
            DirectionCount++;

        }
    }


	if(toExplore->getChildren()==0)
    {
        toExplore->deadEnd(grid,Leaves);
    }

	return NULL;
}

bool PathPlan::Explore_Unkown(Coordinate& start, Grid& KnownWorld)
{
 KnownWorld.clearGridViewed();
Leaves.clear();
	Leaves.push_back(new Node(start));
	Node* toExplore;
	while(1)//loop till broken
	{
        toExplore= Leaves.back();
        Leaves.pop_back();
	    if( explore(KnownWorld, toExplore, false) != NULL)
         {
             return true;
         }
        if(Leaves.size()==0)
        {
            return false;
        }
	}
}

