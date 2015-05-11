#include "SubGrid.h"

SubGrid::SubGrid(Grid& master_grid, Coordinate alpha, Coordinate beta)
{

    //first define where the top left corner is of the aplah and beta, same for righ bot corner
    int Left, Right, Top, Bot;
    if(alpha.getColumn() > beta.getColumn())
    {
        Left=beta.getColumn();
        Right=alpha.getColumn();
    }
    else
    {
    Left= alpha.getColumn();
    Right=beta.getColumn();
    }

    if(alpha.getRow() > beta.getRow())
    {
        Top=beta.getRow();
        Bot= alpha.getRow();
    }
     else
    {
        Top= alpha.getRow();
        Bot= beta.getRow();
    }

    //now set it to our class members
    top_left= Coordinate(Top,Left);
    bot_right=Coordinate(Bot, Right);


    //now make grid from section of grid known
    updateSize(bot_right); //make this new grid the right size

    //and give it correct contnet
    for(int row_indx=0; row_indx<Bot;row_indx++)
    {
        for(int col_indx=0; col_indx<Right; col_indx++)
        {
            Cell& temp = master_grid[Coordinate(row_indx, col_indx)];
            for(int cont_indx=0; cont_indx<temp.getContent().size(); cont_indx++)
            {
                cells[row_indx][col_indx].addContent(  temp.getContent()[cont_indx] );
            }
        }
    }



}

void SubGrid::Wall_count(Coordinate center, int& top_left_count, int& bot_righ_count)
{
    Coordinate relative_center= Coordinate(
                                           center.getRow()-top_left.getRow(),
                                           center.getColumn()-top_left.getColumn()
                                           );
    top_left_count=0;
     for(int row_indx=0; row_indx<relative_center.getRow();row_indx++)
    {
        for(int col_indx=0; col_indx<relative_center.getColumn(); col_indx++)
        {

           if(  cells[row_indx][col_indx].hasContent(ContentType::Wall))
              {
                 top_left_count++;
              }

        }
    }

    bot_righ_count=0;
    for(int row_indx=relative_center.getRow(); row_indx<LastCell.getRow();row_indx++)
    {
        for(int col_indx=relative_center.getColumn(); col_indx<LastCell.getColumn(); col_indx++)
        {

           if(  cells[row_indx][col_indx].hasContent(ContentType::Wall))
              {
                 bot_righ_count++;
              }

        }
    }

}
