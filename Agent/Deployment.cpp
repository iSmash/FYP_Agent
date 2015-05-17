#include "Deployment.h"
#include <limits>
#include <cmath>
#include "../Grid/SubGrid.h"
#include "VirtualRelay.h"



using namespace DeploymentSpace;
using namespace std;

static const int WallSignal_Relation =3;

vector<Coordinate> Deployment::MidWayPlacement(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld)
{
	vector<Coordinate> relayPositions;
	relayPositions.push_back(Base);
	relayPositions.push_back(Client);
	while(relayCount+2>relayPositions.size())
	{

		vector<Coordinate> templist= relayPositions;
		for(int i = 1; i< relayPositions.size(); i++)
		{
			//cout<<"from "<<relayPositions[i-1] <<" and "<< relayPositions[i]<<endl;
			int rowMidPoint    = (relayPositions[i-1].getRow()+relayPositions[i].getRow())/2;
			int columnMidPoint = (relayPositions[i-1].getColumn()+relayPositions[i].getColumn())/2;
			//cout<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
			/** adujust position based on walls bettewen points */
			SubGrid subgrid(knownWorld,relayPositions[i-1], relayPositions[i]);

			int walls_left_top, walls_right_bot;
			subgrid.Wall_count(Coordinate(rowMidPoint,columnMidPoint), walls_left_top, walls_right_bot);

			//cout<<"Wall changes: -"<<walls_left_top<<"+"<<walls_right_bot<<endl;
			//rowMidPoint=rowMidPoint
			//            -walls_left_top/WallSignal_Relation
			//            +walls_right_bot/WallSignal_Relation;

			rowMidPoint=rowMidPoint+floor((walls_right_bot-walls_left_top)/WallSignal_Relation);

			columnMidPoint=columnMidPoint+floor((walls_left_top-walls_right_bot)/WallSignal_Relation);

			//            columnMidPoint=columnMidPoint
			//                           -walls_left_top/WallSignal_Relation
			//                           +walls_right_bot/WallSignal_Relation;
			//cout<<"gives "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
			/**  */
			//if adjustment made it not in between any more, put it on the boarder.


			//make sure not on top of wall
			int moveRange = 1;
			while(  knownWorld[Coordinate(rowMidPoint,columnMidPoint)].hasContent(ContentType::Object)
					||  knownWorld[Coordinate(rowMidPoint,columnMidPoint)].hasContent(ContentType::Unknown)
			)

			{
				for(int i=-(moveRange); i<=moveRange; i++)
				{
					for(int j=-(moveRange); j<=moveRange; j++)
					{
						try{
							if(  !(knownWorld[Coordinate(rowMidPoint+i,columnMidPoint+j)].hasContent(ContentType::Object))  &&
									!(knownWorld[Coordinate(rowMidPoint+i,columnMidPoint+j)].hasContent(ContentType::Unknown))
							)
							{

								rowMidPoint=rowMidPoint+i;
								columnMidPoint=columnMidPoint+j;
								i=moveRange+1;//break outer for-loop too
								break;

							}
						}
						catch (std::out_of_range){}
					}
				}
				moveRange++;
			}
			//cout<<"on wall fix "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
			templist.insert(templist.begin()+i, Coordinate(rowMidPoint, columnMidPoint));
			//cout<<Coordinate(rowMidPoint, columnMidPoint)<<" just added";

			// Checking if we are inside the domain of allowable node placement points.
//			if(rowMidPoint<subgrid.Get_top())
//				rowMidPoint=subgrid.Get_top()+1;
//			if(rowMidPoint>subgrid.Get_bot())
//				rowMidPoint=subgrid.Get_bot()-1;
//			if(columnMidPoint<subgrid.Get_left())
//				columnMidPoint=subgrid.Get_left()+1;
//			if(columnMidPoint>subgrid.Get_right())
//				columnMidPoint=subgrid.Get_right()-1;

			//cout<<"out of bounds fix "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
		}
		//cout<<endl;
		relayPositions= templist;
	}

	relayPositions.pop_back();
	relayPositions.erase(relayPositions.begin()); //remove the base and clinet from the list

	return relayPositions;

}

// Assigning quality to each cell and then selecting the bestest from this.
vector<Coordinate> Deployment::MidWayPlacementPotentialState(int relayCount, Coordinate Base, Coordinate Client, Grid& knownWorld)
{

	vector<Coordinate> relayPositions;
	relayPositions.push_back(Base);
	relayPositions.push_back(Client);

	while(relayCount+2>relayPositions.size())
	{

		vector<Coordinate> templist= relayPositions;
		for(int i = 1; i< relayPositions.size(); i++)
		{
			// Make subgrid between client and base.
			//cout<<"from "<<relayPositions[i-1] <<" and "<< relayPositions[i]<<endl;
			SubGrid subgrid(knownWorld, relayPositions[i-1], relayPositions[i]);

			Coordinate bestCoord;

			double bestScore = std::numeric_limits<double>::max(); // Ultimately searching for lowest value, like golf.
			for(int x=subgrid.Get_left(); x<=subgrid.Get_right(); x++)
			{
				for (int y=subgrid.Get_top(); y<=subgrid.Get_bot(); y++)
				{
					Coordinate current_examin =Coordinate(y,x);
					int walls_left_top, walls_right_bot;
					//look through all cells between points for best placement.
					if(!knownWorld[current_examin].hasContent(ContentType::Object)&&!knownWorld[current_examin].hasContent(ContentType::Unknown))
					{
						// Here is where cell quality value/score is determined.
						subgrid.Wall_count(current_examin,walls_left_top, walls_right_bot );
						double scoreCOL=  ( (x-subgrid.Get_left())+walls_left_top*WallSignal_Relation ) - ( (subgrid.Get_right()-x)+walls_right_bot*WallSignal_Relation );
						double scoreROW= ( (y-subgrid.Get_top())+walls_left_top*WallSignal_Relation ) - ( (subgrid.Get_bot()-y)+walls_right_bot*WallSignal_Relation );
						double score= sqrt( pow(scoreROW,2.0) + pow(scoreCOL,2.0));
						//cout<<score<<" "<<Coordinate(y,x)<<endl;
						if(score<bestScore)
						{
							bestScore=score;
							bestCoord=Coordinate(y,x);
						}
					}
				}
			}



			//cout<<bestCord<<endl;
			templist.insert(templist.begin()+i, bestCoord);
		}
		cout<<endl;
		relayPositions= templist;
	}

	relayPositions.pop_back();
	relayPositions.erase(relayPositions.begin()); //remove the base and client from the list
	return relayPositions;
}



vector<Coordinate> Deployment::VirtualForce(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld)
{

	vector<VirtualRelay> Relays;

	VirtualRelay Base_VF(Base);
	VirtualRelay Client_VF(Client); //these are define out of the vecoor, as they will not be movoing

	/*vector<Coordinate> initPlacement;
	initPlacement.push_back(Base);
	initPlacement.push_back(Client);
	while(relayCount+2>initPlacement.size())
	{

		vector<Coordinate> templist= initPlacement;
		for(int i = 1; i< initPlacement.size(); i++)
		{
			//cout<<"from "<<relayPositions[i-1] <<" and "<< relayPositions[i]<<endl;
			int rowMidPoint    = (initPlacement[i-1].getRow()+initPlacement[i].getRow())/2;
			int columnMidPoint = (initPlacement[i-1].getColumn()+initPlacement[i].getColumn())/2;

			templist.insert(templist.begin()+i, Coordinate(rowMidPoint, columnMidPoint));
		}
		    initPlacement= templist;
    }
    initPlacement.pop_back();
	initPlacement.erase(initPlacement.begin());
*/
	for(int relay_index =0; relay_index< relayCount; relay_index++) //create new relays on top of the base
	{
			//Relays.push_back(VirtualRelay(initPlacement[relay_index])); //NOT, base, relay on top of base at start
			Relays.push_back(VirtualRelay(Base));
	}

    Relays.front().addNeighbour(&Base_VF);
    Relays.back().addNeighbour(&Client_VF);
	for(int relay_index =0; relay_index< relayCount-1; relay_index++)
	{
		Relays[relay_index].addNeighbour(&Relays[relay_index+1]);
	}
	for(int relay_index =1; relay_index< relayCount; relay_index++)
	{
		Relays[relay_index].addNeighbour(&Relays[relay_index-1]);
	}

	int equalibirum_count=0;
	while(equalibirum_count<relayCount*10)
	{
		for(int relay_index =0; relay_index< relayCount; relay_index++)
		{
			Relays[relay_index].findForces(knownWorld);
		}

		for(int relay_index =0; relay_index< relayCount; relay_index++)
		{
			if( Relays[relay_index].Move(knownWorld))
            {
                equalibirum_count=0;
            }
            else
                 equalibirum_count++;
            cout<<relay_index<<":"<<Relays[relay_index].getLocation()<<endl;
		}
		cout<<equalibirum_count<<endl;
    //char x; cin>>x;
	}

	//done
	vector<Coordinate> toReturn;
	for(int i =0; i< relayCount; i++)
	{
		toReturn.push_back(Relays[i].getLocation());
	}
	return toReturn;
}


vector<Coordinate> Deployment::positionRelays(int method, int relayCount, Coordinate Base, Coordinate Client, Grid& knownWorld)
{
	//cout<<"start finding positons"<<endl;

	if (method>=3 && method<=5)
	{
		return MidWayPlacement(relayCount, Base,  Client, knownWorld);
	}
	else if (method>=6 && method<=8)
	{
		return MidWayPlacementPotentialState(relayCount, Base,  Client, knownWorld);
	}
	else if (method>=9 && method<=11)
	{
		return VirtualForce(relayCount, Base,  Client, knownWorld);
	}
	else
	{
	    vector<Coordinate> empty; //return this if method 0, 1 or error and method is not defined
		return empty;
	}

}
