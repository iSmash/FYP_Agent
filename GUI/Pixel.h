/***************************************************************************
 *
 *   Copyright (C) 2011 by Willem van Straten
 *   Licensed under the Academic Free License version 2.1
 *
 *   Multiplayer Battleships
 *   HIT3172 - Object-Oriented Programming in C++ Semester Project
 *
 ***************************************************************************/

#ifndef __Pixel_header
#define __Pixel_header

class Pixel
{
  unsigned x;
  unsigned y;

public:

  // performs the vector sum of two pixel coordinates
  friend Pixel operator + (const Pixel& A, const Pixel& B);

  // default constructor
  Pixel (unsigned _x=0, unsigned _y=0) { x = _x; y = _y; }

  unsigned getX () const { return x; }
  unsigned getY () const { return y; }
  void setX (unsigned _x) { x = _x; }
  void setY (unsigned _y) { y = _y; }

};



#endif

