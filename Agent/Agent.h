 #ifndef AGENT_H
#define AGENT_H

using namespace std;
namespace Agent{
	class Agent{
		public:
			virtual bool done();
			
			inline void findPath(Coordinate goal){endofRunLocation = planner.findPath(goal);}
			void tryPath();
			
			virtual void setRelayCount(int numberofRelays); //same, but makes either implemnet, or simulation relays.
			Relay getRelay(int _ID);
			vector<Relay> getRelays(); //namechange for error provension? na
				
		protected:
			enum Direction {North, East, South, West};
			virtual void move(Direction toMove);
			
			void PlaceRelay(int _ID);
			void PickupRelay(Relay toAdd);	
			
			Node* endofRunLocation;
			PathPlan planner;		
			Grid KnownWorld;
			vector<Relay> heldRelays; //relays held on the robot, moved to grid's vector of relays when deployed.
			
		
	};
}
#endif
