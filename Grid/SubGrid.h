#ifndef SUBGRID_H
#define SUBGRID_H
#include "Grid.h"
#include "Coordinate.h"

class SubGrid: public Grid
{
    public:
        SubGrid(Grid& master_grid, Coordinate alpha, Coordinate beta);
        bool Wall_count(Coordinate center, int& top_left_count, int& bot_righ_count, int& bot_left_count, int& top_right_count);

        inline int Get_left(){return top_left.getColumn();}
        inline int Get_right(){return bot_right.getColumn();}
        inline int Get_top(){return top_left.getRow();}
        inline int Get_bot(){return bot_right.getRow();}
    private:
        Coordinate top_left;
        Coordinate bot_right;
        bool Top_left_item;
};

#endif // SUBGRID_H
