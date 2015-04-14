/**                                                                 *
 *   Coordinate, defining Coordinate class                          *
 *   Navigating robot                                               *
 *   @author Phillip C. Smith                                       *
 *   @version 1.0                                                   *
 *   @date 23/3/13                                                  *
 *                                                                **/

#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>
 #include <stdexcept>
namespace environment
{
    class Coordinate
    {
    public:
        /** Constructor
         * @param row - vertical position
         * @param colum- the horazontal position */
        Coordinate(unsigned rows = 0, unsigned columns =0);


         //Get functions
        inline const unsigned getRow() const {return row;}
        inline const unsigned getColumn() const {return column;}

        //Set funtions
        inline void setRow(const unsigned coordrow)
{
if(coordrow<0)
 throw(std::out_of_range("below 0") );
row = coordrow;
}
        inline void setColumn(const unsigned coordcol)
 {
if(coordcol<0)
 throw(std::out_of_range("below 0") );
column = coordcol;
}

        /** \brief Compare operator, checks both row and coloum of coordinates are equal
        */
        bool operator ==(const Coordinate &testcoords);

    private:
        unsigned row;
        unsigned column;
    };

}



#endif
