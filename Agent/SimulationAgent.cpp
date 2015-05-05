#include "SimulationAgent.h"
#include "../Relay/SimulationRelay.h"
using namespace Agentspace;
using namespace Relayspace;
using namespace std;

void SimulationAgent::findPath()
{
    if(GoalLocation.size()==0)
        {
            //dont know where to go
            //cout<<"run out";
            vector<Relay*> deployedRelays =trueWorld.getRelays();
            for(int i=0; i<deployedRelays.size(); i++)
            {

                ((SimulationRelay*)deployedRelays[i])->incRange();
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
	for(int i=0; i<heldRelays.size(); i++)
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


}

void SimulationAgent::PlaceRelay(int ID, Coordinate whereToPlace)
{
    //cout<<"place node"<<endl;
	SimulationRelay* tobePlaced = (SimulationRelay*)GetRelay(ID);
    if(tobePlaced == NULL)
        return; //out of nodes.
    RemoveRelay(ID);
    trueWorld.placeRelay(tobePlaced);

	tobePlaced->updatePos(whereToPlace+trueLocationRelativity);
	trueWorld[whereToPlace+trueLocationRelativity].addContent(ContentType::RelayMarker);
	Agent::PlaceRelay(whereToPlace);
}

void SimulationAgent::PickupRelay(int ID, Coordinate whereToTake)
{
	cout<<"pickup2"<<endl; // DEBUG

    Relay* tobePicked = trueWorld.getRelay(ID);
    trueWorld.removeRelay(ID);
    heldRelays.push_back(tobePicked);

	tobePicked->updatePos(Coordinate(0,0));
	trueWorld[whereToTake+trueLocationRelativity].removeContent(ContentType::RelayMarker);
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
    case Node::UpRight:
		CurrentLocationtemp = Coordinate(CurrentLocation.getRow()-1, CurrentLocation.getColumn()+1);
		break;
	case Node::UpLeft:
		CurrentLocationtemp = Coordinate(CurrentLocation.getRow()-1, CurrentLocation.getColumn()-1);
		break;
	case Node::DownRight:
		CurrentLocationtemp = Coordinate(CurrentLocation.getRow()+1, CurrentLocation.getColumn()+1);
		break;
	case Node::DownLeft:
		CurrentLocationtemp = Coordinate(CurrentLocation.getRow()+1, CurrentLocation.getColumn()-1);
		break;
	case Node::Root:

		return true;
		break;
	}

	if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Wall) )
	{
		//bad move
		return false;
	}
	if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Client))
	{
	    if(DeploymentMethod>1)
            updateGoal();
        return false;
	}
	if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Goal))
	{
	    if(DeploymentMethod>1)
            {
                GoalLocation.pop_back();
                try{PlaceRelay(heldRelays.front()->getID(),CurrentLocationtemp);}
                catch(RelayError e){//cout<<"out of relays"<<endl;
                }
            }
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
	trueWorld[CurrentLocation+trueLocationRelativity].addContent(ContentType::Robot);
	lookAround();

	return true;
}

bool SimulationAgent::done()
{
     //cout<<"done check"<<endl;
    vector<Relay*> deployedRelays = trueWorld.getRelays();
vector<SimulationRelay*> tocheck;

     for( int j=1; j<deployedRelays.size(); j++) //set all but the base to not be on network
    {
            ((SimulationRelay*)deployedRelays[j])->OnNetwork=false;
           // cout<<deployedRelays[j]->getPos()<<endl;
    }


        tocheck.push_back((SimulationRelay*)deployedRelays.front()); //put base on first thing to look at
        deployedRelays.erase(deployedRelays.begin());

    while(tocheck.size()>0)
    {
     if(tocheck.back()->OnNetwork)
        {

            vector<Coordinate> currentdomain = tocheck.back()->getDomain();
            //cout<<"on network "<<tocheck.back()->getPos()<<endl;

            for(int i =0; i< currentdomain.size(); i++)
            {
                //look over every cell that this relay has homain over
                if(currentdomain[i]==ClientLocation)
                    {
                        //cout<<"sees client"<<endl;
                        return true;
                    }

                for( int j=0; j<deployedRelays.size(); j++)
                {
                    //look over all remaining relays to add them to the network

                    if(currentdomain[i]==deployedRelays[j]->getPos())
                    {
                        //match, this relay is now on the network we will now check it to see if it connects anyone
                        ((SimulationRelay*)deployedRelays[j])->OnNetwork=true;


                         tocheck.insert(tocheck.begin(),((SimulationRelay*)deployedRelays[j]));
                         deployedRelays.erase(deployedRelays.begin()+j); //remove it so we dont go back and fourth adding to network

                    }
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
