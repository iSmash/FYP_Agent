#include "SimulationAgent.h"
#include "../Relay/SimulationRelay.h"
#include <math.h>
using namespace Agentspace;
using namespace Relayspace;
using namespace std;

void SimulationAgent::findPath()
{
    if(GoalLocation.size()==0)
        {
            //dont know where to go
            //cout<<"run out";

             SimulationRelay::incRange();
 for(int i=0; i<trueWorld.getRelays().size(); i++)
        {
             ((SimulationRelay*)trueWorld.getRelays()[i])->findDomain();
       }

        }
    else
        Agent::findPath();
}


void SimulationAgent::setRelayCount(int numberofRelays)
{
	//will do nothing if already has more then number told. but this should only be called on startups once.

	//has too few?
	while(heldRelays.size()<numberofRelays)
	{
		SimulationRelay* temp= new SimulationRelay(&trueWorld);
		heldRelays.push_back( temp);
	}
}

void SimulationAgent::addRange(int range)
{
	/*for(int i=0; i<heldRelays.size(); i++)
	{
		SimulationRelay* temp= (SimulationRelay*)heldRelays[i];
		temp->addRange(range);
//		temp->incRange();
	}
	for(int i=0; i<knownWorld.getRelays().size(); i++)
	{
		SimulationRelay* temp= (SimulationRelay*)knownWorld.getRelays()[i];
		temp->addRange(range);
		//temp->incRange();
	}
	*/
	SimulationRelay::addRange(range);


}

void SimulationAgent::PlaceRelay(int ID, Coordinate whereToPlace)
{
	SimulationRelay* tobePlaced = (SimulationRelay*)GetRelay(ID);
    if(tobePlaced == NULL)
        return; //out of nodes.
    cout<<"Placing"<<ID<<" at"<<whereToPlace+trueLocationRelativity<<endl;
    RemoveRelay(ID);
    trueWorld.placeRelay(tobePlaced);
	trueWorld[whereToPlace+trueLocationRelativity].addContent(ContentType::RelayMarker);
	tobePlaced->updatePos(whereToPlace+trueLocationRelativity);
	tobePlaced->findDomain();
	Agent::PlaceRelay(ID, whereToPlace);

}

void SimulationAgent::PickupRelay(int ID, Coordinate whereToTake)
{
	cout<<"pickup2"<<endl; // DEBUG

    Relay* tobePicked = trueWorld.getRelay(ID);
    trueWorld.removeRelay(ID);
    heldRelays.push_back(tobePicked);

	tobePicked->updatePos(Coordinate(0,0));
	trueWorld[whereToTake+trueLocationRelativity].removeContent(ContentType::RelayMarker);
 	Agent::PickupRelay(ID,whereToTake);
}
void SimulationAgent::evaluateRealayRange()
{
    int relayCount= heldRelays.size()+trueWorld.getRelays().size();
    int distance= sqrt(pow((double)(ClientLocation.getRow()-BaseLocation.getRow()) ,2.0)+pow((double)(ClientLocation.getColumn()-BaseLocation.getColumn()) ,2.0));
    while(distance> relayCount*SimulationRelay::getRange())
    {
        cout<<"too small";
        SimulationRelay::incRange();
         for(int i=0; i<trueWorld.getRelays().size(); i++)
        {
             ((SimulationRelay*)trueWorld.getRelays()[i])->findDomain();
       }
    }
}

void SimulationAgent::ShuffleLoctions(int row, int column)
{
    trueLocationRelativity=RelativeCoordinate(trueLocationRelativity.getRow()-row, trueLocationRelativity.getColumn()-column);
    Agent::ShuffleLoctions(row, column);
}
void SimulationAgent::lookAround()
{
/*if(CurrentLocation.getRow()==0)
	{
		trueLocationRelativity=RelativeCoordinate(trueLocationRelativity.getRow()-1, trueLocationRelativity.getColumn());
	}
	if(CurrentLocation.getColumn()==0)
	{
		trueLocationRelativity=RelativeCoordinate(trueLocationRelativity.getRow(), trueLocationRelativity.getColumn()-1);
	}*/
	Agent::lookAround();



	//std::cout<<"true"<<trueCurrentLocation.getRow()<<" "<< trueCurrentLocation.getColumn()<<std::endl;
	//std::cout<<"knonwn"<<CurrentLocation.getRow()<<" "<< CurrentLocation.getColumn()<<std::endl;
	for(int i=-1; i<2; i++)
	{
		for(int j=-1; j<2;j++)
		{
			try{        //std::cout<<i<<" "<<j<<std::endl;
			    Coordinate trueLocation = CurrentLocation+trueLocationRelativity;
				std::vector<Content> temp= trueWorld[Coordinate(trueLocation.getRow()+i, trueLocation.getColumn()+j)].getContent();
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

    bool AgentResult = Agent::move(toMove);

    //cout<<"Cur "<< CurrentLocation<<endl;
    //cout<<"Rel "<< trueLocationRelativity<<endl;
    //cout<<"Sum "<< CurrentLocation+trueLocationRelativity<<endl;
	if(AgentResult)
	{
	    trueWorld[CurrentLocation+trueLocationRelativity].addContent(ContentType::Robot);
        lookAround();
	}

	return AgentResult;
}

bool SimulationAgent::done()
{
     cout<<"done check"<<endl;
    vector<Relay*> deployedRelays = trueWorld.getRelays();
vector<SimulationRelay*> tocheck;

        tocheck.push_back((SimulationRelay*)deployedRelays.front()); //put base on first thing to look at
        deployedRelays.erase(deployedRelays.begin());

    while(tocheck.size()>0)
    {


            vector<Coordinate> currentdomain = tocheck.back()->getDomain();
            cout<<"on network "<<tocheck.back()->getID()<<" "<<tocheck.back()->getPos()<<endl;

            for(int i =0; i< currentdomain.size(); i++)
            {
                //look over every cell that this relay has homain over
                if(currentdomain[i]==ClientLocation+trueLocationRelativity)
                    {
                       // cout<<"sees client"<<endl;
                        return true;
                    }

                for( int j=0; j<deployedRelays.size(); j++)
                {
                    //look over all remaining relays to add them to the network

                    if(currentdomain[i]==deployedRelays[j]->getPos())
                    {
                        //match, this relay is now on the network we will now check it to see if it connects anyone
                        cout<<"found"<<deployedRelays[j]->getID();
                        tocheck.insert(tocheck.begin(),((SimulationRelay*)deployedRelays[j]));
                         deployedRelays.erase(deployedRelays.begin()+j); //remove it so we dont go back and fourth adding to network
                    }
                }
            }
         tocheck.pop_back();
    }
 //cout<<"not done yet"<<endl;
    return false;



}

bool SimulationAgent::lowSignal()
{
	vector<Relay*> gridRelays = trueWorld.getRelays();
	bool poor_range =true;
	for(int i =0; i< gridRelays.size(); i++)
	{
		//cout<<"relay"<<i;
		if(gridRelays[i]->inRange(CurrentLocation+trueLocationRelativity) )
			poor_range=false;
	}
	return poor_range;
}
