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
            inline std::vector<Coordinate> getDomain(){return domain;}

			void setRange(int range);
            bool inRange(Coordinate test);

           	bool OnNetwork;//setters and getter would give full access anyway, so fuck it, this is public
		private:
			std::vector<int> Ranges;
			int activeRange;

			std::vector<Coordinate> domain;

	};

}

#endif
