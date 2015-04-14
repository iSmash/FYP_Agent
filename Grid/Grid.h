#ifndef GRID_H
#define GRID_H

#include <vector>
#include "../Relay/Relay.h"
#include "Cell.h"
#include "Coordinate.h"
#include <iostream>

using namespace std;
using namespace Relayspace;
namespace environment
{
class Grid
	{
		public:
            inline vector<Relay*> getRelays(){return deployedRelays;}
			Relay* getRelay(int _ID);

			void removeRelay(int _ID);
			void placeRelay(Relay* toPlace);

			inline Coordinate getLast(){return LastCell;}
			void updateSize(Coordinate newSize);

			enum updateSizeDirection{top, right, bottom, left};
			void updateSize(updateSizeDirection toAdd);

			///Allows gird cell to be called like an array.
			Cell& operator [] (const Coordinate coord);

            void clearGridViewed(); //resets grid, so no cells thing they have been looked at, will be used for new search

            void placeWall(int x, int y, int width, int high);

		private:
		  vector< vector<Cell> > cells; // vector of vectors, is a matrix of any other name not just as Keano?
		  vector<Relay*> deployedRelays;
		Coordinate LastCell; //held max col and row, so we dont need to find it every time.
	};
}

#endif
