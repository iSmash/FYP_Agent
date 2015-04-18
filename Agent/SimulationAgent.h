 #ifndef SIMULATIONREADIN_H
#define SIMULATIONREADIN_H
#include "Agent.h"
#include "../GUI/GridGUI.h"

namespace Agentspace{

	class SimulationAgent: public Agent
	{

		public:
        SimulationAgent(): Agent()
        {


        }
		    bool done();
			void setRelayCount(int numberofRelays);
			void addRange(int range);

			Grid trueworld; //the simulator is a slut, and it dont give no shits if everyone sees it grids

            inline void setTrueCurrentLocation(Coordinate toset){trueCurrentLocation=toset;}

 void lookAround(); //make private later
		private:
            void move(Direction toMove);

            Coordinate trueCurrentLocation;


	};
}

#endif
