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
         temp->setRange(1);
     }
     for(int i=0; i<KnownWorld.getRelays().size(); i++)
     {
         SimulationRelay* temp= (SimulationRelay*)KnownWorld.getRelays()[i];
         temp->addRange(range);
         temp->setRange(1);
     }


 }

void SimulationAgent::PlaceRelay(int ID, Coordinate whereToPlaceKnown, Coordinate whereToPlacetrue)
{
   Relay* tobePlaced = NULL;
	for(int i=0; i< heldRelays.size(); i++)
	{
		if(heldRelays[i]->getID()== ID)
		{
			tobePlaced=heldRelays[i];
			heldRelays.erase(heldRelays.begin()+i);
			break;
		}
	}
	if (tobePlaced==NULL)
		throw(RelayError());

	tobePlaced->updatePos(whereToPlacetrue);
	trueworld.placeRelay(tobePlaced);
	trueworld[whereToPlacetrue].addContent(ContentType::RelayMarker);
	Agent::PlaceRelay(whereToPlaceKnown);
}

void SimulationAgent::PickupRelay(int ID, Coordinate whereToTake)
{
    cout<<"pickup2"<<endl;
	trueworld[whereToTake].removeContent(ContentType::RelayMarker);
heldRelays.push_back(KnownWorld.getRelay(ID));
	KnownWorld.removeRelay(ID);

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
   try{        //std::cout<<i<<" "<<j<<std::endl;
        std::vector<Content> temp= trueworld[Coordinate(trueCurrentLocation.getRow()+i, trueCurrentLocation.getColumn()+j)].getContent();
  //std::cout<<temp.size()<<std::endl;
    for(int x=0; x< temp.size(); x++)
    {
        KnownWorld[Coordinate(CurrentLocation.getRow()+i, CurrentLocation.getColumn()+j)].addContent(temp[x]);
    }
   }
   catch(std::out_of_range r){}
 }}

/*
     //above
 try{
 if(CurrentLocation.getRow()-1==0 && !(KnownWorld[Coordinate(CurrentLocation.getRow()-1, CurrentLocation.getColumn())].hasContent(ContentType::Boarder)))
    {
        std::cout<<"ex above"<<std::endl;
        KnownWorld.updateSize(Grid::top);
        CurrentLocation=Coordinate(CurrentLocation.getRow()+1, CurrentLocation.getColumn());
        }
 }
catch(std::out_of_range r){}

     //bot
 try{
 if(CurrentLocation.getRow()+1==KnownWorld.getLast().getRow() && !(KnownWorld[Coordinate(CurrentLocation.getRow()+1, CurrentLocation.getColumn())].hasContent(ContentType::Boarder)))
    {KnownWorld.updateSize(Grid::bottom);
    std::cout<<"ex below"<<std::endl;}
 }
catch(std::out_of_range r){}

     //left
 try{
 if(CurrentLocation.getColumn()-1==0 && !(KnownWorld[Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()-1)].hasContent(ContentType::Boarder)))
    {
        KnownWorld.updateSize(Grid::left);
        std::cout<<"ex left"<<std::endl;
         CurrentLocation=Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()+1);
        }
 }
catch(std::out_of_range r){}

     //right
 try{
 if(CurrentLocation.getColumn()+1==KnownWorld.getLast().getColumn() && !(KnownWorld[Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()+1)].hasContent(ContentType::Boarder)))
    {
        std::cout<<"ex right"<<std::endl;
        KnownWorld.updateSize(Grid::right);
        }
 }
catch(std::out_of_range r){}
*/

 }



 bool SimulationAgent::move(Node::Direction toMove)
 {

         Coordinate CurrentLocationtemp, trueCurrentLocationtemp;
         Coordinate OldPosknown = CurrentLocation; //for backtrack in method one
           Coordinate OldPosTrue = trueCurrentLocation; //for backtrack in method one
     switch (toMove)
     {
     case Node::Right:
         CurrentLocationtemp = Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()+1);
         trueCurrentLocationtemp = Coordinate(trueCurrentLocation.getRow(), trueCurrentLocation.getColumn()+1);

        break;
     case Node::Left:
         CurrentLocationtemp = Coordinate(CurrentLocation.getRow(), CurrentLocation.getColumn()-1);
         trueCurrentLocationtemp = Coordinate(trueCurrentLocation.getRow(), trueCurrentLocation.getColumn()-1);
        break;
     case Node::Up:
         CurrentLocationtemp = Coordinate(CurrentLocation.getRow()-1, CurrentLocation.getColumn());
         trueCurrentLocationtemp = Coordinate(trueCurrentLocation.getRow()-1, trueCurrentLocation.getColumn());
        break;
     case Node::Down:
         CurrentLocationtemp = Coordinate(CurrentLocation.getRow()+1, CurrentLocation.getColumn());
         trueCurrentLocationtemp = Coordinate(trueCurrentLocation.getRow()+1, trueCurrentLocation.getColumn());
        break;
     case Node::Root:

        return true;
        break;
     }

     if(KnownWorld[CurrentLocationtemp].hasContent(ContentType::Wall))
     {
         //bad move
         return false;
     }


        CurrentLocation=CurrentLocationtemp;
        trueCurrentLocation=trueCurrentLocationtemp;




        if(DeploymentMethod==1 && lowSignal()) //find out if need to place a new node donw
        {

            try{PlaceRelay(heldRelays.front()->getID(),OldPosknown,OldPosTrue);}
            catch(RelayError e){//cout<<"out of relays"<<endl;
            }
        }


        trueworld[trueCurrentLocation].addContent(ContentType::Robot);
         lookAround();

        return true;
}

 bool SimulationAgent::done()
 {
    if(KnownWorld[CurrentLocation].hasContent(ContentType::Goal))
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
        if(gridRelays[i]->inRange(trueCurrentLocation) )
            poor_range=false;
    }
    return poor_range;
}
