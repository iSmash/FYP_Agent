#define pixels_per_cell 25;


namespace envrionment
{
	class GridGUI
	{
	public:	
gridGUI(Grid* paintgrid, String name, int screenLeft);
	
	void updateSize(Grid* paintgrid);	
	
	
	void paint();	

	private:
	int window; 	
	int windowHeight;
	int windowWidth;
	Painter* painter;
	Grid* grid
	Grid oldGrid;//this is an old copy of the grid, so we know what to change
	
	//colours
	 Colour Grid_line;
         Colour Grid_fill;
         Colour Wall_fill;
         Colour Goal;
         Colour Robot;


	};
}
