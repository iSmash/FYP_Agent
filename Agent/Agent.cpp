#include <iostream>
#include "Agent.h"

using namespace Agentspace;
using namespace Relayspace;
using namespace std;
Coordinate Agent::CurrentLocation =Coordinate(0,0);
void printDirection2(Node::Direction toprint)
{
    switch(toprint)
    {
    case Node::Right:
        cout<<"Right; ";
        break;
    case Node::Left:
        cout<<"Left; ";
        break;
    case Node::Up:
        cout<<"Up; ";
        break;
    case Node::Down:
        cout<<"Down; ";
        break;
    case Node::UpRight:
        cout<<"Up-Right; ";
        break;
    case Node::UpLeft:
        cout<<"Up-Left; ";
        break;
    case Node::DownLeft:
        cout<<"Down-Left; ";
        break;
    case Node::DownRight:
        cout<<"Down-Right; ";
        break;
    case Node::Root:
        cout<<"Start;";
        break;
    }
}

void Agent::findPath()
{
    //std::cout<<"current"<<CurrentLocation<<std::endl;
    //std::cout<<"goal"<<GoalLocation.front()<<std::endl;
    bool success=false;



    knownWorld[CurrentLocation].setViewed(true);
    try
    {

         actionList = planner.findPath(CurrentLocation, GoalLocation,knownWorld);
    }
    catch(string &s)
    {
        //cout<<s;
        /* cout<<"Last"<<knownWorld.getLast()<<endl;
         cout<<"cur"<<CurrentLocation<<endl;
         cout<<"goal"<<GoalLocation.back()<<endl;
         cout<<"cli"<<ClientLocation<<endl;
         cout<<"base"<<BaseLocation<<endl;*/
        knownWorld.updateSize(Grid::right);
        knownWorld.updateSize(Grid::bottom);
        if(knownWorld.updateSize(Grid::top))
            ShuffleLoctions(1,0);
        if(knownWorld.updateSize(Grid::left))
            ShuffleLoctions(0,1);

        knownWorld.clearGridViewed();

        throw 1; //soft throw, will retry
    }

    tryPath();
}

void Agent::tryPath()
{
    //std::cout<<"Path is"<<std::endl;

    while(actionList.size()!=0)
    {
        //printDirection2(actionList.back());

        if(!move(actionList.back()))
            break;

        actionList.pop_back();
        knownWorld[CurrentLocation].addContent(ContentType::Robot);
    }


    //clean up old search
    knownWorld.clearGridViewed();
    planner.clear();
    //cout<<endl;
}

void Agent::updateGoal()
{
    //cout<<"update goals";

    //at clinet, now set where relays should place.
    knownWorld[GoalLocation.back()].removeContent(ContentType::Goal);

    /*for(int i =0; i< GoalLocation.size(); i++)
    {
        cout<<GoalLocation[i]<<endl;
    }*/

    GoalLocation = relayPlace.positionRelays(DeploymentMethod, heldRelays.size(), BaseLocation, ClientLocation, knownWorld);


    for(int i=0; i<GoalLocation.size(); i++)
    {
        cout<<"goal locations at" ;
        cout<<GoalLocation[i]<<endl;
        if(knownWorld[GoalLocation[i]].hasContent(ContentType::Goal))
        {
            cout<<"Goal overlap"<<endl;
            GoalLocation.erase(GoalLocation.begin()+i);
        }
        else
             knownWorld[GoalLocation[i]].addContent(ContentType::Goal);

    }

     if(DeploymentMethod==2)
    {

        return_journy=true;
        GoalLocation.push_back(BaseLocation);
        knownWorld[BaseLocation].addContent(ContentType::Goal);
        evaluateRealayRange();
        // cout<<"client found, now going to "<<BaseLocation<<GoalLocation.size()<<endl;
    }



}


Relay* Agent::GetRelay(int _ID)
{
    for(int i=0; i< heldRelays.size(); i++)
    {
        if(heldRelays[i]->getID()== _ID)
            return heldRelays[i];
    }
    //cout<<"failed to find relay"<<endl;
    return NULL;
}

void Agent::RemoveRelay(int _ID)
{
    for(int i=0; i< heldRelays.size(); i++)
    {
        if(heldRelays[i]->getID()== _ID)
            heldRelays.erase(heldRelays.begin()+i);
    }
}

void Agent::PlaceRelay(int ID,Coordinate whereToPlace)
{
    //Relay* tobePlaced = GetRelay(ID);
    // if(tobePlaced == NULL)
    //    return; //out of nodes.

    //knownWorld.placeRelay(tobePlaced);


    knownWorld[whereToPlace].addContent(ContentType::RelayMarker);
}

void Agent::PickupRelay(int ID,Coordinate PickFrom)
{
    knownWorld[PickFrom].removeContent(ContentType::RelayMarker);

}

// TODO 20150505 does this need to be expanded for new diagonal movement? I think not..
void Agent::lookAround(Coordinate lookFrom)
{
    //look up

    if(lookFrom.getRow()==0)
    {
        //as top as can be, so lets make more world
        //std::cout<<"top ";
        knownWorld.updateSize(Grid::top);
        //as we are push above the grid, we need to move down our knonw position
        ShuffleLoctions(1,0);
    }

    //look down
    if(lookFrom.getRow()>=knownWorld.getLast().getRow()-1)
    {
        //as top as can be, so lets make more world
       // std::cout<<"bot "<<knownWorld.getLast();
        knownWorld.updateSize(Grid::bottom);
       //  std::cout<<"bot "<<knownWorld.getLast();
    }



    //look right
    if(lookFrom.getColumn()>=knownWorld.getLast().getColumn()-1)
    {
        //as top as can be, so lets make more world
        //std::cout<<"right ";
        knownWorld.updateSize(Grid::right);
    }

    //look left
    if(lookFrom.getColumn()==0)
    {
        //as top as can be, so lets make more world
        // std::cout<<"left ";
        knownWorld.updateSize(Grid::left);
        //as we are push above the grid, we need to move down our knonw position

        ShuffleLoctions(0,1);
    }



}

void Agent::ShuffleLoctions(int row, int column)
{
//cout<<"base suffle"<<endl;
    CurrentLocation=Coordinate(CurrentLocation.getRow()+row, CurrentLocation.getColumn()+column);
    for(int i=0; i< GoalLocation.size(); i++)
        GoalLocation[i]=Coordinate(GoalLocation[i].getRow()+row, GoalLocation[i].getColumn()+column);
    BaseLocation=Coordinate(BaseLocation.getRow()+row, BaseLocation.getColumn()+column);
    ClientLocation=Coordinate(ClientLocation.getRow()+row, ClientLocation.getColumn()+column);
    for(int i=0; i<knownWorld.getRelays().size(); i++)
    {
        knownWorld.getRelays()[i]->updatePos(Coordinate(knownWorld.getRelays()[i]->getPos().getRow(),knownWorld.getRelays()[i]->getPos().getColumn()));
    }
}




void Agent::setGoal(RelativeCoordinate relativeToGoal)
{
    /**using magic we find where the goal is */

    Grid::updateSizeDirection direcion;
    if(relativeToGoal.getRow()<0)
    {
        for(int i =0; i< abs(relativeToGoal.getRow()); i++)
        {
            knownWorld.updateSize(Grid::top);
            ShuffleLoctions(1,0);

        }
    }
    else
    {
        for(int i =0; i< abs(relativeToGoal.getRow()); i++)
        {

            knownWorld.updateSize(Grid::bottom);
        }
    }


    if(relativeToGoal.getColumn()<0)
    {
        //add up

        for(int i =0; i< abs(relativeToGoal.getColumn()); i++)
        {

            knownWorld.updateSize(Grid::left);
            ShuffleLoctions(0,1);

        }
    }
    else
    {
        for(int i =0; i< abs(relativeToGoal.getColumn()); i++)
        {
            knownWorld.updateSize(Grid::right);
        }
    }



    ClientLocation = CurrentLocation+relativeToGoal;
    GoalLocation.push_back(ClientLocation);
    //cout<<"C"<<CurrentLocation<<endl;
    //cout<<"G"<<GoalLocation<<endl;
    knownWorld[GoalLocation.back()].addContent(ContentType::Goal);

}
bool Agent::move(Node::Direction toMove)
{
     //std::cout<<"move"<<std::endl;
    Coordinate CurrentLocationtemp;
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

    }


    if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Client))
    {
        updateGoal();
    }

    if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Goal) && DeploymentMethod>2)
    {

        GoalLocation.pop_back();
        try
        {
            PlaceRelay(heldRelays.front()->getID(),CurrentLocationtemp);
        }
        catch(RelayError e) //cout<<"out of relays"<<endl;
        {
        }

    }

    if( (DeploymentMethod<=1 ||( DeploymentMethod==2 && return_journy ))   && lowSignal(CurrentLocationtemp) ) //find out if need to place a new node donw
    {
        try
        {
            PlaceRelay(heldRelays.front()->getID(),CurrentLocation);
        }
        catch(RelayError e) //cout<<"out of relays"<<endl;
        {
        }
    }

    if(DeploymentMethod==2 && return_journy && CurrentLocationtemp==BaseLocation)
    {
        GoalLocation.pop_back();
    }

    if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Object) )
    {
        //bad move
        return false; //last because most of the above will trigger
    }

    CurrentLocation=CurrentLocationtemp;
    step_count++;
    return true;
}

void Agent::defineDeploymentMethod(int meth)
{
    DeploymentMethod=meth;

    if(DeploymentMethod==1)
    {
        evaluateRealayRange();
    }

}


