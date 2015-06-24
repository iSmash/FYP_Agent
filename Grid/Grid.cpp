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

Relay* Grid::removeRelay(Coordinate location)
{
    Relay* toReturn;
	for(int i=0; i< deployedRelays.size(); i++)
	{
		if(deployedRelays[i]->getPos() == location)
		{
		    toReturn=deployedRelays[i];
		    toReturn->updatePos(Coordinate(0,0));
		    deployedRelays.erase(deployedRelays.begin()+i);
		    break;
		}
	}
	return toReturn;
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

	//remove world endge
	for(int row_index=0;row_index<cells.size(); row_index++)
    {
        for(int col_index=0;col_index<cells[row_index].size(); col_index++)
        {
                cells[row_index][col_index].removeContent(ContentType::Jormungandr_Wall);
        }

    }

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

bool Grid::updateSize(updateSizeDirection toAdd)
{
	 //std::cout<<"adding to grid";
	 //std::cout<<"rows " <<cells.size();
	 //if(cells.size()!=0)
	//	 std::cout<<"column " <<cells[0].size()<<std::endl;
	 //else
	//    std::cout<<std::endl;
	switch (toAdd)
	{
	    //first go though that area looking for edge of world, rueturn without exansion if end of world reached.
	case top:{
	    //std::cout<<"top"<<std::endl;
		for(int i=1; i<LastCell.getColumn()-1; i++)
		{
		    if(cells.front()[i].hasContent(ContentType::Jormungandr_Wall))
                return false;
		}

		vector<Cell> temp;
		for(int i=0; i<LastCell.getColumn(); i++)
		{
		    //make new row
			Cell c = Cell();
			c.addContent(ContentType::Unknown);
			temp.push_back(c);
		}
		cells.insert(cells.begin(), temp);
		LastCell=Coordinate(LastCell.getRow()+1, LastCell.getColumn());
		break;
	}
	case  right:{
	    //std::cout<<"right"<<std::endl;
		for(int i=1; i<LastCell.getRow()-1; i++)
		{
		    if(cells[i].back().hasContent(ContentType::Jormungandr_Wall))
                  return false;
		}


		for(int i=0; i<LastCell.getRow(); i++)
		{
            //add new col
			Cell c = Cell();
			c.addContent(ContentType::Unknown);
			cells[i].push_back(c);
		}

		LastCell=Coordinate(LastCell.getRow(), LastCell.getColumn()+1);
		break;
	}
	case bottom:{
        //td::cout<<"bot"<<std::endl;
		for(int i=1; i<LastCell.getColumn()-1; i++)
		{
            if(cells.back()[i].hasContent(ContentType::Jormungandr_Wall))
                 return false;
		}

		vector<Cell> temp;
		for(int i=0; i<LastCell.getColumn(); i++)
		{
		    //add new row
			Cell c = Cell();
			c.addContent(ContentType::Unknown);
			temp.push_back(c);
		}
		cells.push_back(temp);
		LastCell=Coordinate(LastCell.getRow()+1, LastCell.getColumn());
		break;
	}
	case left:{
	    //td::cout<<"left"<<std::endl;

		for(int i=1; i<LastCell.getRow()-1; i++)
		{
		    if(cells[i].front().hasContent(ContentType::Jormungandr_Wall))
               return false;
		}

		for(int i=0; i<LastCell.getRow(); i++)
		{


		    //add new col
			Cell c = Cell();
			c.addContent(ContentType::Unknown);
			//vector<Cell> *temp= &cells[i];
			//temp->insert(temp->begin(),c);
			cells[i].insert(cells[i].begin(), c);
		}
		LastCell=Coordinate(LastCell.getRow(), LastCell.getColumn()+1);
		break;
	}
	};
	   return true;

	//std::cout<<"rows " <<cells.size();
	//if(cells.size()!=0)
	// std::cout<<"column " <<cells[0].size()<<std::endl;
}




