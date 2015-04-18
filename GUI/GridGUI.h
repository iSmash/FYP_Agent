#ifndef GRIDGUI_H
#define GRIDGUI_H



#include "../Grid/Grid.h"
#include "Painter.h"
#include "Colour.h"

using namespace environment;

	class GridGUI
	{
	public:
    GridGUI(Grid* paintgrid,  int screenLeft);

	void updateSize();


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
          Colour Wifi;
           Colour THEVOID_THAT_IS_MY_SOUL;


	};

#endif
