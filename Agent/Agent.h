 #ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include "PathPlan.h"
#include "../Relay/Relay.h"
#include "../Grid/Grid.h"

using namespace environment;
using namespace std;
using namespace Relayspace;
namespace Agentspace{
	class Agent{
		public:
			virtual bool done()=0;


            Agent(){endofRunLocation=Coordinate(0,0);}
			inline void findPath(Coordinate goal)
			{
                KnownWorld[endofRunLocation].setViewed(true);
                endofRunLocation = planner.findPath(goal);
			}
			void tryPath();

			virtual void setRelayCount(int numberofRelays)=0; //same, but makes either implemnet, or simulation relays.
			Relay* getRelay(int _ID);
			vector<Relay*> getRelays() {return heldRelays;} //namechange for error provension? na



		protected:
			enum Direction {North, East, South, West};
			virtual void move(Direction toMove)=0;

			void PlaceRelay(int ID, Coordinate whereToPlace);
			void PickupRelay(int ID);

			Coordinate endofRunLocation;
			PathPlan planner;
			Grid KnownWorld;
			vector<Relay*> heldRelays; //relays held on the robot, moved to grid's vector of relays when deployed.


	};
}
#endif
