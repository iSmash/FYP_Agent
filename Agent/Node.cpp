#include "Node.h"
#include <cmath>
#include <vector>
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

void Node::printDirection(Node::Direction toprint)
{
    switch(toprint)
    {
    case Node::Right:
        cout<<"Right; ";
        break;
    case Node::Left:
        cout<<"Left; ";
        break;
    case Node::Up:
        cout<<"Up; ";
        break;
    case Node::Down:
        cout<<"Down; ";
        break;
    case Node::UpRight:
        cout<<"Up-Right; ";
        break;
    case Node::UpLeft:
        cout<<"Up-Left; ";
        break;
    case Node::DownLeft:
        cout<<"Down-Left; ";
        break;
    case Node::DownRight:
        cout<<"Down-Right; ";
        break;
    case Node::Root:
        cout<<"Start;";
        break;
    }
}

 void Node::deadEnd(Grid& grid, list<Node*> &Leaves) //needed param, thus not using ~
 {
    //cout<<"DELETING "<<state.getRow()<<' '<<state.getColumn()<<' '<<heuristic<<endl;
      //cout<<Parent->getState().getRow()<<' '<<Parent->getState().getColumn()<<' '<<Parent->getChildren()<<endl;

    if(Parent->getHeuristic()>heuristic) //first time parent Heur is -1 (very big unsigned) so first child deleted will always pass this
        Parent->setHeuristic(heuristic);

        Parent->Dec_children();

	 if(!Parent->getChildren() && Parent->getParent()!= NULL)//if no children, parent is a leaf again unless its the root
        {
            Leaves.push_back(Parent);
        }

    delete this;
 }



void Node::findHeuristic(vector<Coordinate> goals)
{   //std::cout<<endl<<state<<" ";
    //std::cout<<ceil(sqrt(pow((state.getRow()-goals[0].getRow()),2.0)+pow((state.getColumn()-goals[0].getColumn()),2.0)))<<" "<<level<<std::endl;
    if(goals.size()==0)
        throw string("No goal to go toward");

    heuristic= 9999999999;
    for(int goals_index=0; goals_index<goals.size(); goals_index++)
    {
        //int temp = ceil(sqrt(pow((state.getRow()-goals[goals_index].getRow()),2.0)+pow((state.getColumn()-goals[goals_index].getColumn()),2.0)))+level;
        int temp = abs(state.getRow()-goals[goals_index].getRow())+abs(state.getColumn()-goals[goals_index].getColumn())+level;

        //cout<<"heur "<<temp<<"\t";
        if(temp< heuristic && temp>0)
            heuristic = temp;
    }


}
