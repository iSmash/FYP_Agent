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
        BaseLocation= CurrentLocation;
        knownWorld.updateSize(Coordinate(1,1));
        step_count=0;
        return_journy=false;
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

    virtual void updateGoal(bool all=false);

    void defineDeploymentMethod(int meth);

    inline int getDeploymentMethod()
    {
        return DeploymentMethod;
    }

    virtual void evaluateRealayRange()=0;

    inline int Get_stepcount(){return step_count;}

    void SaveGrid();

protected:
void Replan(bool all);

    virtual bool lowSignal(Coordinate CurrentLocationtemp)=0;
    virtual bool move(Node::Direction toMove);
    virtual void lookAround(Coordinate lookFrom=CurrentLocation);
   virtual void ShuffleLoctions(int row, int column);

  virtual  void PlaceRelay(int ID,Coordinate whereToPlace);
  virtual  void PickupRelay(Coordinate PickFrom);

static   Coordinate CurrentLocation;
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
    int fullRelayCount;
    bool return_journy;

};
}
#endif
