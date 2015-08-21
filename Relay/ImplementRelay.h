#ifndef IMPLEMENTRELAY_H
 #define IMPLEMENTRELAY_H

#include "Relay.h"
#include "../SerialPort.h"

namespace Relayspace
{

	class ImplementRelay: public Relay
	{
		public:
		    ImplementRelay();
			bool inRange(Coordinate test);
            void place(Coordinate newPos);
            void pickUp();
        private:
            static SerialPort *communication;
            char up[2];
            char down[2] ;

	};

}

#endif
