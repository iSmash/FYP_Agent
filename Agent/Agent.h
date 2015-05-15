#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include "PathPlan.h"
#include "../Relay/Relay.h"
#include "../Grid/Grid.h"
#include "Deployment.h"

using namespace environment;
using namespace std;
using namespace Relayspace;
namespace Agentspace
{
class Agent
{
public:
    virtual bool done()=0;

    Agent()
    {
        CurrentLocation=Coordinate(0,0);
        BaseLocation= CurrentLocation;
        knownWorld.updateSize(Coordinate(1,1));
        step_count=0;
    }

     void findPath();

    void tryPath();

    virtual void setRelayCount(int numberofRelays)=0; //same, but makes either implemnet, or simulation relays.
    Relay* GetRelay(int _ID);
    vector<Relay*> getRelays()
    {
        return heldRelays;   //namechange for error provension? na, english language hey bruz
    }
    void RemoveRelay(int _ID);

    inline Grid &getKnownGrid()
    {
        return knownWorld;
    }

    void setGoal(RelativeCoordinate relativeToGoal);/**using magic we find where the goal is */

    void updateGoal();

    inline void defineDeploymentMethod(int meth)
    {
        DeploymentMethod=meth;
    }
    inline int getDeploymentMethod()
    {
        return DeploymentMethod;
    }

    virtual void evaluateRealayRange()=0;

    inline int Get_stepcount(){return step_count;}
protected:
    virtual bool lowSignal()=0;
    virtual bool move(Node::Direction toMove);
    virtual void lookAround();
   virtual void ShuffleLoctions(int row, int column);

  virtual  void PlaceRelay(int ID,Coordinate whereToPlace);
  virtual  void PickupRelay(int ID,Coordinate PickFrom);

    Coordinate CurrentLocation;
    vector<Coordinate> GoalLocation;
    Coordinate ClientLocation;
    Coordinate BaseLocation;
    vector<Node::Direction> actionList;
    PathPlan planner;
    Grid knownWorld;
    vector<Relay*> heldRelays; //relays held on the robot, moved to grid's vector of relays when deployed.
    int DeploymentMethod;
    DeploymentSpace::Deployment relayPlace;
    int step_count;

};
}
#endif
