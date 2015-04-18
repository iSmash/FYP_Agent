#ifndef NODE_H
#define NODE_H
#include <list>
#include "../Grid/Grid.h"
#include <stdlib.h>
using namespace std;
using namespace environment;
namespace Agentspace{
 class Node{
public:
        ///direcections robot has move
        enum Direction {Right, Left, Up, Down, Root};//Root means did not move to get there, as at ....root position

      Node(Coordinate _state);
Node(Node* _Parent, Coordinate _state, Direction _actionToReach);


      Node operator = (Node was);

      //gets
        inline const Coordinate getState() const {return state;}
         inline const unsigned getLevel() const {return level;}
         inline  Node* getParent() const {return Parent;}
         inline const Direction getAction() const {return actionToReach;}
        inline const unsigned getHeuristic() const {return heuristic;}
      inline const unsigned getChildren() const {return children;}


         void setHeuristic(Coordinate goal);
         inline void addChild(){children++;}
         inline void slender_man(){children--;}
 void deadEnd(Grid& grid,  list<Node*>* Leaves);



private:
    Node* Parent;   //the node that made this node
    Coordinate state; //the location on map
    unsigned level;     //how many moves in this node is
    Direction actionToReach; //what does the robot need to do to reach this state
    unsigned heuristic;   //how good this node is for reaching goal
	unsigned children; //used for freeing useless nodes



};
}
#endif
