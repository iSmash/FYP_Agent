/**                                                                 *
 *   Implementation of readin, reads grid from file                 *
 *   Navigating robot                                               *
 *   @author Phillip C. Smith                                       *
 *   @version 1.1                                                   *
 *   @date 23/3/13                                                  *
 *                                                                **/

#include "FileRead.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "Relay/ImplementRelay.h"
#include "Relay/SimulationRelay.h"

#include "Simulation.h"

#define MAX_FAILS 5000
using namespace std;


RelativeCoordinate readfileGrid(SimulationAgent &agent, string filename) //simulation only
{
	cout<< filename<<endl;
	unsigned x, y, w, h;
	Coordinate goal, robotCoord;
	RelativeCoordinate relation;

	ifstream problemFile(filename.c_str());

	//find M and N for grid size
	if(problemFile.good())
	{
		problemFile.ignore();
		problemFile>> x;
		problemFile.ignore();
		problemFile>>y;
		agent.trueWorld.updateSize(Coordinate(y,x));
		for(int i=0; i<x; i++)
		{
			for( int j=0; j<y; j++)
			{
				agent.trueWorld[Coordinate(j,i)].addContent(ContentType::Empty);
			}

		}


	}
	//find robot starting pos
	if(problemFile.good())
	{
		problemFile.ignore(3);
		problemFile>> x;
		problemFile.ignore();
		problemFile>>y;
		robotCoord = Coordinate(y,x);
		agent.trueWorld[robotCoord].addContent(ContentType::Base);
		agent.trueWorld[robotCoord].addContent(ContentType::Robot);
		agent.setRelativity(robotCoord);
		agent.trueWorld[robotCoord].setViewed(true);
		Relay* basesStation = new SimulationRelay(&agent.trueWorld);
		basesStation->updatePos(robotCoord);
		agent.trueWorld.placeRelay(basesStation);
	}
	//find goal pos
	if(problemFile.good())
	{
		problemFile.ignore(3);
		problemFile>> x;
		problemFile.ignore();
		problemFile>>y;
		agent.trueWorld[Coordinate(y,x)].addContent(ContentType::Client);
		goal= Coordinate(y,x);
		relation= RelativeCoordinate(goal.getRow()-robotCoord.getRow(), goal.getColumn()-robotCoord.getColumn());

	}


	problemFile.ignore(3);
	//find walls
	while(problemFile.good())
	{
		//std::cout<<"wall"<<std::endl;
		problemFile>>x;
		problemFile.ignore();
		problemFile>>y;
		problemFile.ignore();
		problemFile>>w;
		problemFile.ignore();
		problemFile>>h;

		agent.trueWorld.placeWall(x, y, w, h);
		problemFile.ignore(3);
	}
	if(problemFile.bad())
		cout<<"error reading file";

	problemFile.close();
	return relation;

}


void readfileRelay(SimulationAgent &agent, string filename)
{
	/*
		looks like>
		3
		(1,2,7,9)
	 */
	unsigned robotRelayNumber, oldtemp, temp=0;


	ifstream problemFile(filename.c_str());
	//find relaynumber
	if(problemFile.good())
	{
		problemFile>> robotRelayNumber;
		agent.setRelayCount(robotRelayNumber);
	}


	problemFile.ignore(2);

	//relay ranges, simulation only.
#ifdef Simulation
	while(problemFile.good())
	{

		oldtemp=temp;
		problemFile>>temp;
		if(temp>oldtemp)
		{
			agent.addRange(temp);
		}
		problemFile.ignore(1);
	}
	vector<Relay*> RelayRange = agent.trueWorld.getRelays();
			for(int i=0; i<RelayRange.size(); i++)
			{
				SimulationRelay* rel = (SimulationRelay*)RelayRange[i];
				rel->findDomain();
			}
#endif
	if(problemFile.bad())
		cout<<"error reading file";

	problemFile.close();

}


//generate grid to explore //old code
void makefile()
{
	unsigned M, N, x1, y1, x2, y2, x3, y3, w=0, h=0, walls;
	srand(time(NULL));
	M= rand() % 20;
	N= rand() % 20;

	//set agent
	x1= rand() %(M-1);
	y1= rand() %(N-1);

	//set goal (can be on agetn)
	x2= rand() %(M-1);
	y2= rand() %(N-1);

	//add to file
	ofstream problemFile("problem.txt");
	problemFile<<'['<<N<<','<<M<<']'<<endl;
	problemFile<<'('<<x1<<','<<y1<<')'<<endl;
	problemFile<<'('<<x2<<','<<y2<<')'<<endl;

	//set Walls (between 1 and 10 walls, can overlap, but cant be on agent nor goal)
	walls= rand() % 10 +1;

	cout<<walls;
	bool placeOK;
	unsigned failL1;
	for(unsigned i =0; i< walls; i++)
	{
		failL1=0;

		do
		{
			placeOK=true;
			//make wall starting points
			x3=rand() %(M-1);

			y3= rand() %(N-1);
			w=rand() %(M-1);
			h=rand() %(N-1);
			//x3=1; y3=1;
			//w=2; h=2;

			//make sure wall size are inside grid
			if((w+x3)>M)
			{placeOK=false; cout<<"err1 ";}

			if((h+y3)>N)
			{placeOK=false; cout<<"err2 ";}

			//make sure wall not ontop of goal or agent
			for(unsigned j= x3; j<(w+x3); j++)
			{

				for(unsigned k= y3; k<(h+y3); k++)
				{
					if(k==y1&&j==x1)
					{placeOK=false; cout<<"err3 ";}
					if(k==y2&&j==x2)
					{placeOK=false; cout<<"err4 ";}
				}
			}
			failL1++;
			//cout<<failL1<<' '<<MAX_FAILS<<endl;
			//if no valid place for a wall, this will end stop an endless loop
			if(failL1==MAX_FAILS)
			{
				//cout<<"here, "<<x3<<' '<<y3<<' '<<w<<' '<<h<<endl;
				//cout<<"here";
				h=0;
				w=0;
				break;
			}
		}while(!placeOK);
		//once here, valid wall made
		//cout<<x3<<' '<<y3<<' '<<w<<' '<<h<<endl;
		problemFile<<'('<<x3<<','<<y3<<','<<w<<','<<h<<')'<<endl;
	}



	problemFile.close();


}





