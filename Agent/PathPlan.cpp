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

vector<Node::Direction> PathPlan::findPath(Coordinate& start, Coordinate& goal,Grid& KnownWorld)
{
	std::cout<<"RUNNING"<<std::endl;


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
	while(goalPoint!=NULL) //directionlist from child to root, take and put in action list
	{
		actionList.push_back(goalPoint->getAction());

		goalPoint=goalPoint->getParent();

	}
	return actionList;





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
		if (!(grid[above].hasContent(ContentType::Wall)) && !grid[above].getViewed())
		{

			Leaves.push_back(new Node(toExplore, above, Node::Up));
			grid[above].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}
	try{
		Coordinate right= Coordinate(state.getRow(),state.getColumn()+1);
		if (!(grid[right].hasContent(ContentType::Wall)) && !grid[right].getViewed())
		{

			Leaves.push_back(new Node(toExplore, right, Node::Right));
			grid[right].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}
	try{
		Coordinate below= Coordinate(state.getRow()+1,state.getColumn());
		if ( !(grid[below].hasContent(ContentType::Wall)) &&!grid[below].getViewed())
		{

			Leaves.push_back(new Node(toExplore, below, Node::Down));
			grid[below].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}
	try{
		Coordinate left= Coordinate(state.getRow(),state.getColumn()-1);
		if ( !(grid[left].hasContent(ContentType::Wall))&&!grid[left].getViewed())
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



