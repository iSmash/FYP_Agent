#include "Node.h"
using namespace Agentspace;


///Root/public node creator
Node::Node(Coordinate _state)
{
    state=_state;
    Parent = NULL;
    level =0;
    actionToReach=Root;
    heuristic=0;
    children=0;
}

Node::Node(Node* _Parent, Coordinate _state, Direction _actionToReach)
{
    state=_state;
    Parent = _Parent;
    level = (Parent->level)+1;
    actionToReach=_actionToReach;
    heuristic=0;
    children=0;

}


 void Node::deadEnd(Grid& grid, list<Node*>* Leaves) //needed param, thus not using ~
 {
    //cout<<"DELETING "<<state.getRow()<<' '<<state.getColumn()<<' '<<heuristic<<endl;
      //cout<<Parent->getState().getRow()<<' '<<Parent->getState().getColumn()<<' '<<Parent->getChildren()<<endl;
    if(Parent->getHeuristic()>heuristic) //first time parent Heur is -1 (very big unsigned) so first child deleted will always pass this
        Parent->setHeuristic(heuristic);

        Parent->slender_man();
	 if(!Parent->getChildren())//if no children, parent is a leaf again
        {
            Leaves->push_back(Parent);
        }

	 grid[state].setViewed(false);//GUI

     delete this;
 }



void Node::setHeuristic(Coordinate goal)
{   //std::cout<<state.getRow()<<" "<<goal.getRow()<<std::endl;
    //std::cout<<abs(state.getRow()-goal.getRow())<<" "<<abs(state.getColumn()-goal.getColumn())<<" "<<level<<std::endl;
    heuristic= abs(state.getRow()-goal.getRow())+abs(state.getColumn()-goal.getColumn())+level;
}
