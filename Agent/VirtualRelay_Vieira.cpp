#include "VirtualRelay_Vieira.h"
#include <cmath>
using namespace DeploymentSpace;

double VirtualRelay_Vieira::K_client=1;//
double VirtualRelay_Vieira::K_obstacle;
double VirtualRelay_Vieira::mass=1;
double VirtualRelay_Vieira::viscous_friction=1;

    void VirtualRelay_Vieira::findForces(Grid& knownWorld)
    {
        Force_j=0;
        Force_i=0;
        for(int neighbour_index=0; neighbour_index<Neighbours.size(); neighbour_index++)
        {
            double Force_temp;
            double PL_do;//??
            double path_loss_exp ;//??
            double WL; //?? Wall signel effect

            double d_ij = sqrt(pow((Location.getRow()-Neighbours[neighbour_index]->getLocation().getRow()),2.0)+pow((Location.getColumn()-Neighbours[neighbour_index]->getLocation().getColumn()),2.0));
            double d0;//??

            Force_temp = PL_do + 10*path_loss_exp*log(d_ij/d0);//+WL*w

            Force_j=Force_j+Force_temp;
            Force_i=Force_i+Force_temp;
        }
    }
    void VirtualRelay_Vieira::Move()
    {
        NULL;
    }
