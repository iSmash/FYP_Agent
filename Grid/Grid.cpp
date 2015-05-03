#include "Grid.h"
using namespace environment;
using namespace std;

Cell& Grid::operator [] (const Coordinate coord)
{
	if(coord.getRow()>=cells.size())
		throw(std::out_of_range("out of row range"));
	vector<Cell> *col= &cells[coord.getRow()];
	if(coord.getColumn()>=col->size())
		throw(std::out_of_range("out of row range"));
	return (*col)[coord.getColumn()];

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
		vector<Cell> *temp = &cells[i];
		for(int j=0; j< temp->size(); j++)
		{
			(*temp)[j].setViewed(false);
		}

	}

}

void Grid::placeWall(int x, int y, int width, int high)
{
	for(unsigned i=y; i<(y+high); i++)
	{
		for(unsigned j=x; j< (x+width); j++)
		{
			vector<Cell> *col= &cells[i];
			(*col)[j].addContent(ContentType::Wall);
		}
	}


}
void Grid::updateSize(Coordinate newSize)
{
	LastCell=newSize;
	for(int i=cells.size(); i<newSize.getRow(); i++ )
	{
		cells.push_back(vector<Cell>());
	}

	for(int i=0; i<cells.size(); i++ )
	{
		vector<Cell> *temp= &cells[i];
		for(int j=temp->size(); j< newSize.getColumn();j++)
		{
			temp->push_back(Cell());
		}
	}

}

void Grid::updateSize(updateSizeDirection toAdd)
{
	// std::cout<<"adding to grid"<<std::endl;
	// std::cout<<"rows " <<cells.size();
	// if(cells.size()!=0)
		// std::cout<<"column " <<cells[0].size()<<std::endl;
	// else
	//    std::cout<<std::endl;
	switch (toAdd)
	{
	case top:{
		vector<Cell> temp;
		for(int i=0; i<LastCell.getColumn(); i++)
		{
			Cell c = Cell();
			c.addContent(ContentType::Unknown);
			temp.push_back(c);
		}
		cells.insert(cells.begin(), temp);
		LastCell=Coordinate(LastCell.getRow()+1, LastCell.getColumn());
		break;
	}
	case  right:{
		for(int i=0; i<LastCell.getRow(); i++)
		{
			Cell c = Cell();
			c.addContent(ContentType::Unknown);
			cells[i].push_back(c);
		}

		LastCell=Coordinate(LastCell.getRow(), LastCell.getColumn()+1);
		break;
	}
	case bottom:{

		vector<Cell> temp;
		for(int i=0; i<LastCell.getColumn(); i++)
		{
			Cell c = Cell();
			c.addContent(ContentType::Unknown);
			temp.push_back(c);
		}
		cells.push_back(temp);
		LastCell=Coordinate(LastCell.getRow()+1, LastCell.getColumn());
		break;
	}
	case left:{
		for(int i=0; i<LastCell.getRow(); i++)
		{
			Cell c = Cell();
			c.addContent(ContentType::Unknown);
			vector<Cell> *temp= &cells[i];
			temp->insert(temp->begin(),c);
		}
		LastCell=Coordinate(LastCell.getRow(), LastCell.getColumn()+1);
		break;
	}
	};

	//std::cout<<"rows " <<cells.size();
	//if(cells.size()!=0)
	// std::cout<<"column " <<cells[0].size()<<std::endl;
}




