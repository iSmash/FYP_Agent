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

    if(alpha == top_left || beta == top_left)
        Top_left_item=true;
    else
        Top_left_item=false;

    Coordinate size = Coordinate(Bot-Top+1,Right-Left+1);
   // cout<<size<<endl;

    //now make grid from section of grid known
    updateSize(size); //make this new grid the right size
    //cout<<LastCell<<endl;
    //and give it correct contnet
    for(int row_indx=0; row_indx<(Bot-Top+1);row_indx++)
    {
        for(int col_indx=0; col_indx<(Right-Left+1); col_indx++)
        {

            Cell& temp = master_grid[Coordinate(row_indx+Top, col_indx+Left)];
            for(int cont_indx=0; cont_indx<temp.getContent().size(); cont_indx++)
            {
                cells[row_indx][col_indx].addContent( temp.getContent()[cont_indx] );
                /*if( temp.getContent()[cont_indx] == ContentType::Wall)
                {
                    cout<<"Wall"<<endl;
                }
                 if( temp.getContent()[cont_indx] == ContentType::Unknown)
                {
                    cout<<"Unknonw"<<endl;
                }
                if( temp.getContent()[cont_indx] == ContentType::Empty)
                {
                    cout<<"Emty"<<endl;
                }*/

            }
        }
    }



}

bool SubGrid::Wall_count(Coordinate center, int& top_left_count, int& bot_righ_count, int& bot_left_count, int& top_right_count)
{
    Coordinate relative_center= Coordinate(
                                           center.getRow()-top_left.getRow(),
                                           center.getColumn()-top_left.getColumn()
                                           );

    //cout<<"midle"<<relative_center<<endl;
    top_left_count=0;
    bot_righ_count=0;
    bot_left_count=0;
    top_right_count=0;
     for(int row_indx=0; row_indx<relative_center.getRow()+1;row_indx++)
    {
       for(int col_indx=0; col_indx<relative_center.getColumn()+1; col_indx++)
        {

           if(  cells[row_indx][col_indx].hasContent(ContentType::Wall))
              {
                  //cout<<"top left ++"<<row_indx<<" "<<col_indx<<endl;
                 top_left_count++;
              }

        }

         for(int col_indx=relative_center.getColumn(); col_indx<LastCell.getColumn(); col_indx++)
        {

        if(  cells[row_indx][col_indx].hasContent(ContentType::Wall))
          {
               // cout<<"bot_righ_count++"<<row_indx<<" "<<col_indx<<endl;
             bot_left_count++;
          }

        }

    }

    for(int row_indx=relative_center.getRow(); row_indx<LastCell.getRow();row_indx++)
    {

         for(int col_indx=0; col_indx<relative_center.getColumn()+1; col_indx++)
        {

           if(  cells[row_indx][col_indx].hasContent(ContentType::Wall))
              {
                  //cout<<"top left ++"<<row_indx<<" "<<col_indx<<endl;
                 top_right_count++;
              }

        }
        for(int col_indx=relative_center.getColumn(); col_indx<LastCell.getColumn(); col_indx++)
        {

           if(  cells[row_indx][col_indx].hasContent(ContentType::Wall))
              {
                   // cout<<"bot_righ_count++"<<row_indx<<" "<<col_indx<<endl;
                 bot_righ_count++;
              }

        }

    }
    return Top_left_item;
}
