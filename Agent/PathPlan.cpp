//A* search method
#include "PathPlan.h"
#include <iostream>
#include <exception>
#include <math.h>


using namespace Agentspace;



vector<Node::Direction> PathPlan::findPath(Coordinate& start, vector<Coordinate> goals,Grid& KnownWorld)
{
	//std::cout<<"RUNNING"<<std::endl;

    /**for now lets just look at a single goal at a time
    */
    Coordinate goal= goals.back();
    /**/

//std::cout<<start<<std::endl;
	//	std::cout<<goal<<std::endl;
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
			throw string("Error, out of leaves");
		}

	}



	//unravel, so we can go from current direction, to goal
	vector<Node::Direction> actionList; //list of directions
	while(goalPoint!=NULL) //directionlist from goal to root, take and put in action list
	{
		actionList.push_back(goalPoint->getAction());

		Node*temp = goalPoint;
		goalPoint=goalPoint->getParent();
        delete temp;
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

	try{
		Coordinate aboveleft= Coordinate(state.getRow()-1,state.getColumn()-1);
		if ( !(grid[aboveleft].hasContent(ContentType::Object))&&!grid[aboveleft].getViewed())
		{

			Leaves.push_back(new Node(toExplore, aboveleft, Node::UpLeft));
			grid[aboveleft].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}

	try{
		Coordinate abovelright= Coordinate(state.getRow()-1,state.getColumn()+1);
		if ( !(grid[abovelright].hasContent(ContentType::Object))&&!grid[abovelright].getViewed())
		{

			Leaves.push_back(new Node(toExplore, abovelright, Node::UpRight));
			grid[abovelright].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}

	try{
		Coordinate belowleft= Coordinate(state.getRow()+1,state.getColumn()-1);
		if ( !(grid[belowleft].hasContent(ContentType::Object))&&!grid[belowleft].getViewed())
		{

			Leaves.push_back(new Node(toExplore, belowleft, Node::DownLeft));
			grid[belowleft].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}

	try{
		Coordinate belowright= Coordinate(state.getRow()+1,state.getColumn()+1);
		if ( !(grid[belowright].hasContent(ContentType::Object))&&!grid[belowright].getViewed())
		{

			Leaves.push_back(new Node(toExplore, belowright, Node::DownRight));
			grid[belowright].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}


	if(toExplore->getChildren()==0) // end
			toExplore->deadEnd(grid,Leaves);


	return NULL;
}



