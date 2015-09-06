#include <iostream>
#include "Agent.h"

using namespace Agentspace;
using namespace Relayspace;
using namespace std;
Coordinate Agent::CurrentLocation =Coordinate(0,0);

int findFailCount=0;
void Agent::findPath()
{
    std::cout<<"current"<<CurrentLocation<<std::endl;
    std::cout<<"goal"<<GoalLocation.front()<<std::endl;
    bool success=false;



    knownWorld[CurrentLocation].setViewed(true);
    try
    {

         actionList = planner.findPath(CurrentLocation, GoalLocation,knownWorld);
        findFailCount=0;
    }
    catch(string &s)
    {
        findFailCount++;
        if(findFailCount>10)
        {
            throw string("failed to find path");
        }
        //cout<<s;
        // cout<<"Last"<<knownWorld.getLast()<<endl;
         //cout<<"cur"<<CurrentLocation<<endl;
         //cout<<"goal"<<GoalLocation.back()<<endl;
         //cout<<"cli"<<ClientLocation<<endl;
        // cout<<"base"<<BaseLocation<<endl;*/
         //for(int testloop=0; testloop<GoalLocation.size(); testloop++)
         //{cout<<GoalLocation[testloop]<<endl;}
        knownWorld.updateSize(Grid::right);
        knownWorld.updateSize(Grid::bottom);
        if(knownWorld.updateSize(Grid::top))
            ShuffleLoctions(1,0);
        if(knownWorld.updateSize(Grid::left))
            ShuffleLoctions(0,1);
//    int a; cin>>a;

        throw 1; //soft throw, will retry
    }

    tryPath();
}

void Agent::tryPath()
{
    //std::cout<<"Path is"<<std::endl;

    while(actionList.size()!=0)
    {

        Node::printDirection(actionList.back());
        if(!move(actionList.back()))
        {
        //cout<<"but not"; Node::printDirection(actionList.back());
        //int a; cin>>a;
        break;

        }
        //else{ Node::printDirection(actionList.back());}

        actionList.pop_back();
        knownWorld[CurrentLocation].addContent(ContentType::Robot);
    }


    //clean up old search


    //cout<<endl;
}

void Agent::updateGoal(bool all)
{
    //cout<<"update goals";
return_journy=true;

 if(DeploymentMethod==2)
    {

        GoalLocation.clear();
        GoalLocation.push_back(BaseLocation);
        knownWorld[BaseLocation].addContent(ContentType::Goal);
        evaluateRealayRange();
        // cout<<"client found, now going to "<<BaseLocation<<GoalLocation.size()<<endl;
        return;
    }
    //at clinet, now set where relays should place.


    /*for(int i =0; i< GoalLocation.size(); i++)
    {
        cout<<GoalLocation[i]<<endl;
    }*/
   //cout<<"relays to deply "<<heldRelays.size()<<endl;
   bool valid;
  do
   {
       valid=true;
       if(all)
       {
           GoalLocation = relayPlace.positionRelays(DeploymentMethod, fullRelayCount, BaseLocation, ClientLocation, knownWorld);
       }
       else
        {
            GoalLocation = relayPlace.positionRelays(DeploymentMethod, heldRelays.size(), BaseLocation, ClientLocation, knownWorld);
        }


    vector<Coordinate>::iterator tempGoalLocation = GoalLocation.begin();
    while(tempGoalLocation!= GoalLocation.end())
    {
        //cout<<"goal locations at" ;
        //cout<<*tempGoalLocation<<endl;

         if(knownWorld[*tempGoalLocation].hasContent(ContentType::Unknown))
        {
            //cout<<"Reverse Explore"<<endl;
            if(!planner.Explore_Unkown(*tempGoalLocation, knownWorld))
            {
               // cout<<"bad Goal Location"<<endl;
                relayPlace.addBadGoal(*tempGoalLocation);
                valid=false;
                break;
            }
           //else{cout<<"OK goal loaction"<<endl;}
        }
           tempGoalLocation++;

    }
   } while(!valid);

    vector<Coordinate>::iterator tempGoalLocation = GoalLocation.begin();
    while(tempGoalLocation!= GoalLocation.end())
    {
         if(knownWorld[*tempGoalLocation].hasContent(ContentType::Goal))
        {
            cout<<"Goal overlap"<<*tempGoalLocation<<endl;
//            int a; cin>>a;
            GoalLocation.erase(tempGoalLocation);
        }
        else
        {
            knownWorld[*tempGoalLocation].addContent(ContentType::Goal);
            tempGoalLocation++;
        }
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

    //cout<<whereToPlace<<endl;
    knownWorld[whereToPlace].addContent(ContentType::RelayMarker);
}

void Agent::PickupRelay(Coordinate PickFrom)
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
        //cout<<"up add"<<endl;
    }

    //look down
    if(lookFrom.getRow()>=knownWorld.getLast().getRow()-1)
    {
        //as top as can be, so lets make more world
       // std::cout<<"bot "<<knownWorld.getLast();
        knownWorld.updateSize(Grid::bottom);
       //  std::cout<<"bot "<<knownWorld.getLast();
       //cout<<"down add"<<endl;
    }



    //look right
    if(lookFrom.getColumn()>=knownWorld.getLast().getColumn()-1)
    {
        //as top as can be, so lets make more world
        //std::cout<<"right ";
        knownWorld.updateSize(Grid::right);
        //cout<<"right add"<<endl;
    }

    //look left
    if(lookFrom.getColumn()==0)
    {
        //as top as can be, so lets make more world
        // std::cout<<"left ";
        knownWorld.updateSize(Grid::left);
        //as we are push above the grid, we need to move down our knonw position

        ShuffleLoctions(0,1);
        //cout<<"left add"<<endl;
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
    cout<<relativeToGoal<<endl;
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


//cout<<"move"<<endl;
    if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Client))
    {
      //  cout<<"Client"<<endl;
        if(!knownWorld[CurrentLocationtemp].removeContent(ContentType::Goal))
       {
           cout<<"Client:Failied to remove goal state"<<endl;
//           int a; cin>>a;
       }
        updateGoal();
    }

    if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Goal) && DeploymentMethod>2 )
    {


       if(!knownWorld[CurrentLocationtemp].removeContent(ContentType::Goal))
       {
           cout<<"Failied to remove goal state"<<endl;

       }

        for(int i =0; i< GoalLocation.size(); i++)
        {
            if(GoalLocation[i]==CurrentLocationtemp)
                GoalLocation.erase(GoalLocation.begin()+i);
        }


        if(knownWorld[CurrentLocationtemp].hasContent(ContentType::RelayMarker))
        {
            try
            {
                //cout<<"pickup"<<endl;
                PickupRelay(CurrentLocationtemp);
            }
            catch(RelayError e) //cout<<"out of relays"<<endl;
            {
            }
        }
        else
        {
            try
            {
                if(!knownWorld[CurrentLocationtemp].hasContent(ContentType::Deployment_Object))
                {
                    PlaceRelay(heldRelays.front()->getID(),CurrentLocationtemp);
                }
            }
            catch(RelayError e) //cout<<"out of relays"<<endl;
            {
            }
        }


    }


    if(knownWorld[CurrentLocationtemp].hasContent(ContentType::Object) )
    {
        //bad move
        cout<<"Object in agent move"<<endl;
        return false; //last because most of the above will trigger
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
        if(heldRelays.size()==0)
        {
            if(!knownWorld[GoalLocation.back()].removeContent(ContentType::Goal))
            {
                cout<<"Failied to remove goal state"<<endl;
            }
            GoalLocation.pop_back();
            return false;
        }
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


void Agent::Replan(bool all)
{
   // cout<<"Replan future relays"<<CurrentLocation<<endl;
    for(int i =0; i< GoalLocation.size(); i++)
    {
        //cout<<"Goal location"<<GoalLocation[i]<<endl;
        if(!knownWorld[GoalLocation[i]].removeContent(ContentType::Goal))
       {
           NULL;
           //cout<<"Failied to remove goal state"<<GoalLocation[i]<<endl;

       }

    }



    GoalLocation.clear();


  updateGoal(all);
  if(all)
  {
     vector<Coordinate> tempGoalLocation;
     // cout<<"Find relays to pick back up"<<endl;
      for(int row=0; row<knownWorld.getLast().getRow(); row++)
      {
        for(int col=0; col<knownWorld.getLast().getColumn(); col++)
        {
              Coordinate current =Coordinate(row,col);
              if(knownWorld[current].hasContent(ContentType::RelayMarker) && !knownWorld[current].hasContent(ContentType::Goal))
              {
                 // cout<<current<<" Nolonger valid position for realy"<<endl;
                  tempGoalLocation.push_back(current);


              }
        }
      }

      //remomve any goals that are requsting placemtn of relay where relay is.
     // cout<<"Remove unneeded goals"<<endl;
      std::vector<Coordinate>::iterator goalIter= GoalLocation.begin();

      while(goalIter!= GoalLocation.end())
    {
        //cout<<"Goal location"<<*goalIter<<endl;
        if(knownWorld[*goalIter].hasContent(ContentType::RelayMarker))
       {
           // cout<<"unNeeded"<<endl;
            knownWorld[*goalIter].removeContent(ContentType::Goal);
           GoalLocation.erase(goalIter);

       }
       else
        {
            goalIter++;
        }
    }
    for(int i=0; i<tempGoalLocation.size(); i++)
    {
        GoalLocation.push_back(tempGoalLocation[i]);
        knownWorld[tempGoalLocation[i]].addContent(ContentType::Goal);
    }

  }

}




