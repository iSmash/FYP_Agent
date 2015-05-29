#ifndef VIRTUALRELAY_H
#define VIRTUALRELAY_H
#include <vector>
#include "../Grid/Coordinate.h"
#include "../Grid/Grid.h"
#include "IJ_Componet.h"

class VirtualRelay
{
public:
    VirtualRelay(Coordinate _Location){Location=_Location;}
    void findForces(Grid& knownWorld);
    bool Move(Grid& knownWorld);
    inline void addNeighbour(VirtualRelay* neighbour){Neighbours.push_back(neighbour);}
    inline Coordinate getLocation(){return Location;}
    inline void setLocation(Coordinate _Location){Location=_Location;}
    inline static void set_mass(double _mass){mass= _mass;}
    inline static void set_friction(double _frict){viscous_friction= _frict;}
private:
    IJ_Componet force; //Foreces in i,j components. Down and right are posative, up and left are negative
    IJ_Componet accelleration;
    IJ_Componet velocity;
    vector<VirtualRelay*> Neighbours;
    Coordinate Location;
  static double mass;
   static double viscous_friction;

};


#endif // VIRTUALRELAY_H
