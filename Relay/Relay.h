#ifndef RELAY_H
#define RELAY_H
#include "../Grid/Coordinate.h"
#include <exception>
#include <iostream>
using namespace environment;

namespace Relayspace
{

class Relay
{
public:
	Relay(){ID=ID_Count++;}
	inline int getID(){return ID;}

	inline void updatePos(Coordinate pos){gridLocation= pos;}
	inline Coordinate getPos(){return gridLocation;}

	virtual bool inRange(Coordinate test)=0;

protected:
	int ID;
	Coordinate gridLocation; //when held by robot this should be null;

private:
	static int ID_Count;
};


//snuk this in the same file, coz its not worth its own, special exeption if something goes wrong with relay
class RelayError: public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Relay error: ";
	}
};

}

#endif
