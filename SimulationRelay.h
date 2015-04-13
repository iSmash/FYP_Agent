#ifndef RELAY_H
 #define RELAY_H

#include "Relay.h"

namespace Relay
{
	class SimulationRelay : protected shape
	{
		public:
			inline void addRange(int add){Ranges.push_back(add);}
std::vector<Coordinate> domain();
		private:
			std::vector<int> Ranges;
	}
	
}

#endif
