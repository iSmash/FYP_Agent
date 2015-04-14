 #ifndef AGENT_H
#define AGENT_H

using namespace std;
namespace Agent{
 class PathPlan{
	public:
		Node* findPath(Coordinate goal);
	private:
		list<Node*> Leaves;
};

}
