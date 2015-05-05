/**                                                                 *
 *   Coordinate, implamentation of Coordinate class                 *
 *   Navigating robot                                               *
 *   @author Phillip C. Smith                                       *
 *   @version 1.0                                                   *
 *   @date 23/3/13                                                  *
 *                                                                **/

#include "Coordinate.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace environment;
using namespace std;

/** \brief Compare operator, checks both row and coloum of coordinates are equal
    */
bool Coordinate::operator ==(const Coordinate &testcoords)
                 { return (testcoords.getRow() == row )&& (testcoords.getColumn() == column);}

  Coordinate Coordinate::operator +(const Coordinate &secondcoord)
  {
      return Coordinate(row+secondcoord.getRow(), column+secondcoord.getColumn());
  }



///constructor
Coordinate::Coordinate(int rows, int columns)
{
if(rows<0 || columns<0)
    throw(std::out_of_range("below 0") );
    row = rows;
    column = columns;
}

RelativeCoordinate::RelativeCoordinate(int rows, int columns)
{
    row = rows;
    column = columns;
}



