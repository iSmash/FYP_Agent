#ifndef IMPLAMENTAGENT_H
#define IMPLAMENTAGENT_H
#include "Agent.h"
#include "../iRobotControl.h"
#include "../GUI/GridGUI.h"

namespace Agentspace{

class ImplementAgent: public Agent
{
public:
    ImplementAgent(char* ControlPort);

	inline bool done();

	void setRelayCount(int numberofRelays);
    void tryPath();

	bool inRange(Coordinate test);
    inline void giveGUI(GridGUI* _GUI){GUI=_GUI;}

private:

	inline void PlaceRelay(int _ID, Coordinate whereToPlace){
		//physical shit;
		Agent::PlaceRelay(_ID,whereToPlace);
	}
	inline void PickupRelay(int ID){
		//physical shit;
		//Agent::PickupRelay(ID);
	}
    void AdjustAngle(int newAngle);
	bool move(Node::Direction toMove);
	void lookAround();
    bool lowSignal(Coordinate CurrentLocationtemp);
    void evaluateRealayRange();
    iRobotControl iRobot_Control;
    int currentAngle;
    GridGUI* GUI;
};
}
#endif
