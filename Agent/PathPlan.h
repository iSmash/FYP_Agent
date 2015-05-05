#ifndef PATHPLAN_H
#define PATHPLAN_H


#include "Node.h"


using namespace std;
using namespace environment;
namespace Agentspace{

class PathPlan{
public:
    vector<Node::Direction> findPath(Coordinate& start, vector<Coordinate> goal, Grid& KnownWorld);
    inline void clear(){Leaves.clear();}
 vector<Coordinate> positionRelays(int method, int relayCount, Coordinate Base, Coordinate Client, Grid* knownWorld);

	private:
	     Node* explore(Grid& grid, Node* toExplores, Coordinate& goal);
		list<Node*> Leaves;

    void ErrorState(Coordinate& start,Grid& KnownWorld);

};
}
#endif
