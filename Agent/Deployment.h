#ifndef DEPLOYMENT_H
#define DEPLOYMENT_H
#include "../Grid/Grid.h"

namespace DeploymentSpace{
class Deployment
{
    public:
        vector<Coordinate> positionRelays(int method, int relayCount, Coordinate Base, Coordinate Client, Grid& knownWorld);

    private:
        vector<Coordinate> MidWayPlacement(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld);
        vector<Coordinate> MidWayPlacementPotentialState(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld);
        vector<Coordinate> VirtualForce(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld, int type);



};
}
#endif // DEPLOYMENT_H