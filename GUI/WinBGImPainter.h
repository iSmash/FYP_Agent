/**                                                                 *
 *   WinBGImPainter, defining of painter window                     *
 *   Navigating robot                                               *
 *   @author Phillip C. Smith                                       *
 *   @version 1.0                                                   *
 *   @date 23/3/13                                                  *
 *                                                                **/
#ifndef WINDBGIMPAINTER_H
#define WINDBGIMPAINTER_H
#include "Painter.h"
#include "pixel.h"
#include "Colour.h"


class WinBGImPainter : public Painter
{
    public:
        /** \brief Constructor
         *
         * \param hieght, y-axis number of pixels to make the window
         * \param width, x-axis number of pixels to make the window
         * \return
         *
         */
        WinBGImPainter(const unsigned& hight = 0, const unsigned& width = 0)
        {
            Hight = hight;
            Width= width;
        }

        //get fucntions
        inline unsigned getHeight(){return Hight;}
        inline unsigned getWidth(){return Width;}

        //set fucntions
        inline void setPenColour(const Colour& pen){ setcolor(COLOR(pen.get_red(),pen.get_green(),pen.get_blue() ));}
        inline void setFillColour(const Colour& fill){ setfillstyle(1, COLOR(fill.get_red(),fill.get_green(), fill.get_blue()));}

        /** \brief Create a circle in painter window
         *
         * \param centre, location of center of circle
         * \param radius, radius of circle in pixel.
         */
        void drawCircle(const Pixel& centre, unsigned radius);

        /** \brief Creat a square in painter window
         *
         * \param centre, location of center of square
         * \param size, pixel lenght of a side
         */
        void drawSquare(const Pixel& centre, unsigned size);


    protected:
        unsigned Hight;
        unsigned Width;
};



#endif
