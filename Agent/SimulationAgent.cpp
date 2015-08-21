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
        //cout<<"grow range";

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
    fullRelayCount=numberofRelays;
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

void SimulationAgent::PickupRelay(Coordinate whereToTake)
{
    //cout<<"pickup2"<<endl; // DEBUG

    Relay* tobePicked = trueWorld.removeRelay(whereToTake+trueLocationRelativity);
    heldRelays.push_back(tobePicked);

    trueWorld[whereToTake+trueLocationRelativity].removeContent(ContentType::RelayMarker);
    Agent::PickupRelay(whereToTake);
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
        ((SimulationRelay*)trueWorld.getRelay(0))->updatePos(ClientLocation+trueLocationRelativity);

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

void SimulationAgent::lookAround(Coordinate lookFrom)
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
    Agent::lookAround(lookFrom);



   // std::cout<<"true"<<trueCurrentLocation.getRow()<<" "<< trueCurrentLocation.getColumn()<<std::endl;
    //std::cout<<"knonwn"<<CurrentLocation.getRow()<<" "<< CurrentLocation.getColumn()<<std::endl;
    bool newMapData= false;
    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
        {
            Coordinate tempLocation=Coordinate(CurrentLocation.getRow()+i, CurrentLocation.getColumn()+j);
            try         //std::cout<<i<<" "<<j<<std::endl;
            {
                Coordinate trueLocation = CurrentLocation+trueLocationRelativity;
                           trueLocation = Coordinate(trueLocation.getRow()+i, trueLocation.getColumn()+j);

                //cout<<"relative location"<<CurrentLocation<<endl;
                //cout<<"true"<<trueLocation;


                if(knownWorld[tempLocation].hasContent(ContentType::Unknown)&& return_journy )
                {
                    newMapData=true;
                }

                std::vector<Content> temp_contnet= trueWorld[trueLocation].getContent();
                //std::cout<<temp.size()<<std::endl;
                for(int x=0; x< temp_contnet.size(); x++)
                {
                    knownWorld[tempLocation].addContent(temp_contnet[x]);
                }



                if(!knownWorld[tempLocation].hasContent(ContentType::Object))
                {
                    //cout<<"explore further"<<tempLocation<<endl;
                    Agent::lookAround(tempLocation); //By having the this lookAround run again, we dont see more of the world. We just expand the grid more. This lets the robot know there is more "just beyound the river bend"
                }


            }
            catch(std::out_of_range r)
            {
                // cout<<"world end"<<tempLocation<<endl;
                knownWorld[tempLocation].addContent(ContentType::Jormungandr_Wall);

            }


        }
    }
  if (newMapData)
  {
      if(DeploymentMethod==4||DeploymentMethod==7)
        {
            Replan(false);
        }
    else if(DeploymentMethod==5||DeploymentMethod==8)
        {
            Replan(true);
        }
  }


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
    //cout<<"low sign at "<<CurrentLocation<<" "<<(CurrentLocationtemp.getRow()+trueLocationRelativity.getRow())<<" "<<(CurrentLocationtemp.getColumn()+trueLocationRelativity.getColumn())<<endl;
    vector<Relay*> gridRelays = trueWorld.getRelays();
    bool poor_range =true;
    for(int i =0; i< gridRelays.size(); i++)
    {
       // cout<<"relay"<<i;
        try{
        if(gridRelays[i]->inRange(CurrentLocationtemp+trueLocationRelativity) )
            poor_range=false;
        }catch(std::out_of_range){}
    }
    //cout<<poor_range<<endl;
    return poor_range;
}



