
#define GRIDFILE "RelayTestGrid.txt"
#define RELAYFILE "RelayTestRelay.txt"

#define Simulation
//if commented out then implementation

#include "Agent/ImplementAgent.h"
#include "Agent/SimulationAgent.h"
#include "FileRead.h"
#include "GUI/GridGUI.h"

using namespace Agentspace;
using namespace environment;
using namespace std;
int main()
{
	//make agent
	#ifdef Simulation
        cout<<"Simulation"<<endl;
		Agent* AgentSmith= new SimulationAgent();
		static Grid trueworld;

		//read file about trueworld and relay
		Coordinate goalLocation= readfile(trueworld, GRIDFILE);
		readfile(trueworld, (SimulationAgent*)AgentSmith, RELAYFILE);
        cout<<trueworld.getLast().getColumn()<<endl;

		//make GUI
		GridGUI TrueGUI = GridGUI(&trueworld, "True grid",5);
        TrueGUI.paint();
	#else
		Agent* AgentSmith= new ImpementAgent();

		//read file of just relay for agent
		readfile(null, AgentSmith, RELAYFILE);
	#endif



;
	//Agent run
	while(AgentSmith->done()) //loop until robot job is done.
	{
		AgentSmith->findPath(goalLocation);
		AgentSmith->tryPath();

	}
}
