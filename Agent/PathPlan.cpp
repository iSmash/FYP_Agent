//A* search method
#include "PathPlan.h"
#include <iostream>
#include <exception>
#include <math.h>


using namespace Agentspace;



vector<Node::Direction> PathPlan::findPath(Coordinate& start, vector<Coordinate> goals,Grid& KnownWorld)
{
	std::cout<<"RUNNING"<<std::endl;

    /**for now lets just look at a single goal at a time
    */
    Coordinate goal= goals.back();
    /**/

std::cout<<start<<std::endl;
		std::cout<<goal<<std::endl;
	Node* NodePoint =NULL;
	Node* goalPoint=NULL;
	Leaves.push_back(new Node(start));
	while(1)//loop till broken
	{


		//std::cout<<"loop"<<std::endl;
		list<Node*>::iterator searchItor, BestItor;
		unsigned BestManhattanDistance_plusLevel=-1; //initial worst case, closes to infinity possible

		//find best node in list
		for(searchItor = Leaves.begin(); searchItor!= Leaves.end(); searchItor++)
		{

			if(!(*searchItor)->getHeuristic()) // if node heuristic not known, find
				(*searchItor)->setHeuristic(goal);

			//if its less its better, even if it does have unknonws
			if((*searchItor)->getHeuristic()<BestManhattanDistance_plusLevel)
			{
				BestItor=searchItor;
				BestManhattanDistance_plusLevel=(*searchItor)->getHeuristic();
			}
			//else if((*searchItor)->getHeuristic()==BestManhattanDistance_plusLevel && KnownWorld[Coordinate((*searchItor)->getState().getRow(), (*searchItor)->getState().getColumn())].hasContent(ContentType::Unknown))
			//{
			//	BestItor=searchItor;
			//	BestManhattanDistance_plusLevel=(*searchItor)->getHeuristic();
			//}


		}
		//std::cout<<"best"<<(*BestItor)->getState()<<" "<<(*BestItor)->getHeuristic()<<" "<<Leaves.size()<<std::endl;
		NodePoint=(*BestItor);
		Leaves.erase(BestItor); //pop cosen of the choice list

		goalPoint=explore(KnownWorld, NodePoint, goal); //explore node for children
		if(goalPoint!=NULL)//found goal
		{
			break;
		}
		if(!Leaves.size())//nothing in list, all paths explored without result
		{
			throw string("Error, out of leaves");
		}

	}



	//unravel, so we can go from current direction, to goal
	vector<Node::Direction> actionList; //list of directions
	while(goalPoint!=NULL) //directionlist from goal to root, take and put in action list
	{
		actionList.push_back(goalPoint->getAction());

		Node*temp = goalPoint;
		goalPoint=goalPoint->getParent();
        delete temp;
	}
	return actionList;





}


vector<Coordinate> MidWayPlacemtn(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld)
{
    vector<Coordinate> relayPositions;
    relayPositions.push_back(Base);
    relayPositions.push_back(Client);

    while(relayCount+2>relayPositions.size())
    {

        vector<Coordinate> templist= relayPositions;
        for(int i = 1; i< relayPositions.size(); i++)
        {
            cout<<"from "<<relayPositions[i-1] <<" and "<< relayPositions[i]<<endl;
            int rowMidPoint    = (relayPositions[i-1].getRow()+relayPositions[i].getRow())/2;
            int columnMidPoint = (relayPositions[i-1].getColumn()+relayPositions[i].getColumn())/2;
            cout<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
    /** adujust position based on walls bettewen points */
            int top_left_walls=0;
            int bot_right_wall=0;

            int top= relayPositions[i-1].getRow();
            if(relayPositions[i-1].getRow() > relayPositions[i].getRow())
                top=relayPositions[i].getRow();

            int left= relayPositions[i-1].getColumn();
             if(relayPositions[i-1].getColumn() > relayPositions[i].getColumn())
                left=relayPositions[i].getColumn();

               for(int i=top+1; i<rowMidPoint; i++)
               {
                   for( int j = left+1; j<columnMidPoint; j++)
                   {
                       if( knownWorld[Coordinate(i,j)].hasContent(ContentType::Wall) )
                        top_left_walls++;
                   }
               }

            int bot=  relayPositions[i].getRow();
            if(relayPositions[i-1].getRow() > relayPositions[i].getRow())
                bot=relayPositions[i-1].getRow();

            int right= relayPositions[i].getColumn();
             if(relayPositions[i-1].getColumn() > relayPositions[i].getColumn())
                right=relayPositions[i-1].getColumn();


             for(int i=rowMidPoint+1; i<bot; i++)
               {
                   for( int j = columnMidPoint+1; j<right; j++)
                   {
                       if(knownWorld[Coordinate(i,j)].hasContent(ContentType::Wall))
                        bot_right_wall++;
                   }
               }
            cout<<"Wall changes: -"<<top_left_walls<<"+"<<bot_right_wall<<endl;
               rowMidPoint=rowMidPoint-top_left_walls+bot_right_wall;
               columnMidPoint=columnMidPoint-top_left_walls+bot_right_wall;
               cout<<"gives "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
    /**  */
    //if adjustment made it not in between any more, put it on the boarder.
               if(rowMidPoint<top)
                rowMidPoint=top+1;
               if(rowMidPoint>bot)
                rowMidPoint=bot-1;
                 if(columnMidPoint<left)
                columnMidPoint=left+1;
                 if(columnMidPoint>right)
                columnMidPoint=right-1;

                cout<<"out of bounds fix "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;

                //make sure not on top of wall
                int moveRange = 1;
                while(  knownWorld[Coordinate(rowMidPoint,columnMidPoint)].hasContent(ContentType::Wall) ||
                        knownWorld[Coordinate(rowMidPoint,columnMidPoint)].hasContent(ContentType::Unknown)
                    )
                {
                    for(int i=-(moveRange); i<=moveRange; i++)
                    {
                        for(int j=-(moveRange); j<=moveRange; j++)
                        {

                            if(  !(knownWorld[Coordinate(rowMidPoint+i,columnMidPoint+j)].hasContent(ContentType::Wall))  &&
                                 !(knownWorld[Coordinate(rowMidPoint+i,columnMidPoint+j)].hasContent(ContentType::Unknown))
                               )
                            {
                                rowMidPoint=rowMidPoint+i;
                                columnMidPoint=columnMidPoint+j;
                                i=moveRange+1;//break outer for loop too
                                break;
                            }
                        }
                    }
                    moveRange++;
                }
            cout<<"on wall fix "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
            templist.insert(templist.begin()+i, Coordinate(rowMidPoint, columnMidPoint));
            //cout<<Coordinate(rowMidPoint, columnMidPoint)<<" just added";
        }
        cout<<endl;
        relayPositions= templist;
    }

    relayPositions.pop_back();
    relayPositions.erase(relayPositions.begin()); //remove the base and clinet from the list

return relayPositions;

}


vector<Coordinate> MidWayPlacemtn2(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld)
{
    vector<Coordinate> relayPositions;
    relayPositions.push_back(Base);
    relayPositions.push_back(Client);

    while(relayCount+2>relayPositions.size())
    {

        vector<Coordinate> templist= relayPositions;
        for(int i = 1; i< relayPositions.size(); i++)
        {
            cout<<"from "<<relayPositions[i-1] <<" and "<< relayPositions[i]<<endl;
            int left= relayPositions[i-1].getColumn();
            int right=relayPositions[i].getColumn();
            if(relayPositions[i-1].getColumn() > relayPositions[i].getColumn())
                {
                    left=relayPositions[i].getColumn();
                    right=relayPositions[i-1].getColumn();
                }

            int top= relayPositions[i-1].getRow();
            int bot= relayPositions[i].getRow();
            if(relayPositions[i-1].getRow() > relayPositions[i].getRow())
                {
                    top=relayPositions[i].getRow();
                    bot= relayPositions[i-1].getRow();
                }

            Coordinate bestCord;
            double bestScore=99999;
            for(int x=left; x<=right; x++)
            {
                for (int y=top; y<=bot; y++)
                {
                    //look thorugh all cells bweteen points for best placemtnet
                    if(!knownWorld[Coordinate(y,x)].hasContent(ContentType::Wall)&&!knownWorld[Coordinate(y,x)].hasContent(ContentType::Unknown))
                    {
                        int walls_left_top=0;
                        int walls_right_bot=0;
                        for(int wall_x=left; wall_x<=x; wall_x++)
                        {
                            for(int wall_y=top; wall_y<=y; wall_y++)
                            {
                                if(knownWorld[Coordinate(wall_y,wall_x)].hasContent(ContentType::Wall))
                                    //walls_left_top++;
                                    NULL;
                            }
                        }

                        for(int wall_x=x; wall_x<=right; wall_x++)
                        {
                            for(int wall_y=y; wall_y<=bot; wall_y++)
                            {
                                if(knownWorld[Coordinate(wall_y,wall_x)].hasContent(ContentType::Wall))
                                    //walls_right_bot++;
                                    NULL;
                            }
                        }
                        double scoreCOL=  ( (x-left)+walls_left_top ) - ( (right-x)+walls_right_bot );
                        double scoreROW= ( (y-top)+walls_left_top ) - ( (bot-y)+walls_right_bot );
                        double score= sqrt( pow(scoreROW,2.0) + pow(scoreCOL,2.0));
                        //cout<<score<<" "<<Coordinate(y,x)<<endl;
                        if(score<bestScore)
                        {
                            bestScore=score;
                            bestCord=Coordinate(y,x);
                        }
                    }
                }
            }



            //cout<<bestCord<<endl;
            templist.insert(templist.begin()+i, bestCord);
        }
        cout<<endl;
        relayPositions= templist;
    }

    relayPositions.pop_back();
    relayPositions.erase(relayPositions.begin()); //remove the base and clinet from the list
    return relayPositions;
}


 vector<Coordinate> PathPlan::positionRelays(int method, int relayCount, Coordinate Base, Coordinate Client, Grid& knownWorld)
 {

        cout<<"start finding positons"<<endl;

    if (method ==2)
         return MidWayPlacemtn(relayCount, Base,  Client, knownWorld);
         else   if (method ==3)
         return MidWayPlacemtn2(relayCount, Base,  Client, knownWorld);


    vector<Coordinate> fail;
    return fail;
 }



Node* PathPlan::explore(Grid& grid, Node* toExplore, Coordinate& goal)
{

	Coordinate state = toExplore->getState();
	if(grid[state].hasContent(ContentType::Goal))
	{
		goal=state;
		return toExplore;
	}


	/*bool aboveOK=false;
    bool rightOK=false;
    bool belowOK =false;
    bool leftOK=false;*/

	try{
		Coordinate above= Coordinate(state.getRow()-1,state.getColumn());
		if (!(grid[above].hasContent(ContentType::Object)) && !grid[above].getViewed())
		{

			Leaves.push_back(new Node(toExplore, above, Node::Up));
			grid[above].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}
	try{
		Coordinate right= Coordinate(state.getRow(),state.getColumn()+1);
		if (!(grid[right].hasContent(ContentType::Object)) && !grid[right].getViewed())
		{

			Leaves.push_back(new Node(toExplore, right, Node::Right));
			grid[right].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}
	try{
		Coordinate below= Coordinate(state.getRow()+1,state.getColumn());
		if ( !(grid[below].hasContent(ContentType::Object)) &&!grid[below].getViewed())
		{

			Leaves.push_back(new Node(toExplore, below, Node::Down));
			grid[below].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}
	try{
		Coordinate left= Coordinate(state.getRow(),state.getColumn()-1);
		if ( !(grid[left].hasContent(ContentType::Object))&&!grid[left].getViewed())
		{

			Leaves.push_back(new Node(toExplore, left, Node::Left));
			grid[left].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}

	try{
		Coordinate aboveleft= Coordinate(state.getRow()-1,state.getColumn()-1);
		if ( !(grid[aboveleft].hasContent(ContentType::Object))&&!grid[aboveleft].getViewed())
		{

			Leaves.push_back(new Node(toExplore, aboveleft, Node::UpLeft));
			grid[aboveleft].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}

	try{
		Coordinate abovelright= Coordinate(state.getRow()-1,state.getColumn()+1);
		if ( !(grid[abovelright].hasContent(ContentType::Object))&&!grid[abovelright].getViewed())
		{

			Leaves.push_back(new Node(toExplore, abovelright, Node::UpRight));
			grid[abovelright].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}

	try{
		Coordinate belowleft= Coordinate(state.getRow()+1,state.getColumn()-1);
		if ( !(grid[belowleft].hasContent(ContentType::Object))&&!grid[belowleft].getViewed())
		{

			Leaves.push_back(new Node(toExplore, belowleft, Node::DownLeft));
			grid[belowleft].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}

	try{
		Coordinate belowright= Coordinate(state.getRow()+1,state.getColumn()+1);
		if ( !(grid[belowright].hasContent(ContentType::Object))&&!grid[belowright].getViewed())
		{

			Leaves.push_back(new Node(toExplore, belowright, Node::DownRight));
			grid[belowright].setViewed(true);
			toExplore->Broken_condom();
		}
	}
	catch(std::out_of_range){}


	if(toExplore->getChildren()==0) // end
			toExplore->deadEnd(grid,Leaves);


	return NULL;
}



