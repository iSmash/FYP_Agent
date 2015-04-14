#include "Agent.h"
using namespace Agent;

void Agent::tryPath()
{
	std::cout<<"no try path yet"<<endl;
}
			


Relay Agent::getRelay(int _ID)
{
	for(int i=0; i< heldRelays.size(); i++)
	{
		if(heldRelays[i].getID()== _ID)
			return heldRelays[i];
	}
}

void Agent::PlaceRelay(int _ID, Coordinate whereToPlace)
{
	Relay tobePlaced = null;
	for(int i=0; i< heldRelays.size(); i++)
	{
		if(heldRelays[i].getID()== _ID)
		{
			tobePlaced=heldRelays[i];
			heldRelays.erase(i);
			break;
		}
	}
	if (tobePlaced==null)
		throw(RelayError("Cannont place, Id not found");
	
	tobePlaced.updatePos(whereToPlace);
	KnownWorld.placeRelay(tobePlaced)
}

void Agent::PickupRelay(int _ID)
{
	heldRelays.push_back(KnownWorld.getRelay(_ID));
	KnownWorld.removeRelay(_ID);
}

