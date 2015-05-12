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
	private:
	     Node* explore(Grid& grid, Node* toExplores);
		list<Node*> Leaves;


};
}
#endif
