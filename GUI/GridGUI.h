#ifndef GRIDGUI_H
#define GRIDGUI_H



#include "../Grid/Grid.h"
#include "Painter.h"
#include "Colour.h"

using namespace environment;

	class GridGUI
	{
	public:
    GridGUI(Grid* paintgrid, char* name, int screenLeft);

	void updateSize(Grid* paintgrid);


	void paint();

	private:
	int window;
	int windowHeight;
	int windowWidth;
	Painter* painter;
	Grid* grid;
	Grid oldGrid;//this is an old copy of the grid, so we know what to change

	//colours
	 Colour Grid_line;
         Colour Grid_fill;
         Colour Wall_fill;
         Colour Goal;
         Colour Robot;


	};

#endif
