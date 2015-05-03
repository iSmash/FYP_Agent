/* Main.cpp
 * Author:  Phil Smith
 * Date:    20150411
 * Version: inf
 *
 */


#define GRIDFILE "RelayTestGrid.txt"
#define RELAYFILE "RelayTestRelay.txt"
#define MethodType 1

#include "Simulation.h"

#include "Agent/ImplementAgent.h"
#include "FileRead.h"


using namespace Agentspace;
using namespace environment;
using namespace std;
int main()
{
	//make agent
#ifdef Simulation
	cout<<"Simulation"<<endl;
	SimulationAgent* AgentSmith=  new SimulationAgent();
	/**
Relay* basesStation = new SimulationRelay();
            basesStation->updatePos(Coordinate(0,0));
             AgentSmith->getKnownGrid()->placeRelay(basesStation);
	 */

	//read file about trueworld and relay
	RelativeCoordinate relativeToGoal =readfileGrid(AgentSmith, GRIDFILE);
	AgentSmith->setGoal(relativeToGoal);/**using magic we find where the goal is */

	readfileRelay(AgentSmith, RELAYFILE);


	//GridGUI TrueGUI = GridGUI(&AgentSmith->trueworld,5);
	//GridGUI  KnownGUI=GridGUI(AgentSmith->getKnownGrid(),500);
	//TrueGUI.paint();
	AgentSmith->lookAround();

	//KnownGUI.updateSize();

	//KnownGUI.paint();








#else
	Agent* AgentSmith= new ImpementAgent();

	//read file of just relay for agent
	readfileRelay(AgentSmith, RELAYFILE);
#endif

	AgentSmith->defineDeploymentMethod(MethodType);


	;
	//Agent run
	while(!AgentSmith->done()) //loop until robot job is done.
	{
		AgentSmith->findPath();
		AgentSmith->tryPath();
		//TrueGUI.paint();
	//	KnownGUI.updateSize();
	//	KnownGUI.paint();


	}
	char x;
	cin>>x;
}
