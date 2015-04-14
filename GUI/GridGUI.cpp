#define pixels_per_cell 25
#include "GridGUI.h"
#include "WinBGImPainter.h"
#include <exception>
using namespace environment;

GridGUI::GridGUI(Grid* paintgrid, char* name, int screenLeft)
	{
//colour defines
            Grid_line= Colour(0,0,0);
            Grid_fill= Colour(175,175,175);
            Wall_fill= Colour(125,125,125);

            Goal= Colour(1,200,1);
            Robot= Colour(200,1,1);

	grid=paintgrid;

//size define
    windowHeight=pixels_per_cell* (grid->getLast().getRow()+1);
	windowWidth=pixels_per_cell*(grid->getLast().getColumn()+1);

    //make the painter and such
	painter=  new WinBGImPainter (grid->getLast().getColumn()+1, grid->getLast().getRow()+1);
	window= initwindow(grid->getLast().getColumn()+1, grid->getLast().getRow()+1, name ,screenLeft);
	delay(100);
        }

void GridGUI::updateSize(Grid* paintgrid)
{
	grid= paintgrid;
	windowHeight=pixels_per_cell*(grid->getLast().getRow()+1);
        windowWidth=pixels_per_cell*(grid->getLast().getColumn()+1);
}

void GridGUI::paint()
{

	if(getcurrentwindow( )!=window)
     	{
        	 setcurrentwindow(window);
     	}


	for(unsigned i=0; i<grid->getLast().getRow();i++)
     	{

         	for(unsigned j=0; j<grid->getLast().getColumn();j++)
         	{
                bool update =false;
                Grid newGrid= *grid;
                std::vector<Content> newContentList = newGrid[Coordinate(i,j)].getContent() ;
                std::vector<Content> oldContnetList;
                try
                {
                     oldContnetList = oldGrid[Coordinate(i,j)].getContent();
                }
                catch(...){std::cout<<"OldGrid exep"<<std::endl;}

                for(unsigned i=0; i<oldContnetList.size(); i++)
                {
                    //look if somthing removed
                    if(!newGrid[Coordinate(i,j)].hasContent(oldContnetList[i]))
                    {
                        update=true;
                        break;
                    }

                }
                 for(unsigned i=0; i<newContentList.size(); i++)
                {
                    //look if somthing added
                     if(!oldGrid[Coordinate(i,j)].hasContent(newContentList[i]))
                    {
                        update=true;
                        break;
                    }
                }

                if(update)
           		{
           		    //draw grid cell
                    painter->setPenColour(Grid_line);
                    painter->setFillColour(Grid_fill);
                    painter->drawSquare(Pixel((j+1)*pixels_per_cell,(i+1)*pixels_per_cell), pixels_per_cell);

                    if(newGrid[Coordinate(i,j)].hasContent(ContentType::Goal))
                    {
                        painter->setPenColour(Goal);
                        painter->setFillColour(Goal);
                        painter->drawCircle(Pixel(float(j-0.5)*pixels_per_cell,float(i-0.5)*pixels_per_cell), pixels_per_cell/4);
                    }

                    if(newGrid[Coordinate(i,j)].hasContent(ContentType::Robot))
                    {
                        painter->setPenColour(Robot);
                        painter->setFillColour(Robot);
                        painter->drawCircle(Pixel(float(j+0.5)*pixels_per_cell,float(i+0.5)*pixels_per_cell), pixels_per_cell/4);
                    }


           		}
        	}
   	 }

	oldGrid = *grid;//make this my old grid so next paint knows what to chage

}


