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

///constructor
Coordinate::Coordinate(unsigned rows, unsigned columnes)
{
if(rows<0 || columnes<0)
 throw(std::out_of_range("below 0") );
    row = rows;
    column = columnes;
}


