#include <iostream>
#include "Agent.h"
using namespace Agentspace;
using namespace Relayspace;



void printDirection(Node::Direction toprint)
{
     switch(toprint)
    {
        case Node::Right: cout<<"Right; ";break;
        case Node::Left: cout<<"Left; "; break;
        case Node::Up: cout<<"Up; ";break;
        case Node::Down: cout<<"Down; ";break;
        case Node::Root: break;
    }
}

void Agent::tryPath()
{
    std::cout<<"Path is"<<std::endl;
	for(int i=0; i<actionList.size(); i++)
    {
        printDirection(Node::Down);
    }

    KnownWorld.clearGridViewed();
    planner.clear();
    //clean up old search
}



Relay* Agent::getRelay(int _ID)
{
	for(int i=0; i< heldRelays.size(); i++)
	{
		if(heldRelays[i]->getID()== _ID)
			return heldRelays[i];
	}
}

void Agent::PlaceRelay(int ID, Coordinate whereToPlace)
{
	Relay* tobePlaced = NULL;
	for(int i=0; i< heldRelays.size(); i++)
	{
		if(heldRelays[i]->getID()== ID)
		{
			tobePlaced=heldRelays[i];
			heldRelays.erase(heldRelays.begin()+i);
			break;
		}
	}
	if (tobePlaced==NULL)
		throw(RelayError());

	tobePlaced->updatePos(whereToPlace);
	KnownWorld.placeRelay(tobePlaced);
}

void Agent::PickupRelay(int ID)
{
	heldRelays.push_back(KnownWorld.getRelay(ID));
	KnownWorld.removeRelay(ID);
}

void Agent::lookAround()
 {
    //look up
    //std::cout<<"looking"<<std::endl;
    if(CurrentLocation.getRow()==0)
    {
        //as top as can be, so lets make more world
        // std::cout<<"top ";
        KnownWorld.updateSize(Grid::top);
        //as we are push above the grid, we need to move down our knonw position
        CurrentLocation=Coordinate(CurrentLocation.getRow()+1, CurrentLocation.getColumn());
    }

    //look donw
    if(CurrentLocation.getRow()>=KnownWorld.getLast().getRow()-1)
    {
        //as top as can be, so lets make more world
        //std::cout<<"bot ";
        KnownWorld.updateSize(Grid::bottom);
    }



    //look right
    if(CurrentLocation.getColumn()>=KnownWorld.getLast().getColumn()-1)
    {
        //as top as can be, so lets make more world
        // std::cout<<"right ";
        KnownWorld.updateSize(Grid::right);
    }


    //look left
    if(CurrentLocation.getColumn()==0)
    {
        //as top as can be, so lets make more world
         //std::cout<<"left ";
        KnownWorld.updateSize(Grid::left);
        //as we are push above the grid, we need to move down our knonw position
        CurrentLocation=Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()+1);
    }



 }


