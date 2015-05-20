#ifndef VIRTUALRELAY_H
#define VIRTUALRELAY_H
#include <vector>
#include "../Grid/Coordinate.h"
#include "../Grid/Grid.h"
class VirtualRelay
{
public:
    VirtualRelay(Coordinate _Location){Location=_Location;vel_j=vel_i=0;}
    void findForces(Grid& knownWorld);
    bool Move(Grid& knownWorld);
    inline void addNeighbour(VirtualRelay* neighbour){Neighbours.push_back(neighbour);}
    inline Coordinate getLocation(){return Location;}
    inline void setLocation(Coordinate _Location){Location=_Location;}
    inline static void set_mass(double _mass){mass= _mass;}
    inline static void set_friction(double _frict){viscous_friction= _frict;}
private:
    double Force_j, Force_i; //Foreces in i,j components. Down and right are posative, up and left are negative
    double accel_j, accel_i;
    double vel_j, vel_i;
    vector<VirtualRelay*> Neighbours;
    Coordinate Location;
  static double mass;
   static double viscous_friction;

};


#endif // VIRTUALRELAY_H
