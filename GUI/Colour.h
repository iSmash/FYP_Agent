/**                                                                 *
 *   Colour, defining colour class                                  *
 *   Navigating robot                                               *
 *   @author Phillip C. Smith                                       *
 *   @version 1.0                                                   *
 *   @date 23/3/13                                                  *
 *                                                                **/

#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>

/** \brief Deifines a basic Red, Green, Blue colour for use with WinBGImPainter
 */
class Colour
{
    protected:
        unsigned char red, green, blue;

public:
/** \brief Constructors, take no param or 3 chars, use of chars to work with WinBGImPainter
 *
 * \param r, red amount between 0(none) and 255(very)
 * \param g, green amount between 0(none) and 255(very)
 * \return b, blue amount between 0(none) and 255(very)
 *
 */

  Colour () { red = green = blue = 0; }
  Colour (char r, char g, char b) : red(r), green(g), blue(b) {}

  unsigned char get_red () const   { return red; }
  unsigned char get_green () const { return green; }
  unsigned char get_blue () const  { return blue; }

  inline Colour operator + (const Colour toAdd)
  {
      Colour newCol;
      newCol.red = (this->red+toAdd.red)/2;
      newCol.blue = (this->blue+toAdd.blue)/2;
      newCol.green = (this->green+toAdd.green)/2;
      return newCol;
  }
};

#endif
