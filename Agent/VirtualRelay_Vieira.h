#ifndef VirtualRelay_Vieira_H
#define VirtualRelay_Vieira_H
#include "VirtualRelay.h"
using namespace environment;

namespace DeploymentSpace{
class VirtualRelay_Vieira: public VirtualRelay
{
public:
    VirtualRelay_Vieira(Coordinate _Location):VirtualRelay(_Location){};
    void findForces(Grid& knownWorld);
    void Move();
      private:
        static double K_client;//
        static double K_obstacle;
        static double mass;
        static double viscous_friction;
};
}
#endif
