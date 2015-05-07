#ifndef IMPLAMENTAGENT_H
#define IMPLAMENTAGENT_H
#include "Agent.h"

namespace Agentspace{

class ImplementAgent: public Agent
{
public:
	inline bool done();

	void setRelayCount(int numberofRelays);

	bool inRange(Coordinate test);

private:
	inline void PlaceRelay(int _ID, Coordinate whereToPlace){
		//physical shit;
		Agent::PlaceRelay(_ID,whereToPlace);
	}
	inline void PickupRelay(int ID){
		//physical shit;
		//Agent::PickupRelay(ID);
	}

	bool move(Node::Direction toMove);
	void lookAround();
    bool lowSignal();
};
}
#endif
