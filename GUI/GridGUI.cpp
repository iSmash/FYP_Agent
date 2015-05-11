#define pixels_per_cell 20
#include "GridGUI.h"
#include "WinBGImPainter.h"
#include <exception>
#include "../Relay/SimulationRelay.h"




using namespace environment;



GridGUI::GridGUI(Grid* paintgrid, int screenLeft, char* name)
	{
//colour defines



	grid=paintgrid;
	oldGrid;


//size define
    windowHeight=pixels_per_cell* (grid->getLast().getRow()+1);
	windowWidth=pixels_per_cell*(grid->getLast().getColumn()+1);

    //make the painter and such
	painter=  new WinBGImPainter (windowWidth, windowHeight);
	window= initwindow(windowWidth, windowHeight, name ,screenLeft);
	delay(100);


        }

void GridGUI::updateSize()
{
    if(getcurrentwindow( )!=window)
    	{
       	 setcurrentwindow(window);
     	}

	windowHeight=pixels_per_cell*(grid->getLast().getRow()+1);
    windowWidth=pixels_per_cell*(grid->getLast().getColumn()+1);

    closegraph(window);
    window= initwindow(windowWidth, windowHeight, "name" ,900);
    delay(100);
}

void GridGUI::paint(bool Last)
{
    Colour Grid_line= Colour(0,0,0);
         Colour   Grid_fill= Colour(175,175,175);
          Colour  Wall_fill= Colour(125,125,125);

          Colour  Goal= Colour(1,200,1);
         Colour   Robot= Colour(200,1,1);

         Colour   Wifi = Colour(90,90 ,255);

          Colour  Client = Colour(204,204,0);

          Colour  THEVOID_THAT_IS_MY_SOUL=Colour(0,0,0);

	if(getcurrentwindow( )!=window)
    	{
       	 setcurrentwindow(window);
     	}
     vector<Relay*> RelayDraw = (*grid).getRelays();
	for(int i=0; i<grid->getLast().getRow();i++)
     	{


         	for(int j=0; j<grid->getLast().getColumn();j++)
         	{
                bool update =Last;
                int updateRange=0;
                //std::cout<<i<<" "<<j<<",";
                Grid newGrid= (*grid);


                std::vector<Content> newContentList = newGrid[Coordinate(i,j)].getContent() ;
                std::vector<Content> oldContnetList;

                try
                {


                for(int r=0; r< RelayDraw.size();r++)
                    {

                       if(RelayDraw[r]->inRange(Coordinate(i,j)))
                        {

                           update=true;
                           updateRange++;

                        }
                    }

            oldContnetList = oldGrid[Coordinate(i,j)].getContent();

                for(unsigned i=0; i<oldContnetList.size(); i++)
                {
                    //look if somthing removed
                    if(!(*grid)[Coordinate(i,j)].hasContent(oldContnetList[i]))
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

}
                catch(std::out_of_range){
                    //std::cout<<"OldGrid exep"<<std::endl;
                    update=true;
                    }
                if(update)
           		{
           		    //std::cout<<"change, redraw"<<std::endl;
           		    //draw grid cell
           		    Colour Background= Grid_fill;

                    if((*grid)[Coordinate(i,j)].hasContent(ContentType::Wall))
                    {
                        Background=Wall_fill;
                    }

                    if((*grid)[Coordinate(i,j)].hasContent(ContentType::Goal))
                    {
                        Background=Goal;

                    }
                    if((*grid)[Coordinate(i,j)].hasContent(ContentType::Unknown))
                    {
                        //std::cout<<"unkonw";
                        Background=THEVOID_THAT_IS_MY_SOUL;

                    }


                else{ //this mean unknown stays dark


                   while(updateRange>0)
                        {
                            Background = Background + Wifi;

                            updateRange--;
                        }
                }


                    painter->setPenColour(Grid_line);
                    painter->setFillColour(Background);
                    painter->drawSquare(Pixel((j+1)*pixels_per_cell,(i+1)*pixels_per_cell), pixels_per_cell);

                    if((*grid)[Coordinate(i,j)].hasContent(ContentType::Robot))
                    {
                        painter->setPenColour(THEVOID_THAT_IS_MY_SOUL);
                        painter->setFillColour(Robot);
                        painter->drawCircle(Pixel(float(j+1)*pixels_per_cell,float(i+1)*pixels_per_cell), pixels_per_cell/4);
                    }
                    if((*grid)[Coordinate(i,j)].hasContent(ContentType::RelayMarker))
                    {
                        painter->setPenColour(Wifi);
                        painter->setFillColour(Wifi);

                        painter->drawCircle(Pixel(float(j+1)*pixels_per_cell,float(i+1)*pixels_per_cell), pixels_per_cell/6);

                        }

                    if((*grid)[Coordinate(i,j)].hasContent(ContentType::Client))
                    {
                        painter->setPenColour(THEVOID_THAT_IS_MY_SOUL);
                        painter->setFillColour(Client);
                        painter->drawSquare(Pixel(float(j+1)*pixels_per_cell,float(i+1)*pixels_per_cell), pixels_per_cell/2);

                        }




           		}
        	}
   	 }

	oldGrid = *grid;//make this my old grid so next paint knows what to chage

}


