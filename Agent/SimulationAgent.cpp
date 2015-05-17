#include "SimulationAgent.h"
#include "../Relay/SimulationRelay.h"
#include <math.h>
using namespace Agentspace;
using namespace Relayspace;
using namespace std;

void SimulationAgent::findPath()
{
    if(knownWorld.getLast().getRow()>trueWorld.getLast().getRow()+2 && knownWorld.getLast().getColumn()>trueWorld.getLast().getColumn()+2)
    {
            throw string("unreachable location presented");
    }

    if(GoalLocation.size()==0)
    {
        //dont know where to go
        cout<<"grow range";

        SimulationRelay::incRange();
        for(int i=0; i<trueWorld.getRelays().size(); i++)
        {
            ((SimulationRelay*)trueWorld.getRelays()[i])->findDomain();
        }

    }
    else
    {
        Agent::findPath();
    }
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
    //cout<<"Placing"<<ID<<" at"<<whereToPlace+trueLocationRelativity<<endl;
    RemoveRelay(ID);
    trueWorld.placeRelay(tobePlaced);
    trueWorld[whereToPlace+trueLocationRelativity].addContent(ContentType::RelayMarker);
    tobePlaced->updatePos(whereToPlace+trueLocationRelativity);
    Agent::PlaceRelay(ID, whereToPlace);

}

void SimulationAgent::PickupRelay(int ID, Coordinate whereToTake)
{
    //cout<<"pickup2"<<endl; // DEBUG

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
      int distance;
    if(DeploymentMethod ==1)
    {
        distance= ceil(  sqrt(
                              ceil(pow((double)(ClientLocation.getRow()-BaseLocation.getRow()) ,2.0))  +
                              ceil(pow((double)(ClientLocation.getColumn()-BaseLocation.getColumn()) ,2.0))
                              )
                       ); //distance to goal, crows path
    }
    else if (DeploymentMethod ==2)
    {
        ((SimulationRelay*)trueWorld.getRelay(0))->updatePos(ClientLocation);
        knownWorld.clearGridViewed();
        planner.clear();
        actionList = planner.findPath(CurrentLocation, GoalLocation,knownWorld);
        distance= actionList.size();
    }
    else
    {
        cout<<"evalutate relay range called with bad Deployment method"<<endl;
    }
    //cout<<relayCount<<" D:"<<distance<<endl;
    while(distance> relayCount*(SimulationRelay::getRange()-1))
    {
        //cout<<"too small";
        SimulationRelay::incRange();
        for(int i=0; i<trueWorld.getRelays().size(); i++)
        {
            ((SimulationRelay*)trueWorld.getRelays()[i])->findDomain();
        }
    }
}

void SimulationAgent::ShuffleLoctions(int row, int column)
{
    //cout<<"sim suffle"<<endl;
    trueLocationRelativity=RelativeCoordinate(trueLocationRelativity.getRow()-row, trueLocationRelativity.getColumn()-column);
    Agent::ShuffleLoctions(row, column);
}
void SimulationAgent::lookAround()
{
    //cout<<"looking around"<<endl;
    /*if(CurrentLocation.getRow()==0)
    	{
    		trueLocationRelativity=RelativeCoordinate(trueLocationRelativity.getRow()-1, trueLocationRelativity.getColumn());
    	}
    	if(CurrentLocation.getColumn()==0)
    	{
    		trueLocationRelativity=RelativeCoordinate(trueLocationRelativity.getRow(), trueLocationRelativity.getColumn()-1);
    	}*/
    Agent::lookAround();



   // std::cout<<"true"<<trueCurrentLocation.getRow()<<" "<< trueCurrentLocation.getColumn()<<std::endl;
    //std::cout<<"knonwn"<<CurrentLocation.getRow()<<" "<< CurrentLocation.getColumn()<<std::endl;
    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
        {
            try         //std::cout<<i<<" "<<j<<std::endl;
            {
                Coordinate trueLocation = CurrentLocation+trueLocationRelativity;
                //cout<<"relative location"<<CurrentLocation<<endl;
                //cout<<"true"<<trueLocation;
                std::vector<Content> temp= trueWorld[Coordinate(trueLocation.getRow()+i, trueLocation.getColumn()+j)].getContent();
                //std::cout<<temp.size()<<std::endl;
                for(int x=0; x< temp.size(); x++)
                {
                    knownWorld[Coordinate(CurrentLocation.getRow()+i, CurrentLocation.getColumn()+j)].addContent(temp[x]);
                }
            }
            catch(std::out_of_range r)
            {
                // cout<<"world end"<<Coordinate(CurrentLocation.getRow()+i, CurrentLocation.getColumn()+j)<<endl;
                knownWorld[Coordinate(CurrentLocation.getRow()+i, CurrentLocation.getColumn()+j)].addContent(ContentType::Jormungandr_Wall);

            }
        }
    }
    // cout<<"done looking"<<endl;

}



bool SimulationAgent::move(Node::Direction toMove)
{

    bool AgentResult = Agent::move(toMove);

    //cout<<"Cur "<< CurrentLocation<<endl;
   // cout<<"Rel "<< trueLocationRelativity<<endl;
    //cout<<"Sum "<< CurrentLocation+trueLocationRelativity<<endl;
    if(AgentResult)
    {
        trueWorld[CurrentLocation+trueLocationRelativity].addContent(ContentType::Robot);
        lookAround();
    }
 //std::cout<<"done"<<std::endl;
    return AgentResult;
}

bool SimulationAgent::done()
{
    //cout<<"done check"<<endl;
    vector<Relay*> deployedRelays = trueWorld.getRelays();
    vector<SimulationRelay*> tocheck;

    tocheck.push_back((SimulationRelay*)deployedRelays.front()); //put base on first thing to look at
    deployedRelays.erase(deployedRelays.begin());

    while(tocheck.size()>0)
    {


        vector<Coordinate> currentdomain = tocheck.back()->getDomain();
        //cout<<"on network "<<tocheck.back()->getID()<<" "<<tocheck.back()->getPos()<<endl;

        for(int i =0; i< currentdomain.size(); i++)
        {
            //look over every cell that this relay has homain over
            //cout<<"looking at"<<currentdomain[i]<<endl;
            if(currentdomain[i]==ClientLocation+trueLocationRelativity && DeploymentMethod!=2)
            {
               // cout<<"sees client"<<endl;
                return true;
            }
            else  if(currentdomain[i]==BaseLocation+trueLocationRelativity && DeploymentMethod==2&& return_journy)
            {
                //cout<<"sees base"<<endl;
                return true;
            }
            for( int j=0; j<deployedRelays.size(); j++)
            {
                //look over all remaining relays to add them to the network

                if(currentdomain[i]==deployedRelays[j]->getPos())
                {
                    //match, this relay is now on the network we will now check it to see if it connects anyone
                    //cout<<"found"<<deployedRelays[j]->getID();
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

bool SimulationAgent::lowSignal(Coordinate CurrentLocationtemp)
{
    //cout<<"low sign at "<<CurrentLocation<<endl;
    vector<Relay*> gridRelays = trueWorld.getRelays();
    bool poor_range =true;
    for(int i =0; i< gridRelays.size(); i++)
    {
        //cout<<"relay"<<i;
        if(gridRelays[i]->inRange(CurrentLocationtemp+trueLocationRelativity) )
            poor_range=false;
    }
   // cout<<poor_range<<endl;
    return poor_range;
}



