#ifndef SIMULATIONREADIN_H
#define SIMULATIONREADIN_H
#include "Agent.h"


namespace Agentspace{

class SimulationAgent: public Agent
{

public:

	bool done();
	void setRelayCount(int numberofRelays);
	void addRange(int range);

void findPath();



	Grid trueWorld; //the simulator is a slut, and it dont give no shits if everyone sees it grids

	void lookAround(); //make private later
    inline void setRelativity(Coordinate _trueLocationRelativity){trueLocationRelativity=RelativeCoordinate(_trueLocationRelativity.getRow(), _trueLocationRelativity.getColumn());}
    void ShuffleLoctions(int row, int column);
    void evaluateRealayRange();


private:

	bool move(Node::Direction toMove);
	bool lowSignal(Coordinate CurrentLocationtemp);
	void PlaceRelay(int ID, Coordinate whereToPlace);
	void PickupRelay(int ID, Coordinate whereToTake);

	RelativeCoordinate trueLocationRelativity;


};
}

#endif
