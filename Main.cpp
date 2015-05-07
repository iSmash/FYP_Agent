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

#define GRIDFILE "RelayTestGrid"
#define RELAYFILE "RelayTestRelay.txt"
#define LOGFILE "LogFile.txt"

#include "Simulation.h"

#include "Agent/ImplementAgent.h"
#include "FileRead.h"
#include <fstream>
#include "GUI/GridGUI.h"
#include <ctime>

using namespace Agentspace;
using namespace environment;
using namespace std;
int main(int argc, char* argv[]) {
	//make agent
#ifdef Simulation
	cout<<"Simulation"<<endl;
	//SimulationAgent* AgentSmith = new SimulationAgent();
	SimulationAgent AgentSmith;

	//read file about trueWorld and relay
	RelativeCoordinate relativeToGoal = readfileGrid(AgentSmith, (string)GRIDFILE+(string)argv[1]+".txt");

	AgentSmith.setGoal(relativeToGoal);/**using magic we find where the goal is */

	readfileRelay(AgentSmith, (string)RELAYFILE);

	GridGUI TrueGUI = GridGUI(&AgentSmith.trueWorld,5);
	GridGUI KnownGUI = GridGUI(&AgentSmith.getKnownGrid(),900);
	AgentSmith.lookAround();

#else
	//Agent* AgentSmith= new ImpementAgent();
	ImplementationAgent AgentSmith;
	//read file of just relay for agent
	readfileRelay(AgentSmith, RELAYFILE);

#endif
	AgentSmith.defineDeploymentMethod(atoi(argv[2]));



 clock_t start = clock();
	try{

	     if(AgentSmith.getDeploymentMethod()==1)
    {
        AgentSmith.evaluateRealayRange();
    }
	    //Agent run
		while(!AgentSmith.done()) //loop until robot job is done.
		{
			TrueGUI.paint();
			KnownGUI.updateSize();
			KnownGUI.paint(true);

			//char x;cin>>x;
			try{AgentSmith.findPath();} catch(int easyThrow){} //nothing serius, just keep trying


		}
	}
	catch(string s){cout<<s<<endl;} //yall done goofed, lets stop
     double timer = (clock()-start) / (double) CLOCKS_PER_SEC;
	TrueGUI.paint(true);
	KnownGUI.updateSize();
	KnownGUI.paint(true);
#ifdef Simulation
	cout<<"relay range used: "<<SimulationRelay::getRange()<<endl<<"Time Taken: "<<timer<<endl;;
#endif

    //print results to file

    ofstream Log(LOGFILE, fstream::app );
    if(Log.is_open())
    {
        #ifdef Simulation
        Log<<"Simulation;"
        #else
        Log<<"Implementation;"
        #endif

        Log<<argv[1]<<";";//grid tested
        Log<<argv[2]<<";";//method
        Log<<timer<<";";

        #ifdef Simulation //now for some less intersting details
        Log<<SimulationRelay::getRange()<<";";
        #endif
        for()
        Log<<

        Log<<endl;
        Log.close();
    }
}
