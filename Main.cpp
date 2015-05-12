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

int main(int argc, char* argv[]) {

char x;
	//make agent
#ifdef Simulation
	//cout<<"Simulation"<<endl;
	//SimulationAgent* Robotino = new SimulationAgent();
	SimulationAgent Robotino;

	//read file about trueWorld and relay
	RelativeCoordinate relativeToGoal = readfileGrid(Robotino, (string)GRIDFILE+(string)argv[1]+".txt");
        cout<<"rel"<<relativeToGoal<<endl;
	Robotino.setGoal(relativeToGoal);/**using magic we find where the goal is */

	readfileRelay(Robotino, (string)RELAYFILE);

#ifdef Show_Graphics
	GridGUI TrueGUI = GridGUI(&Robotino.trueWorld,5, argv[2]);
	GridGUI KnownGUI = GridGUI(&Robotino.getKnownGrid(),900,argv[2]);
#endif
	Robotino.lookAround();

#else
	//Agent* Robotino= new ImpementAgent();
	ImplementationAgent Robotino;
	//read file of just relay for agent
	readfileRelay(Robotino, RELAYFILE);

#endif
	Robotino.defineDeploymentMethod(atoi(argv[2]));



 clock_t start = clock();
	try{

	     if(Robotino.getDeploymentMethod()==1)
    {
        Robotino.evaluateRealayRange();
    }
	    //Agent run
		while(!Robotino.done()) //loop until robot job is done.
		{
#ifdef Show_Graphics
			TrueGUI.paint();
			KnownGUI.updateSize();
			KnownGUI.paint(true);
#endif
			char x;cin>>x;
			try{Robotino.findPath();} catch(int easyThrow){} //nothing serius, just keep trying


		}
	}
	catch(string s){cout<<s<<endl;} //yall done goofed, lets stop
     double timer = (clock()-start) / (double) CLOCKS_PER_SEC;

#ifdef Show_Graphics
	TrueGUI.paint(true);
	KnownGUI.updateSize();
	KnownGUI.paint(true);
#endif

#ifdef Simulation
	cout<<"relay range used: "<<SimulationRelay::getRange()<<endl<<"Time Taken: "<<timer<<endl;;
#endif
 //cin>>x;
    //print results to file

    ofstream Log(LOGFILE, fstream::app );
    if(Log.is_open())
    {
        #ifdef Simulation
        Log<<"Simulation;";
        Log<<SimulationRelay::getRange()<<";";
        #else
        Log<<"Implementation;";
        //put like ping quality or somehting here
        #endif
        Log<<currentDateTime()<<";";
        Log<<argv[2]<<";";//method
        Log<<timer<<";";
        for(int i=0; i<Robotino.getKnownGrid().getRelays().size(); i++)
        {
        Log<< Robotino.getKnownGrid().getRelays()[i]->getPos()<<" ";
        }
        Log<<";";
        Log<<argv[1]<<";";//GRID
        ifstream problemFile(((string)GRIDFILE+(string)argv[1]+".txt").c_str());
        while(problemFile.good())
        {
            char temp;
            problemFile>>temp;
            if(temp!= '\n')
                Log<<temp;
        }
        problemFile.close();
        Log<<";";

        problemFile.open(RELAYFILE);
        while(problemFile.good())
        {
            char temp;
            problemFile>>temp;
            if(temp!= '\n')
                Log<<temp;
        }
        problemFile.close();
        Log<<";";


        Log<<endl;
        Log.close();
    }
}
