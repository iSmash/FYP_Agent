#include <iostream>
#include "Agent.h"
using namespace Agentspace;
using namespace Relayspace;


void printDirection2(Node::Direction toprint)
{
     switch(toprint)
    {
        case Node::Right: cout<<"Right; ";break;
        case Node::Left: cout<<"Left; "; break;
        case Node::Up: cout<<"Up; ";break;
        case Node::Down: cout<<"Down; ";break;
        case Node::Root:cout<<"start;" ;break;
    }
}


void Agent::tryPath()
{
    //std::cout<<"Path is"<<std::endl;

	while(actionList.size()!=0)
    {
        //printDirection2(actionList.back());

        if(!move(actionList.back()))
            break;

          actionList.pop_back();
        KnownWorld[CurrentLocation].addContent(ContentType::Robot);
    }


    //clean up old search
    KnownWorld.clearGridViewed();
    planner.clear();

}



Relay* Agent::getRelay(int _ID)
{
	for(int i=0; i< heldRelays.size(); i++)
	{
		if(heldRelays[i]->getID()== _ID)
			return heldRelays[i];
	}
}

void Agent::PlaceRelay(Coordinate whereToPlace)
{
    KnownWorld[whereToPlace].addContent(ContentType::RelayMarker);
}

void Agent::PickupRelay(Coordinate PickFrom)
{
    KnownWorld[PickFrom].removeContent(ContentType::RelayMarker);
}

void Agent::lookAround()
 {
    //look up
    //std::cout<<"looking"<<std::endl;
    if(CurrentLocation.getRow()==0)
    {
        //as top as can be, so lets make more world
         //std::cout<<"top ";
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
         //std::cout<<"right ";
        KnownWorld.updateSize(Grid::right);
    }

    //look left
    if(CurrentLocation.getColumn()==0)
    {
        //as top as can be, so lets make more world
        // std::cout<<"left ";
        KnownWorld.updateSize(Grid::left);
        //as we are push above the grid, we need to move down our knonw position
        CurrentLocation=Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()+1);
    }



 }

 void Agent::setGoal(RelativeCoordinate relativeToGoal)
 {/**using magic we find where the goal is */

        Grid::updateSizeDirection direcion;
        if(relativeToGoal.getRow()<0)
        {
            //add up
            direcion= Grid::top;
        }
        else
              direcion= Grid::bottom;

        for(int i =0; i< abs(relativeToGoal.getRow()); i++)
        {
            KnownWorld.updateSize(direcion);
        }

        if(relativeToGoal.getColumn()<0)
        {
            //add up
            direcion= Grid::left;
        }
        else
              direcion= Grid::right;

        for(int i =0; i< abs(relativeToGoal.getColumn()); i++)
        {
            KnownWorld.updateSize(direcion);
        }

         Goal = Coordinate(CurrentLocation.getRow()+relativeToGoal.getRow(), CurrentLocation.getColumn()+relativeToGoal.getColumn());
        KnownWorld[Goal].addContent(ContentType::Goal);

 }


