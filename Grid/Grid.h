#ifndef GRID_H
 #define GRID_H

using namespace std;
using namespace Relay;
namespace environment
{
class Grid
	{
		public:
			void  adRealy(Relay toadd);
            		inline vector<Relay> getRelays(){return relays;} //remember this is just a copy, editing will not stick
			Relay getRelay(int _ID);
			vector<Relay> getRelays();//namechange for error provension? na

			void removeRelay(int _ID);
			void placeRelay(Relay toPlace);

		private:
		    vector<vector<Cell>> cells; // vector of vectors, is a matrix of any other name not just as Keano?
		  vector<Relay> deployedRelays;
		Coordinate LastCell; //held max col and row, so we dont need to find it every time. 
	}
}

#endif
