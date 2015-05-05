//A* search method
#include "PathPlan.h"
#include <iostream>
#include <exception>


using namespace Agentspace;

void PathPlan::ErrorState(Coordinate& start,Grid& KnownWorld)
{
	std::cout<<"error"<<std::endl;

	KnownWorld.updateSize(Grid::right);
	KnownWorld.updateSize(Grid::bottom);
	KnownWorld.updateSize(Grid::top);
	KnownWorld.updateSize(Grid::left);

	start=Coordinate(start.getRow()+1, start.getColumn()+1);
	Leaves.push_back(new Node(start));
	KnownWorld.clearGridViewed();
	KnownWorld[start].setViewed(true);


}

vector<Node::Direction> PathPlan::findPath(Coordinate& start, vector<Coordinate> goals,Grid& KnownWorld)
{
	std::cout<<"RUNNING"<<std::endl;

    /**for now lets just look at a single goal at a time
    */
    Coordinate goal= goals.back();
    /**/

//std::cout<<start<<std::endl;
		//std::cout<<goal<<std::endl;
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

			if(!(*searchItor)->getHeuristic()) // if node heuristic not known, find
				(*searchItor)->setHeuristic(goal);

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
		//std::cout<<"best"<<(*BestItor)->getState()<<" "<<(*BestItor)->getHeuristic()<<" "<<Leaves.size()<<std::endl;
		NodePoint=(*BestItor);
		Leaves.erase(BestItor); //pop cosen of the choice list

		goalPoint=explore(KnownWorld, NodePoint, goal); //explore node for children
		if(goalPoint!=NULL)//found goal
		{
			break;
		}
		if(!Leaves.size())//nothing in list, all paths explored without result
		{
			ErrorState(start, KnownWorld);
		}

	}



	//unravel, so we can go from current direction, to goal
	vector<Node::Direction> actionList; //list of directions
	while(goalPoint!=NULL) //directionlist from goal to root, take and put in action list
	{
		actionList.push_back(goalPoint->getAction());

		goalPoint=goalPoint->getParent();

	}
	return actionList;





}


vector<Coordinate> MidWayPlacemtn(int relayCount,Coordinate Base, Coordinate Client)
{
    vector<Coordinate> relayPositions;
    relayPositions.push_back(Base);
    relayPositions.push_back(Client);
    cout<<relayCount<<" "<<relayPositions.size();
    while(relayCount+2>relayPositions.size())
    {

        vector<Coordinate> templist= relayPositions;
        for(int i = 1; i< relayPositions.size(); i++)
        {
            //cout<<"from "<<relayPositions[i-1] <<" and "<< relayPositions[i]<<endl;
            int rowMidPoint    = (relayPositions[i-1].getRow()+relayPositions[i].getRow())/2;
            int columnMidPoint = (relayPositions[i-1].getColumn()+relayPositions[i].getColumn())/2;
            templist.insert(templist.begin()+i, Coordinate(rowMidPoint, columnMidPoint));
            //cout<<Coordinate(rowMidPoint, columnMidPoint)<<" just added";
        }
        cout<<endl;
        relayPositions= templist;
    }

    relayPositions.pop_back();
    relayPositions.erase(relayPositions.begin()); //remove the base and clinet from the list

return relayPositions;

}


 vector<Coordinate> PathPlan::positionRelays(int method, int relayCount, Coordinate Base, Coordinate Client)
 {

        cout<<"start finding positons"<<endl;

    if (method ==2)
         return MidWayPlacemtn(relayCount, Base,  Client);


    vector<Coordinate> fail;
    return fail;
 }



Node* PathPlan::explore(Grid& grid, Node* toExplore, Coordinate& goal)
{

	Coordinate state = toExplore->getState();
	if(grid[state].hasContent(ContentType::Goal))
	{
		goal=state;
		return toExplore;
	}


	/*bool aboveOK=false;
    bool rightOK=false;
    bool belowOK =false;
    bool leftOK=false;*/

	try{
		Coordinate above= Coordinate(state.getRow()-1,state.getColumn());
		if (!(grid[above].hasContent(ContentType::Object)) && !grid[above].getViewed())
		{

			Leaves.push_back(new Node(toExplore, above, Node::Up));
			grid[above].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}
	try{
		Coordinate right= Coordinate(state.getRow(),state.getColumn()+1);
		if (!(grid[right].hasContent(ContentType::Object)) && !grid[right].getViewed())
		{

			Leaves.push_back(new Node(toExplore, right, Node::Right));
			grid[right].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}
	try{
		Coordinate below= Coordinate(state.getRow()+1,state.getColumn());
		if ( !(grid[below].hasContent(ContentType::Object)) &&!grid[below].getViewed())
		{

			Leaves.push_back(new Node(toExplore, below, Node::Down));
			grid[below].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}
	try{
		Coordinate left= Coordinate(state.getRow(),state.getColumn()-1);
		if ( !(grid[left].hasContent(ContentType::Object))&&!grid[left].getViewed())
		{

			Leaves.push_back(new Node(toExplore, left, Node::Left));
			grid[left].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}


	if(toExplore->getChildren()==0) //dead end
			//toExplore->deadEnd(grid,&Leaves);


	return NULL;
}



