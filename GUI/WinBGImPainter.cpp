/**                                                                 *
 *   WinBGImPainter, implementation of painter window               *
 *   Navigating robot                                               *
 *   @author Phillip C. Smith                                       *
 *   @version 1.0                                                   *
 *   @date 23/3/13                                                  *
 *                                                                **/
#include "WinBGImPainter.h"
#include <math.h>
    ///\brief Creat a square in painter window
    void WinBGImPainter::drawSquare(const Pixel& center, unsigned size)
    {
         int poly[8];

        poly[0] = center.getX() - size /2;
        poly[1] = center.getY() - size / 2;
        poly[2] = center.getX() + (size ) / 2;
        poly[3] = center.getY() - size / 2;
        poly[4] = center.getX() + (size ) / 2;
        poly[5] = center.getY() + (size ) / 2;
        poly[6] = center.getX() - size / 2;
        poly[7] = center.getY() + (size) / 2;
        fillpoly(4, poly);

        rectangle(center.getX() - size/2 , center.getY() - size/2,
                  center.getX() + size/2 , center.getY() + size/2);

    }

    ///\brief Create a circle in painter window
  void WinBGImPainter::drawCircle(const Pixel& centre, unsigned radius)
        {
            ellipse(centre.getX(), centre.getY(), 0,0,radius, radius);
            fillellipse(centre.getX(), centre.getY(), radius, radius);
        }

