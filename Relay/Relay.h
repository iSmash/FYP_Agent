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

		  virtual bool inRange(Coordinate test);
		protected:
			int ID;	
			Coordinate gridLocation; //when held by robot this should be null;	
	};


//snuk this in the same file, coz its not worth its own, special exeption if something goes wrong with relay
class RelayError: public std::exception
{
		public: 
			virtual const char* what() const throw()
	{
		return "Relay error";
	}
}

}

#endif
