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

bool ImplementAgent::move(Node::Direction toMove)
{
    float x=0.0;
    float y=0.0;
//    omniDrive.setVelocity( x, y, 0 );
}
bool ImplementAgent::lowSignal(){std::cout<<"no low signal"; return false;}
bool ImplementAgent::done(){std::cout<<"no done"; return false;}
void ImplementAgent::lookAround(){std::cout<<"no look around";}
