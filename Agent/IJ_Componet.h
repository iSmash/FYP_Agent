#ifndef IJ_COMPONET_H
#define IJ_COMPONET_H
#include <cmath>

class IJ_Componet
{
    public:
        IJ_Componet(){i=0; j=0;}
        double i;
        double j;
        inline double set_magnetude (){magnetude= sqrt(pow(i,2.0)+pow(j,2.0));}
        double magnetude;


};

#endif // IJ_COMPONET_H
