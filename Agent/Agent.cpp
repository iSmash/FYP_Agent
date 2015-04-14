#include <iostream>
#include "Agent.h"
using namespace Agentspace;
using namespace Relayspace;

void Agent::tryPath()
{
    KnownWorld.clearGridViewed();
	std::cout<<"no try path yet"<<std::endl;
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


