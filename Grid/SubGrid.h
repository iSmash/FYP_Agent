#ifndef SUBGRID_H
#define SUBGRID_H
#include "Grid.h"
#include "Coordinate.h"

class SubGrid: public Grid
{
    public:
        SubGrid(Grid& master_grid, Coordinate alpha, Coordinate beta);
        void Wall_count(Coordinate center, int& top_left_count, int& bot_righ_count);

        inline int Get_left(){top_left.getColumn();}
        inline int Get_right(){bot_right.getColumn();}
        inline int Get_top(){top_left.getRow();}
        inline int Get_bot(){bot_right.getRow();}
    private:
        Coordinate top_left;
        Coordinate bot_right;
};

#endif // SUBGRID_H
