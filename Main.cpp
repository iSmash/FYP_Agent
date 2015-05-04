/* Main.cpp
 * Author:  Phil Smith
 * Date:    20150411
 * Version: inf
 *
 */


#define GRIDFILE "RelayTestGrid"
#define RELAYFILE "RelayTestRelay.txt"
#define MethodType 1

#include "Simulation.h"

#include "Agent/ImplementAgent.h"
#include "FileRead.h"
#include "GUI/GridGUI.h"

using namespace Agentspace;
using namespace environment;
using namespace std;
int mainint main(int argc, char* argv[]) {
	//make agent
#ifdef Simulation
	cout<<"Simulation"<<endl;
	SimulationAgent* AgentSmith=  new SimulationAgent();


	//read file about trueworld and relay
	RelativeCoordinate relativeToGoal =readfileGrid(AgentSmith, GRIDFILE);

	AgentSmith->setGoal(relativeToGoal);/**using magic we find where the goal is */

	readfileRelay(AgentSmith, RELAYFILE);


	GridGUI TrueGUI = GridGUI(&AgentSmith->trueworld,5);
	GridGUI  KnownGUI=GridGUI(AgentSmith->getKnownGrid(),500);
	AgentSmith->lookAround();










#else
	Agent* AgentSmith= new ImpementAgent();

	//read file of just relay for agent
	readfileRelay(AgentSmith, RELAYFILE);
#endif

	AgentSmith->defineDeploymentMethod(MethodType);


	//Agent run
	while(!AgentSmith->done()) //loop until robot job is done.
	{
	    TrueGUI.paint();
		KnownGUI.updateSize();
		KnownGUI.paint();
		AgentSmith->findPath();
		AgentSmith->tryPath();
	}

	TrueGUI.paint(true);
		KnownGUI.updateSize();
		KnownGUI.paint(true);
	char x;
	cin>>x;
}
