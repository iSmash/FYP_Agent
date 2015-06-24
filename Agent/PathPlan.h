#ifndef PATHPLAN_H
#define PATHPLAN_H


#include "Node.h"


using namespace std;
using namespace environment;
namespace Agentspace{

class PathPlan{
public:
    vector<Node::Direction> findPath(Coordinate& start, vector<Coordinate> goal, Grid& KnownWorld);
	bool Explore_Unkown(Coordinate& start, Grid& knownWolrd);
	private:
	     Node* explore(Grid& grid, Node* toExplores, bool standard_explore=true);
	     Node* AddNode(Coordinate toAdd, Grid& grid, Node* toExplore, Node::Direction dir, bool standard_explore);
		list<Node*> Leaves;


};
}
#endif
