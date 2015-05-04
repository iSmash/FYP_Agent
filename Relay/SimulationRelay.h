#ifndef SIMULATIONRELAY_H
 #define SIMULATIONRELAY_H
#include <vector>
#include "Relay.h"

namespace Relayspace
{
	class SimulationRelay : public Relay
	{
		public:

		    SimulationRelay():Relay()
            {Ranges.push_back(0);
            activeRange=0;
            }

        inline void updatePos(Coordinate pos){ gridLocation= pos; findDomain();}

			inline void addRange(int add){Ranges.push_back(add);}
			void findDomain();

			void setRange(int range);
            bool inRange(Coordinate test);
		private:
			std::vector<int> Ranges;
			int activeRange;

			std::vector<Coordinate> domain;
	};

}

#endif
