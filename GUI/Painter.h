/***************************************************************************
 *
 *   Copyright (C) 2011 by Willem van Straten
 *   Licensed under the Academic Free License version 2.1
 *
 *   Multiplayer Battleships
 *   HIT3172 - Object-Oriented Programming in C++ Semester Project
 *
 ***************************************************************************/

#ifndef __Painter_header
/***************************************************************************
 *
 *   Copyright (C) 2011 by Willem van Straten
 *   Licensed under the Academic Free License version 2.1
 *
 *   Multiplayer Battleships
 *   HIT3172 - Object-Oriented Programming in C++ Semester Project
 *
 ***************************************************************************/
 #define __Painter_header

#include <graphics.h>
#include <string>

//! Forward declaration of class Colour
class Colour;


//! Forward declaration of class Pixel
class Pixel;


//! Abstract base class of a display surface
class Painter
{
public:
 Painter() {}
  virtual ~Painter () {}

  virtual unsigned getWidth() = 0;
  virtual unsigned getHeight() = 0;

  virtual void setPenColour (const Colour&) = 0;
  virtual void setFillColour (const Colour&) = 0;

  virtual void drawCircle (const Pixel& centre, unsigned radius) = 0;
  virtual void drawSquare (const Pixel& centre, unsigned size) = 0;

};

#endif

