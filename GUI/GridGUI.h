#ifndef GRIDGUI_H
#define GRIDGUI_H



#include "../Grid/Grid.h"
#include "Painter.h"
#include "Colour.h"

using namespace environment;

	class GridGUI
	{
	public:
    GridGUI(Grid* paintgrid,  int screenLeft, char* name);

	void updateSize();


	void paint(bool Last=false);

	private:
	int window;
	int windowHeight;
	int windowWidth;
	Painter* painter;
	Grid* grid;
	Grid oldGrid;//this is an old copy of the grid, so we know what to change




	};

#endif
