
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

int main()
{
	//make agent
	#ifdef Simulation
		Agent* AgentSmith= new SimulationAgent();
		static Grid trueworld;

		//read file about trueworld and relay
		Coordinate goalLocation= readfile(trueworld, GRIDFILE);
		readfile(trueworld, (SimulationAgent*)AgentSmith, RELAYFILE);

		//make GUI
		GridGUI True = GridGUI(&trueworld, "True grid",20);

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
