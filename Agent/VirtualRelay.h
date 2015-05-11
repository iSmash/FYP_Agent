#ifndef VIRTUALRELAY_H
#define VIRTUALRELAY_H
#include <vector>
#include "../Grid/Coordinate.h"
#include "../Grid/Grid.h"
class VirtualRelay
{
public:
    VirtualRelay(Coordinate _Location){Location=_Location;}
    virtual  void findForces(Grid& knownWorld)=0;
    virtual void Move()=0;
    inline void addNeighbour(VirtualRelay* neighbour){Neighbours.push_back(neighbour);}
    inline Coordinate getLocation(){return Location;}
    inline void setLocation(Coordinate _Location){Location=_Location;}
protected:
    double Force_j, Force_i; //Foreces in i,j components. Down and right are posative, up and left are negative
    vector<VirtualRelay*> Neighbours;
              Coordinate Location;
};

#endif // VIRTUALRELAY_H
