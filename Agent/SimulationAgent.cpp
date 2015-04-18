#include "SimulationAgent.h"
#include "../Relay/SimulationRelay.h"
using namespace Agentspace;
using namespace Relayspace;

void SimulationAgent::setRelayCount(int numberofRelays)
{
	//will do nothing if already has more then number told. but this should only be called on startups once.

	//has too few?
 	while(heldRelays.size()<numberofRelays)
	{
        SimulationRelay* temp= new SimulationRelay();
		heldRelays.push_back( temp);
	}
}

 void SimulationAgent::addRange(int range)
 {
     for(int i=0; i<heldRelays.size(); i++)
     {
         SimulationRelay* temp= (SimulationRelay*)heldRelays[i];
         temp->addRange(range);
     }
     for(int i=0; i<KnownWorld.getRelays().size(); i++)
     {
         SimulationRelay* temp= (SimulationRelay*)KnownWorld.getRelays()[i];
         temp->addRange(range);
     }


 }

 void SimulationAgent::lookAround()
 {
   Agent::lookAround();

//std::cout<<"true"<<trueCurrentLocation.getRow()<<" "<< trueCurrentLocation.getColumn()<<std::endl;
//std::cout<<"knonwn"<<CurrentLocation.getRow()<<" "<< CurrentLocation.getColumn()<<std::endl;
   for(int i=-1; i<2; i++)
   {
    for(int j=-1; j<2;j++)
    {
          // std::cout<<i<<" "<<j<<std::endl;
    std::vector<Content> temp= trueworld[Coordinate(trueCurrentLocation.getRow()+i, trueCurrentLocation.getColumn()+j)].getContent();
  //std::cout<<temp.size()<<std::endl;
    for(int x=0; x< temp.size(); x++)
    {
        KnownWorld[Coordinate(CurrentLocation.getRow()+i, CurrentLocation.getColumn()+j)].addContent(temp[x]);
    }
 }}


 }

 void SimulationAgent::move(Direction toMove){std::cout<<"no move";}
 bool SimulationAgent::done(){std::cout<<"no done";return false;}
