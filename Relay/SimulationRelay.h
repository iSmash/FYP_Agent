#ifndef SIMULATIONRELAY_H
 #define SIMULATIONRELAY_H
#include <vector>
#include "Relay.h"

namespace Relayspace
{
	class SimulationRelay : public Relay
	{
		public:
			inline void addRange(int add){Ranges.push_back(add);}
			std::vector<Coordinate> domain();

			inline void setRange(int range){if(range>=0 && range<Ranges.size()) activeRange=range;}
            bool inRange(Coordinate test);
		private:
			std::vector<int> Ranges;
			int activeRange;
	};

}

#endif
