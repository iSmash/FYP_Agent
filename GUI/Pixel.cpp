

/***************************************************************************
 *
 *   Copyright (C) 2011 by Willem van Straten
 *   Licensed under the Academic Free License version 2.1
 *
 *   Multiplayer Battleships
 *   HIT3172 - Object-Oriented Programming in C++ Semester Project
 *
 ***************************************************************************/

#include "Pixel.h"

// performs the vector sum of two pixel coordinates
Pixel operator + (const Pixel& A, const Pixel& B)
{
  return Pixel (A.x+B.x, A.y+B.y);
}


