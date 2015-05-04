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
 #include <iostream>
 using namespace std;
namespace environment
{
    class Coordinate
    {
    public:
        /** Constructor
         * @param row - vertical position
         * @param colum- the horazontal position */
        Coordinate(int rows = 0, int columns =0);


         //Get functions
        inline const int getRow() const {return row;}
        inline const int getColumn() const {return column;}

        //Set funtions
        inline void setRow(const int coordrow)
{
if(coordrow<0)
 throw(std::out_of_range("below 0") );
row = coordrow;
}
        inline void setColumn(const int coordcol)
 {
if(coordcol<0)
 throw(std::out_of_range("below 0") );
column = coordcol;
}

        /** \brief Compare operator, checks both row and coloum of coordinates are equal
        */
        bool operator ==(const Coordinate &testcoords);

        Coordinate operator +(const Coordinate &secondcoord);

        friend ostream& operator << (ostream& os, const Coordinate &coord) {os<<"Row: "<<coord.getRow()<<" Column: "<<coord.getColumn(); return os;}
    protected:
        int row;
        int column;
    };

class RelativeCoordinate : public Coordinate //this corrdinate can be negative, dont use unless relative
{
    public:
    RelativeCoordinate(int rows = 0, int columns =0);

     //Set funtions
        inline void setRow(const int coordrow)
{
row = coordrow;
}
        inline void setColumn(const int coordcol)
 {

column = coordcol;
}

} ;

}




#endif
