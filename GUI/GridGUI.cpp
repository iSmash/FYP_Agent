using namespace environment; 

gridGUI::gridGUI(Grid* paintgrid, String name, int screenLeft)
	{
//colour defines
            Grid_line= Colour(0,0,0);
            Grid_fill= Colour(175,175,175);
            Wall_fill= Colour(125,125,125);

            Goal= Colour(1,200,1);
            Robot= Colour(200,1,1);

	grid=paintgrid;
		
//size define
            windowHeight=pixels_per_cell*(grid->getLast().getRow()+1);
	windowWidth=pixels_per_cell*(grid->getLast().getColumn()+1);
	
//make the painter and such
	painter=  new WinBGImPainter (grid->getLast().getColumn()+1, grid->getLast().getRow()+1);
	
	window= initwindow(grid->getLast().getColumn()+1, grid->getLast().getRow()+1, namee ,screenLeft);
	delay(100);
        }

void gridGUI::updateSize(Grid* paintgrid)
{
	grid= paintgrid;
	windowHeight=pixels_per_cell*(grid->getLast().getRow()+1);
        windowWidth=pixels_per_cell*(grid->getLast().getColumn()+1);
}

void gridGUI::paint()
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
			
			std::vector<Content> newContentList = grid->getContent() ;
			try
			{
				std::vector<Content> oldContnetList = oldGrid.getContnet();
			}
			catch(Exception e){std::cout<<e.}
			
			for(unsigned i=0; i<newContentList.size()			

			if(oldGrid=null || !oldGrid[]
           		//draw grid cell
          		painter->setPenColour(Grid_line);
           		painter->setFillColour(Grid_fill);
           		painter->drawSquare(Pixel((j+1)*pixels_per_cell,(i+1)*pixels_per_cell), pixels_per_cell);
        	}
   	 }

	oldGrid =*grid;//make this my old grid so next paint knows what to chage

}


