#include "ImplementAgent.h"
#include "../Relay/ImplementRelay.h"
using namespace Agentspace;
using namespace Relayspace;

void ImplementAgent::setRelayCount(int numberofRelays)
{
	//will do nothing if already has more then number told. but this should only be called on startups once.

	//has too few?
 	while(heldRelays.size()<numberofRelays)
	{
	    ImplementRelay* temp= new ImplementRelay();
		heldRelays.push_back(temp);
	}
}

void ImplementAgent::move(Direction toMove){std::cout<<"no move";}
bool ImplementAgent::done(){std::cout<<"no done"; return false;}
