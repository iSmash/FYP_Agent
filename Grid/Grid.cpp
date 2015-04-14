#include "Grid.h"
using namespace environment;
using namespace std;

Cell& Grid::operator [] (const Coordinate coord)
{
   vector<Cell> col= cells[coord.getRow()];
   return col[coord.getColumn()];

}

Relay* Grid::getRelay(int _ID)
{
	for(int i=0; i< deployedRelays.size(); i++)
	{
		if(deployedRelays[i]->getID()== _ID)
			return deployedRelays[i];
	}

}

void Grid::removeRelay(int _ID)
{
	for(int i=0; i< deployedRelays.size(); i++)
	{
		if(deployedRelays[i]->getID()== _ID)
			deployedRelays.erase(deployedRelays.begin()+i);
	}
}

void Grid::placeRelay(Relay* toPlace)
{
	deployedRelays.push_back(toPlace);
}

void Grid::clearGridViewed()
{
    for( int i =0; i< cells.size(); i++)
    {
        vector<Cell> temp = cells[i];
        for(int j=0; j< temp.size(); j++)
        {
            temp[j].setViewed(false);

        }
    }

}

void Grid::placeWall(int x, int y, int width, int high)
{
    for(unsigned i=y; i<(y+high); i++)
    {
        for(unsigned j=x; j< (x+width); j++)
        {
            vector<Cell> col= cells[i];
            col[j].addContent(ContentType::Wall);
        }
    }


}
void Grid::updateSize(Coordinate newSize){std::cout<<"no updte";}
void Grid::updateSize(updateSizeDirection toAdd){std::cout<<"no updte";}




