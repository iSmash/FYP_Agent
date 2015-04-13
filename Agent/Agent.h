 #ifndef AGENT_H
#define AGENT_H

using namespace std;
namespace Agent{
	class Agent{
		private:
			Node* endofRunLocation;

		protected:
			Grid KnownWorld;
			vector<Relay> heldRelays; //relays held on the robot, moved to grid's vector of relays when deployed.
	};
}
#endif
