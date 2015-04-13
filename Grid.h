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
			vector<Relay> getRelay(int _ID);
			void removeRelay(int _ID);
		private:
		    vector<vector<Cell>> cells; // vector of vectors, is a matrix of any other name not just as Keano?
		  vector<Relay> deployedRelays;
		Coordinate LastCell; //held max col and row, so we dont need to find it every time. 
	}
}

#endif
