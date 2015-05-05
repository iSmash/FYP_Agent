#include <iostream>
#include "Agent.h"
using namespace Agentspace;
using namespace Relayspace;
using namespace std;

void printDirection2(Node::Direction toprint)
{
	switch(toprint)
	{
    case Node::Right:     cout<<"Right; ";      break;
    case Node::Left:      cout<<"Left; ";       break;
    case Node::Up:        cout<<"Up; ";         break;
    case Node::Down:      cout<<"Down; ";       break;
    case Node::UpRight:   cout<<"UpRight; ";    break;
    case Node::UpLeft:    cout<<"UpLeft; ";     break;
    case Node::DownLeft:  cout<<"DownLeft; ";   break;
    case Node::DownRight: cout<<"DownRight; ";  break;
    case Node::Root:      cout<<"Start;";       break;
	}
}


void Agent::tryPath()
{
	//std::cout<<"Path is"<<std::endl;

	while(actionList.size()!=0)
	{
		printDirection2(actionList.back());

		if(!move(actionList.back()))
			break;

		actionList.pop_back();
		knownWorld[CurrentLocation].addContent(ContentType::Robot);
	}


	//clean up old search
	knownWorld.clearGridViewed();
	planner.clear();
}

void Agent::updateGoal()
{
    cout<<"update goals";

    //at clinet, now set where relays should place.

    knownWorld[GoalLocation.back()].removeContent(ContentType::Goal);

    for(int i =0; i< GoalLocation.size(); i++)
    {
        cout<<GoalLocation[i]<<endl;
    }
    GoalLocation = planner.positionRelays(DeploymentMethod, heldRelays.size(), BaseLocation, ClientLocation);
    for(int i=0; i<GoalLocation.size(); i++)
    {
        cout<<GoalLocation[i]<<endl;
        knownWorld[GoalLocation[i]].addContent(ContentType::Goal);
    }


}


Relay* Agent::GetRelay(int _ID)
{
	for(int i=0; i< heldRelays.size(); i++)
	{
		if(heldRelays[i]->getID()== _ID)
			return heldRelays[i];
	}
	//cout<<"failed to find relay"<<endl;
	return NULL;
}

void Agent::RemoveRelay(int _ID)
{
	for(int i=0; i< heldRelays.size(); i++)
	{
		if(heldRelays[i]->getID()== _ID)
			heldRelays.erase(heldRelays.begin()+i);
	}
}

void Agent::PlaceRelay(Coordinate whereToPlace)
{
	knownWorld[whereToPlace].addContent(ContentType::RelayMarker);
}

void Agent::PickupRelay(Coordinate PickFrom)
{
	knownWorld[PickFrom].removeContent(ContentType::RelayMarker);

}

// TODO 20150505 does this need to be expanded for new diagonal movement? I think not..
void Agent::lookAround()
{
	//look up
	//std::cout<<"looking"<<std::endl;
	if(CurrentLocation.getRow()==0)
	{
		//as top as can be, so lets make more world
		//std::cout<<"top ";
		knownWorld.updateSize(Grid::top);
		//as we are push above the grid, we need to move down our knonw position
		ShuffleLoctions(1,0);
	}

	//look down
	if(CurrentLocation.getRow()>=knownWorld.getLast().getRow()-1)
	{
		//as top as can be, so lets make more world
		//std::cout<<"bot ";
		knownWorld.updateSize(Grid::bottom);
	}



	//look right
	if(CurrentLocation.getColumn()>=knownWorld.getLast().getColumn()-1)
	{
		//as top as can be, so lets make more world
		//std::cout<<"right ";
		knownWorld.updateSize(Grid::right);
	}

	//look left
	if(CurrentLocation.getColumn()==0)
	{
		//as top as can be, so lets make more world
		// std::cout<<"left ";
		knownWorld.updateSize(Grid::left);
		//as we are push above the grid, we need to move down our knonw position

		ShuffleLoctions(0,1);
	}



}

void Agent::ShuffleLoctions(int row, int column)
{
    CurrentLocation=Coordinate(CurrentLocation.getRow()+row, CurrentLocation.getColumn()+column);
	for(int i=0; i< GoalLocation.size(); i++)
        GoalLocation[i]=Coordinate(GoalLocation[i].getRow()+row, GoalLocation[i].getColumn()+column);
	BaseLocation=Coordinate(BaseLocation.getRow()+row, BaseLocation.getColumn()+column);
	ClientLocation=Coordinate(ClientLocation.getRow()+row, ClientLocation.getColumn()+column);
}


void Agent::setGoal(RelativeCoordinate relativeToGoal)
{/**using magic we find where the goal is */

	Grid::updateSizeDirection direcion;
	if(relativeToGoal.getRow()<0)
	{
		for(int i =0; i< abs(relativeToGoal.getRow()); i++)
	{
		knownWorld.updateSize(Grid::top);
		CurrentLocation=Coordinate(CurrentLocation.getRow()+1, CurrentLocation.getColumn());

	}
	}
	else
		{
		for(int i =0; i< abs(relativeToGoal.getRow()); i++)
	{
		knownWorld.updateSize(Grid::bottom);
	}
		}


	if(relativeToGoal.getColumn()<0)
	{
		//add up

		for(int i =0; i< abs(relativeToGoal.getColumn()); i++)
	{
		knownWorld.updateSize(Grid::left);
		CurrentLocation=Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()+1);

	}
	}
	else
		{
		    	for(int i =0; i< abs(relativeToGoal.getColumn()); i++)
	{
		knownWorld.updateSize(Grid::right);
		}
		}



	ClientLocation = CurrentLocation+relativeToGoal;
	GoalLocation.push_back(ClientLocation);
   //cout<<"C"<<CurrentLocation<<endl;
   //cout<<"G"<<GoalLocation<<endl;
	knownWorld[GoalLocation.back()].addContent(ContentType::Goal);

}


