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
		private:
            void move(Direction toMove);
	};
}

#endif
