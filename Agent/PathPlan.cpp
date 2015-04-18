//A* search method
#include "PathPlan.h"
#include <iostream>
#include <exception>


using namespace Agentspace;

vector<Node::Direction> PathPlan::findPath(Coordinate start, Coordinate goal,Grid KnownWorld)
{
    std::cout<<"RUNNING"<<std::endl;
    Node* NodePoint =NULL;
    Leaves.push_back(new Node(start));

     while(1)//loop till broken
     {
    //std::cout<<"loop"<<std::endl;
        list<Node*>::iterator searchItor, BestItor;
        unsigned BestManhattanDistance_plusLevel=-1; //initial worst case, closes to infinity possible
		Coordinate BestCoord;
		//find best node in list
        for(searchItor = Leaves.begin(); searchItor!= Leaves.end(); searchItor++)
        {

            if(!(*searchItor)->getHeuristic()) // if node heuristic not known, find
                (*searchItor)->setHeuristic(goal);

            //if its less its better, even if it does have unknonws
            if((*searchItor)->getHeuristic()<BestManhattanDistance_plusLevel)
                {
                    BestItor=searchItor;
                    BestCoord =Coordinate((*BestItor)->getState().getRow(), (*BestItor)->getState().getColumn());
                    BestManhattanDistance_plusLevel=(*searchItor)->getHeuristic();
                }
            else if((*searchItor)->getHeuristic()==BestManhattanDistance_plusLevel && KnownWorld[BestCoord].hasContent(ContentType::Unknown))       //if same but that one had unkonws
                {
                    BestItor=searchItor;
                    BestManhattanDistance_plusLevel=(*searchItor)->getHeuristic();
                }


        }
        std::cout<<"best"<<(*BestItor)->getState().getRow()<<" "<< (*BestItor)->getState().getColumn()<<" "<<(*BestItor)->getHeuristic()<<" "<<Leaves.size()<<std::endl;
        NodePoint=(*BestItor);
        Leaves.erase(BestItor); //pop cosen of the choice list

        NodePoint=explore(KnownWorld, NodePoint); //explore node for children
        if(NodePoint!=NULL)//found goal
           break;
         if(!Leaves.size())//nothing in list, all paths explored without result
		 {

		     throw(std::exception());
		 }

     }

    //unravel, so we can go from current direction, to goal
     vector<Node::Direction> actionList; //list of directions
		while(NodePoint!=NULL) //directionlist from child to root, take and put in action list
		{
			actionList.push_back(NodePoint->getAction());
			//cout<<path[temp->getLevel()].getColumn()<<','<<path[temp->getLevel()].getRow()<<" "<<temp->getLevel()<<endl;
			NodePoint=NodePoint->getParent();

		}
		return actionList;





}


Node* PathPlan::explore(Grid& grid, Node* toExplore)
 {

     Coordinate state = toExplore->getState();
    if(grid[state].hasContent(ContentType::Goal))
    {
      return toExplore;
    }

    /*bool aboveOK=false;
    bool rightOK=false;
    bool belowOK =false;
    bool leftOK=false;*/
    Coordinate above= Coordinate(state.getRow()-1,state.getColumn());
    Coordinate right= Coordinate(state.getRow(),state.getColumn()+1);
    Coordinate below= Coordinate(state.getRow()+1,state.getColumn());
    Coordinate left= Coordinate(state.getRow(),state.getColumn()-1);

    try{
        if (!(grid[above].hasContent(ContentType::Wall)) && !grid[above].getViewed())
           {

            Leaves.push_back(new Node(toExplore, above, Node::Up));
            grid[above].setViewed(true);
			toExplore->addChild();
           }
        }
    catch(std::out_of_range){}
    try{
        if (!(grid[right].hasContent(ContentType::Wall)) && !grid[right].getViewed())
            {

             Leaves.push_back(new Node(toExplore, right, Node::Right));
            grid[right].setViewed(true);
				toExplore->addChild();
            }
          }
    catch(std::out_of_range){}
 try{
     if ( !(grid[below].hasContent(ContentType::Wall)) &&!grid[below].getViewed())
      {

    Leaves.push_back(new Node(toExplore, below, Node::Down));
           grid[below].setViewed(true);
	toExplore->addChild();
      }
     }
    catch(std::out_of_range){}
     try{
         if ( !(grid[left].hasContent(ContentType::Wall))&&!grid[left].getViewed())
           {

            Leaves.push_back(new Node(toExplore, left, Node::Left));
            grid[left].setViewed(true);
				toExplore->addChild();
           }
         }
    catch(std::out_of_range){}


	if(toExplore->getChildren()==0) //dead end
		//toExplore->deadEnd(grid,&Leaves);


    return NULL;
 }



