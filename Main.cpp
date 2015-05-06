/* Main.cpp
 * Author:  Phil Smith
 * Date:    20150411
 * Version: inf
 *
 */


#define GRIDFILE "RelayTestGrid"
#define RELAYFILE "RelayTestRelay.txt"


#include "Simulation.h"

#include "Agent/ImplementAgent.h"
#include "FileRead.h"
#include "GUI/GridGUI.h"

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

	//Agent run
	try{
		while(!AgentSmith.done()) //loop until robot job is done.
		{
			TrueGUI.paint();
			KnownGUI.updateSize();
			KnownGUI.paint();
			AgentSmith.findPath();

			//char x;cin>>x;
		}
	}
	catch(string s){cout<<s<<endl;}

	TrueGUI.paint(true);
	KnownGUI.updateSize();
	KnownGUI.paint(true);
#ifdef Simulation
	SimulationRelay* temp=(SimulationRelay*)(AgentSmith.trueWorld.getRelay(1));
	cout<<"relay range used: "<<temp->getRange()<<endl;
#endif
	char x;
	cin>>x;
}
