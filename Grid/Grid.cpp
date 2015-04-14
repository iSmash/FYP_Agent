#include "Grid.h"
using namespace environment;
void  Grid::adRealy(Relay toadd)
{
	relays.push_back(toadd);
}
            		
Relay Grid::getRelay(int _ID)
{
	for(int i=0; i< relays.size(); i++)
	{
		if(relays[i].getID()== _ID)
			return relays[i];
	}

}

void Grid::removeRelay(int _ID);
{
	for(int i=0; i< relays.size(); i++)
	{
		if(relays[i].getID()== _ID)
			relays.erase(i);
	}
}

void Grid::placeRelay(Relay toPlace)
{
	deployedRelays.push_back(toPlace);
}
