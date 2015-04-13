#ifndef RELAY_H
 #define RELAY_H
#include "coordinate.h"
using namespace environment;

namespace Relay
{
	int ID_Count=0;
	class Relay
	{
		public:
			Relay();
			inline int getID(){return ID;}

		inline void updatePos(Coordinate pos) {gridLocation= pos;}
			inline Coordinate getPos(){return gridLocation;}

		   bool inRange(Coordinate test);
		protected:
			int ID;	
			Coordinate gridLocation; //when held by robot this should be null;	
	}
}

#endif
