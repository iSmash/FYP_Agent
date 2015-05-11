#ifndef SIMULATIONRELAY_H
 #define SIMULATIONRELAY_H
#include <vector>
#include "Relay.h"
#include "../Grid/Grid.h"

namespace Relayspace
{
	class SimulationRelay : public Relay
	{
		public:

		    SimulationRelay(Grid* _trueWorld):Relay()
            {
            trueWorld=_trueWorld;
            }

        inline void updatePos(Coordinate pos){ gridLocation= pos; findDomain();}

			inline static void addRange(int add){Ranges.push_back(add);}
			void findDomain();
            inline std::vector<Coordinate> getDomain(){return domain;}

            static void  incRange();
			static void  decRange();
            bool inRange(Coordinate test);
            inline static int getRange(){return Ranges[activeRange];}

		private:
			static std::vector<int> Ranges;
			static int activeRange;
			 Grid* trueWorld;
			std::vector<Coordinate> domain;

	};

}

#endif
