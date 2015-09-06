/* Main.cpp
 * Author:  Phil Smith
 * Date:    20150411
 * Version: inf
 *
 */

/**
Deployment methods
0 Basic Reflex drop with pre-set threshold
1 Reflex drop we evaluated threshold
2 Midpoint via halfway, adjust for wall
3 Midpoint via lowest force
4 Virtual force relay self positioning using V.
5  ""
*/

#define Show_Graphics

#define GRIDFILE "RelayTestGrid"
#define RELAYFILE "RelayTestRelay.txt"
#define LOGFILE "LogFile.txt"
#define GRIDOUT "KnownWorld.txt"

#include "Simulation.h"

#include "Agent/ImplementAgent.h"
#include "FileRead.h"
#include <fstream>

#include <time.h>

#ifdef Show_Graphics
    #include "GUI/GridGUI.h"
#endif

using namespace Agentspace;
using namespace environment;
using namespace std;

const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


void SaveGrid(Grid toPrint)
{
     ofstream GridSave(GRIDOUT, fstream::out);
     if(GridSave.is_open())
    {
        GridSave<<toPrint.getLast().getRow()<<" "<<toPrint.getLast().getColumn()<<endl;
        for(int x=0; x< toPrint.getLast().getColumn(); x++)
        {
            for(int y=0; y<toPrint.getLast().getRow(); y++)
            {
                std::vector<Content> cellContnet = toPrint[Coordinate(y,x)].getContent();
                for(int c=0; c<cellContnet.size(); c++)
                {
                     switch (cellContnet[c])
                     {
                        case Wall:
                            GridSave<<"W";
                            break;
                        case Robot:
                            GridSave<<"R";
                            break;
                        case Goal:
                            GridSave<<"G";
                            break;
                        case Unknown:
                            GridSave<<"U";
                            break;
                        case Empty:
                            GridSave<<"E";
                            break;
                        case RelayMarker:
                            GridSave<<"M";
                            break;
                        case Client:
                            GridSave<<"C";
                            break;
                        case Base:
                            GridSave<<"B";
                            break;
                        case Jormungandr_Wall:
                            GridSave<<"J";
                            break;
                     }

                }
                GridSave<<" ";
            }
            GridSave<<endl;
        }

    }
}

void Log(string errorString, string Method, double timer, Agent* iRobot, string GridString)
{
    //print results to file
    ofstream Log(LOGFILE, fstream::app );
    if(Log.is_open())
    {
        #ifdef Simulation
        Log<<"Simulation &";
        Log<<SimulationRelay::getRange()<<"&";
        #else
        Log<<"Implementation;";
        //put like ping quality or somehting here
        #endif
        Log<<errorString<<"&";
        Log<<currentDateTime()<<"&";
        Log<<"M"<<Method<<"&";//method
        Log<<timer<<"&";
        Log<<iRobot->Get_stepcount()<<"&";
        for(int row=0; row<iRobot->getKnownGrid().getLast().getRow(); row++)
        {
             for(int col=0; col<iRobot->getKnownGrid().getLast().getColumn(); col++)
             {
                 if(iRobot->getKnownGrid()[Coordinate(row, col)].hasContent(ContentType::RelayMarker))
                    Log<<Coordinate(row, col)<<" ";
             }
        }

        Log<<"&";
        Log<<GridString<<"&";//GRID
        ifstream problemFile(((string)GRIDFILE+GridString+".txt").c_str());
        while(problemFile.good())
        {
            char temp;
            problemFile>>temp;
            if(temp!= '\n')
                Log<<temp;
        }
        problemFile.close();
        Log<<"&";

        problemFile.open(RELAYFILE);
        while(problemFile.good())
        {
            char temp;
            problemFile>>temp;
            if(temp!= '\n')
                Log<<temp;
        }
        problemFile.close();
        Log<<"&";


        Log<<"//"<<endl;
        Log.close();
    }
}



int main(int argc, char* argv[]) {

char x;
	//make agent
#ifdef Simulation
	//cout<<"Simulation"<<endl;
	//SimulationAgent* iRobot = new SimulationAgent();
	SimulationAgent iRobot;

	//read file about trueWorld and relay
	RelativeCoordinate relativeToGoal = readfileGrid(iRobot, (string)GRIDFILE+(string)argv[1]+".txt");
        //cout<<"rel"<<relativeToGoal<<endl;
	iRobot.setGoal(relativeToGoal);/**using magic we find where the goal is */



    #ifdef Show_Graphics
        GridGUI TrueGUI = GridGUI(&iRobot.trueWorld,5, argv[2]);
    #endif


	iRobot.lookAround();

#else
	//Agent* iRobot= new ImpementAgent();
	char ControlPort[5];
	readfileControl(ControlPort);

	ImplementAgent iRobot(ControlPort);
	cout<<"robot made";
    iRobot.setGoal(  RelativeCoordinate(atoi(argv[3]), atoi(argv[4])) );/**using magic we find where the goal is */
	//read file of just relay for agent
cout<<"set";

#endif

#ifdef Show_Graphics
	GridGUI KnownGUI = GridGUI(&iRobot.getKnownGrid(),900,argv[2]);
	#ifndef Simulation
        iRobot.giveGUI(&KnownGUI);
	#endif
#endif

    Agent* AgentPnt = &iRobot;
    readfileRelay(AgentPnt, RELAYFILE);
	iRobot.defineDeploymentMethod(atoi(argv[2]));


    cout<<"setup done"<<endl;
 clock_t start = clock();
 	string errorString;
	try{

	    //Agent run
		while(!iRobot.done()) //loop until robot job is done.
		{
            #ifdef Show_Graphics

                #ifdef Simulation
                    TrueGUI.paint();
                #endif

                KnownGUI.updateSize();
                KnownGUI.paint(true);
                cin>>x;
            #endif
			try{iRobot.findPath();} catch(int easyThrow){} //nothing serius, just keep trying

		}
	}

	catch(string s){ errorString=s; cout<<errorString<<endl;} //yall done goofed, lets stop
     double timer = (clock()-start) / (double) CLOCKS_PER_SEC;



#ifdef Simulation
	cout<<"relay range used: "<<SimulationRelay::getRange()<<endl<<"Time Taken: "<<timer<<endl;;
#endif

#ifdef Show_Graphics
	#ifdef Simulation
        TrueGUI.paint(true);
    #endif
	KnownGUI.updateSize();
	KnownGUI.paint(true);
	 cin>>x;
#endif
    SaveGrid(iRobot.getKnownGrid());

    Log(errorString, argv[2], timer, &iRobot, argv[1]);

}




