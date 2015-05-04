#include "SimulationAgent.h"
#include "../Relay/SimulationRelay.h"
using namespace Agentspace;
using namespace Relayspace;
using namespace std;
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
		temp->setRange(1);
	}
	for(int i=0; i<knownWorld.getRelays().size(); i++)
	{
		SimulationRelay* temp= (SimulationRelay*)knownWorld.getRelays()[i];
		temp->addRange(range);
		temp->setRange(1);
	}


}

void SimulationAgent::PlaceRelay(int ID, Coordinate whereToPlace)
{
    //cout<<"place node"<<endl;
	SimulationRelay* tobePlaced = (SimulationRelay*)getRelay(ID);
    if(tobePlaced == NULL)
        return; //out of nodes.
    removeRelay(ID);
    trueworld.placeRelay(tobePlaced);

	tobePlaced->updatePos(whereToPlace+trueLocationRelativity);
	trueworld[whereToPlace+trueLocationRelativity].addContent(ContentType::RelayMarker);
	Agent::PlaceRelay(whereToPlace);
}

void SimulationAgent::PickupRelay(int ID, Coordinate whereToTake)
{
	cout<<"pickup2"<<endl; // DEBUG

    Relay* tobePicked = trueworld.getRelay(ID);
    trueworld.removeRelay(ID);
    heldRelays.push_back(tobePicked);

	tobePicked->updatePos(Coordinate(0,0));
	trueworld[whereToTake+trueLocationRelativity].removeContent(ContentType::RelayMarker);
	Agent::PickupRelay(whereToTake);
}
void SimulationAgent::lookAround()
{
if(CurrentLocation.getRow()==0)
	{
		trueLocationRelativity=RelativeCoordinate(trueLocationRelativity.getRow()-1, trueLocationRelativity.getColumn());
	}
	if(CurrentLocation.getColumn()==0)
	{
		trueLocationRelativity=RelativeCoordinate(trueLocationRelativity.getRow(), trueLocationRelativity.getColumn()-1);
	}
	Agent::lookAround();



	//std::cout<<"true"<<trueCurrentLocation.getRow()<<" "<< trueCurrentLocation.getColumn()<<std::endl;
	//std::cout<<"knonwn"<<CurrentLocation.getRow()<<" "<< CurrentLocation.getColumn()<<std::endl;
	for(int i=-1; i<2; i++)
	{
		for(int j=-1; j<2;j++)
		{
			try{        //std::cout<<i<<" "<<j<<std::endl;
			    Coordinate trueLocation = CurrentLocation+trueLocationRelativity;
				std::vector<Content> temp= trueworld[Coordinate(trueLocation.getRow()+i, trueLocation.getColumn()+j)].getContent();
				//std::cout<<temp.size()<<std::endl;
				for(int x=0; x< temp.size(); x++)
				{
					knownWorld[Coordinate(CurrentLocation.getRow()+i, CurrentLocation.getColumn()+j)].addContent(temp[x]);
				}
			}
			catch(std::out_of_range r)
			{
			    knownWorld[Coordinate(CurrentLocation.getRow()+i, CurrentLocation.getColumn()+j)].addContent(ContentType::Wall);
			}
		}}

}



bool SimulationAgent::move(Node::Direction toMove)
{

	Coordinate CurrentLocationtemp;
	Coordinate OldPos = CurrentLocation; //for backtrack in method one
	switch (toMove)
	{
	case Node::Right:
		CurrentLocationtemp = Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()+1);

		break;
	case Node::Left:
		CurrentLocationtemp = Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()-1);
		break;
	case Node::Up:
		CurrentLocationtemp = Coordinate(CurrentLocation.getRow()-1, CurrentLocation.getColumn());
		break;
	case Node::Down:
		CurrentLocationtemp = Coordinate(CurrentLocation.getRow()+1, CurrentLocation.getColumn());
		break;
	case Node::Root:

		return true;
		break;
	}

	if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Wall))
	{
		//bad move
		return false;
	}


	CurrentLocation=CurrentLocationtemp;


	if(DeploymentMethod==1 && lowSignal()) //find out if need to place a new node donw
	{
		try{PlaceRelay(heldRelays.front()->getID(),OldPos);}
		catch(RelayError e){//cout<<"out of relays"<<endl;
		}
	}

    //cout<<"Cur "<< CurrentLocation<<endl;
    //cout<<"Rel "<< trueLocationRelativity<<endl;
    //cout<<"Sum "<< CurrentLocation+trueLocationRelativity<<endl;
	trueworld[CurrentLocation+trueLocationRelativity].addContent(ContentType::Robot);
	lookAround();

	return true;
}

bool SimulationAgent::done()
{
	if(knownWorld[CurrentLocation].hasContent(ContentType::Goal))
		return true;

	return false;
}

bool SimulationAgent::lowSignal()
{
	vector<Relay*> gridRelays = trueworld.getRelays();
	bool poor_range =true;
	for(int i =0; i< gridRelays.size(); i++)
	{
		//cout<<"relay"<<i;
		if(gridRelays[i]->inRange(CurrentLocation+trueLocationRelativity) )
			poor_range=false;
	}
	return poor_range;
}
