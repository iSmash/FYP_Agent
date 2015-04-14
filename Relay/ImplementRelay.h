#ifndef IMPLEMENTRELAY_H
 #define IMPLEMENTRELAY_H

#include "Relay.h"

namespace Relayspace
{

	class ImplementRelay: public Relay
	{
		public:
			bool inRange(Coordinate test);

	};

}

#endif
