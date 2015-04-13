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

    void WinBGImPainter::drawAngUp(const Pixel& center, unsigned size)
    {
         float ratio=1.75;
        int poly[8];
         poly[0] = center.getX() - (size/ratio);
        poly[1] = center.getY() -size*ratio;
        poly[2] = center.getX() + (size/ratio);
        poly[3] = center.getY() - size*ratio;
        poly[4] = center.getX() + (size/ratio);
        poly[5] = center.getY() + size*ratio;
        poly[6] = center.getX() - (size/ratio);
        poly[7] = center.getY() + size*ratio;
fillpoly(4, poly);

        rectangle(center.getX() - size/2 , center.getY() - size/2,
                  center.getX() + size/2 , center.getY() + size/2);

         int poly2[6];
           poly2[0]= center.getX();
           poly2[1]=center.getY()-(size*1.2*ratio);
           poly2[2]=center.getX()+(size*ratio*1.2);
           poly2[3]=center.getY()-(size*ratio*0.25);
           poly2[4]=center.getX()-(size*ratio*1.2);
           poly2[5]=center.getY()-(size*ratio*0.25);
fillpoly(3, poly2);

    }

    void WinBGImPainter::drawAngDown(const Pixel& center, unsigned size)
    {
         float ratio=1.75;
        int poly[8];
         poly[0] = center.getX() - (size/ratio);
        poly[1] = center.getY() -size*ratio;
        poly[2] = center.getX() + (size/ratio);
        poly[3] = center.getY() - size*ratio;
        poly[4] = center.getX() + (size/ratio);
        poly[5] = center.getY() + size*ratio;
        poly[6] = center.getX() - (size/ratio);
        poly[7] = center.getY() + size*ratio;
fillpoly(4, poly);

        rectangle(center.getX() - size/2 , center.getY() - size/2,
                  center.getX() + size/2 , center.getY() + size/2);

         int poly2[6];
           poly2[0]= center.getX();
           poly2[1]=center.getY()+(size*1.2*ratio);
           poly2[2]=center.getX()+(size*ratio*1.2);
           poly2[3]=center.getY()+(size*ratio*0.25);
           poly2[4]=center.getX()-(size*ratio*1.2);
           poly2[5]=center.getY()+(size*ratio*0.25);
fillpoly(3, poly2);

    }

    void WinBGImPainter::drawAngLeft(const Pixel& center, unsigned size)
    {
         float ratio=1.75;
        int poly[8];
         poly[0] = center.getX() - (size*ratio);
        poly[1] = center.getY() -size/ratio;
        poly[2] = center.getX() + (size*ratio);
        poly[3] = center.getY() - size/ratio;
        poly[4] = center.getX() + (size*ratio);
        poly[5] = center.getY() + size/ratio;
        poly[6] = center.getX() - (size*ratio);
        poly[7] = center.getY() + size/ratio;
fillpoly(4, poly);

        rectangle(center.getX() - size/2 , center.getY() - size/2,
                  center.getX() + size/2 , center.getY() + size/2);

         int poly2[6];
           poly2[0]= center.getX()-(size*1.2*ratio);
           poly2[1]=center.getY();
           poly2[2]=center.getX()-(size*ratio*0.25);
           poly2[3]=center.getY()+(size*ratio*1.2);
           poly2[4]=center.getX()-(size*ratio*0.25);
           poly2[5]=center.getY()-(size*ratio*1.2);
fillpoly(3, poly2);

    }

    void WinBGImPainter::drawAngRight(const Pixel& center, unsigned size)
    {
         float ratio=1.75;
        int poly[8];
       poly[0] = center.getX() - (size*ratio);
        poly[1] = center.getY() -size/ratio;
        poly[2] = center.getX() + (size*ratio);
        poly[3] = center.getY() - size/ratio;
        poly[4] = center.getX() + (size*ratio);
        poly[5] = center.getY() + size/ratio;
        poly[6] = center.getX() - (size*ratio);
        poly[7] = center.getY() + size/ratio;
fillpoly(4, poly);

        rectangle(center.getX() - size/2 , center.getY() - size/2,
                  center.getX() + size/2 , center.getY() + size/2);

         int poly2[6];
           poly2[0]= center.getX();
       poly2[0]= center.getX()+(size*1.2*ratio);
           poly2[1]=center.getY();
           poly2[2]=center.getX()+(size*ratio*0.25);
           poly2[3]=center.getY()+(size*ratio*1.2);
           poly2[4]=center.getX()+(size*ratio*0.25);
           poly2[5]=center.getY()-(size*ratio*1.2);
fillpoly(3, poly2);

    }

