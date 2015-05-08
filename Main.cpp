/* Main.cpp
 * Author:  Phil Smith
 * Date:    20150411
 * Version: inf
 *
 */

<<<<<<< df918135b89afd757a08fcba7994348c814b76db
/**
Deployment methods
0 Basic Reflex drop with pre-set threshold
1 Reflex drop we evaluated threshold
2 Midpoint via halfway, adjust for wall
3 Midpoint via lowest force
4 Virtual force relay self positioning using V.
5  ""
*/

=======
>>>>>>> b9d770d0b4c6735d46e543e08818bd737f598a8b
#define GRIDFILE "RelayTestGrid"
#define RELAYFILE "RelayTestRelay.txt"
#define LOGFILE "LogFile.txt"

#include "Simulation.h"

#include "Agent/ImplementAgent.h"
#include "FileRead.h"
#include <fstream>
#include "GUI/GridGUI.h"
#include <time.h>

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
	//make agent
#ifdef Simulation
<<<<<<< df918135b89afd757a08fcba7994348c814b76db
	cout<<"Simulation"<<endl;
	//SimulationAgent* Robotino = new SimulationAgent();
	SimulationAgent Robotino;

	//read file about trueWorld and relay
	RelativeCoordinate relativeToGoal = readfileGrid(Robotino, (string)GRIDFILE+(string)argv[1]+".txt");
=======
	cout << "Simulation" << endl;
	//SimulationAgent* AgentSmith = new SimulationAgent();
	SimulationAgent AgentSmith;

	//read file about trueWorld and relay
	RelativeCoordinate relativeToGoal = readfileGrid(AgentSmith,
			(string) GRIDFILE + (string) argv[1] + ".txt");
>>>>>>> b9d770d0b4c6735d46e543e08818bd737f598a8b

	Robotino.setGoal(relativeToGoal);/**using magic we find where the goal is */

<<<<<<< df918135b89afd757a08fcba7994348c814b76db
	readfileRelay(Robotino, (string)RELAYFILE);

	GridGUI TrueGUI = GridGUI(&Robotino.trueWorld,5);
	GridGUI KnownGUI = GridGUI(&Robotino.getKnownGrid(),900);
	Robotino.lookAround();
=======
	readfileRelay(AgentSmith, (string) RELAYFILE);

	GridGUI TrueGUI = GridGUI(&AgentSmith.trueWorld, 5);
	GridGUI KnownGUI = GridGUI(AgentSmith.getKnownGrid(), 900);
	AgentSmith.lookAround();
>>>>>>> b9d770d0b4c6735d46e543e08818bd737f598a8b

#else
	//Agent* Robotino= new ImpementAgent();
	ImplementationAgent Robotino;
	//read file of just relay for agent
	readfileRelay(Robotino, RELAYFILE);

#endif
	Robotino.defineDeploymentMethod(atoi(argv[2]));

<<<<<<< df918135b89afd757a08fcba7994348c814b76db


 clock_t start = clock();
	try{

	     if(Robotino.getDeploymentMethod()==1)
    {
        Robotino.evaluateRealayRange();
    }
	    //Agent run
		while(!Robotino.done()) //loop until robot job is done.
=======
	//Agent run
	try {
		while (!AgentSmith.done()) //loop until robot job is done.
>>>>>>> b9d770d0b4c6735d46e543e08818bd737f598a8b
		{
			TrueGUI.paint();
			KnownGUI.updateSize();
			KnownGUI.paint(true);

			//char x;cin>>x;
			try{Robotino.findPath();} catch(int easyThrow){} //nothing serius, just keep trying


<<<<<<< df918135b89afd757a08fcba7994348c814b76db
=======
			//char x;cin>>x;
>>>>>>> b9d770d0b4c6735d46e543e08818bd737f598a8b
		}
	} catch (string s) {
		cout << s << endl;
	}
<<<<<<< df918135b89afd757a08fcba7994348c814b76db
	catch(string s){cout<<s<<endl;} //yall done goofed, lets stop
     double timer = (clock()-start) / (double) CLOCKS_PER_SEC;
=======

>>>>>>> b9d770d0b4c6735d46e543e08818bd737f598a8b
	TrueGUI.paint(true);
	KnownGUI.updateSize();
	KnownGUI.paint(true);
#ifdef Simulation
<<<<<<< df918135b89afd757a08fcba7994348c814b76db
	cout<<"relay range used: "<<SimulationRelay::getRange()<<endl<<"Time Taken: "<<timer<<endl;;
#endif

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
        Log<<currentDateTime();
        Log<<argv[2]<<";";//method
        Log<<timer<<";";
        for(int i=0; i<Robotino.getKnownGrid().getRelays().size(); i++)
        {
        Log<< Robotino.getKnownGrid().getRelays()[i]->getPos()<<" ";
        }
        Log<<";";

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
=======
	SimulationRelay* temp =
			(SimulationRelay*) (AgentSmith.trueWorld.getRelay(1));
	cout << "relay range used: " << temp->getRange() << endl;
#endif
	char x;
	cin >> x;
>>>>>>> b9d770d0b4c6735d46e543e08818bd737f598a8b
}
