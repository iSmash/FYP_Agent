#include "Deployment.h"
#include <limits>
#include <cmath>
#include "../Grid/SubGrid.h"
#include "VirtualRelay.h"



using namespace DeploymentSpace;
using namespace std;



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
           cout<<"start"<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
			/** adujust position based on walls bettewen points */
			SubGrid subgrid(knownWorld,relayPositions[i-1], relayPositions[i]);

			int walls_left_top, walls_right_bot;
			subgrid.Wall_count(Coordinate(rowMidPoint,columnMidPoint), walls_left_top, walls_right_bot);



			//rowMidPoint=rowMidPoint+floor((walls_right_bot-walls_left_top)/WallSignal_Relation);

			//columnMidPoint=columnMidPoint+floor((walls_left_top-walls_right_bot)/WallSignal_Relation);



			//make sure not on top of wall
			int moveRange = 1;
			while(  knownWorld[Coordinate(rowMidPoint,columnMidPoint)].hasContent(ContentType::Object)

			)

			{
				for(int i=-(moveRange); i<=moveRange; i++)
				{
					for(int j=-(moveRange); j<=moveRange; j++)
					{
						try{
						    cout<<Coordinate(rowMidPoint+i,columnMidPoint+j)<<endl;
							if(  !(knownWorld[Coordinate(rowMidPoint+i,columnMidPoint+j)].hasContent(ContentType::Object)))
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
					cout<<"moveRange"<<moveRange<<endl;
			}

			cout<<"on wall fix "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
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
    double WallSignal_Relation =sqrt( pow((double)(Base.getRow()-Client.getRow()),2.0)+
                                    pow((double)(Base.getColumn()-Client.getColumn()),2.0)
                                    )/9; //3^2
                                    cout<<"wall"<<WallSignal_Relation;
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
					if(!knownWorld[current_examin].hasContent(ContentType::Object))
					{
						// Here is where cell quality value/score is determined.
						subgrid.Wall_count(current_examin,walls_left_top, walls_right_bot );
						double scoreCOL=  ( abs(x-subgrid.Get_left()*1.0)+walls_left_top*WallSignal_Relation ) - ( abs(subgrid.Get_right()-x*1.0)+walls_right_bot*WallSignal_Relation );
						double scoreROW= ( abs(y-subgrid.Get_top()*1.0)+walls_left_top*WallSignal_Relation ) - ( abs(subgrid.Get_bot()-y*1.0)+walls_right_bot*WallSignal_Relation );
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



			cout<<bestCoord<<endl;
			templist.insert(templist.begin()+i, bestCoord);
		}
		//cout<<endl;
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
    /*VirtualRelay::set_mass(  abs((double)Base.getRow()-Client.getRow())*
                             abs((double)Base.getColumn()-Client.getColumn())
                           );

    */
    VirtualRelay::set_mass(pow((double)(Base.getRow()-Client.getRow()),2.0)+
                                    pow((double)(Base.getColumn()-Client.getColumn()),2.0));

    VirtualRelay::set_friction(sqrt( pow((double)(Base.getRow()-Client.getRow()),2.0)+
                                    pow((double)(Base.getColumn()-Client.getColumn()),2.0)
                                    ));

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
	int fail_count=0;
	while(equalibirum_count<relayCount*10)
	{
		for(int relay_index =0; relay_index< relayCount; relay_index++)
		{
			Relays[relay_index].findForces(knownWorld);
		}

		for(int relay_index =0; relay_index< relayCount; relay_index++)
		{
			if( Relays[relay_index].Move(knownWorld) || Relays[relay_index].getLocation()==Base)
            {
                equalibirum_count=0;
                if(fail_count++ >10000)
                    throw string("fail to find equalibrium");

            }
            else
                {
                   equalibirum_count++;
                   fail_count=0;
                }
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
