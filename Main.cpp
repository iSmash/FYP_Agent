
#define GRIDFILE "RelayTestGrid.txt"
#define RELAYFILE "RelayTestRelay.txt"

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


		//read file about trueworld and relay
		Coordinate goalLocation= readfileGrid(AgentSmith, GRIDFILE);

/**test **/
		  Relay* asdf = new SimulationRelay();
        asdf->updatePos(Coordinate(1,7));
        AgentSmith->trueworld.placeRelay(asdf);

          Relay* asdf2 = new SimulationRelay();
        asdf2->updatePos(Coordinate(1,4));
        AgentSmith->trueworld.placeRelay(asdf2);
/**end test **/

		readfileRelay(AgentSmith, RELAYFILE);

/**test **/
        AgentSmith->trueworld[Coordinate(19,19)].addContent(ContentType::Unknown);
        AgentSmith->trueworld[Coordinate(18,19)].addContent(ContentType::Unknown);
        AgentSmith->trueworld[Coordinate(19,18)].addContent(ContentType::Unknown);
        AgentSmith->trueworld[Coordinate(18,17)].addContent(ContentType::Unknown);
        AgentSmith->trueworld[Coordinate(17,18)].addContent(ContentType::Unknown);
        AgentSmith->trueworld[Coordinate(18,18)].addContent(ContentType::Unknown);
     AgentSmith->trueworld[Coordinate(17,19)].addContent(ContentType::Unknown);
        AgentSmith->trueworld[Coordinate(19,17)].addContent(ContentType::Unknown);

        AgentSmith->trueworld[Coordinate(1,2)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(1,3)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(1,4)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(1,5)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(1,6)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(1,7)].addContent(ContentType::Robot);
     AgentSmith->trueworld[Coordinate(1,8)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(1,9)].addContent(ContentType::Robot);
AgentSmith->trueworld[Coordinate(2,9)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(3,9)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(4,9)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(5,9)].addContent(ContentType::Robot);
         AgentSmith->trueworld[Coordinate(3,9)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(4,9)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(5,9)].addContent(ContentType::Robot);
         AgentSmith->trueworld[Coordinate(6,9)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(7,9)].addContent(ContentType::Robot);
        AgentSmith->trueworld[Coordinate(7,8)].addContent(ContentType::Robot);
         AgentSmith->trueworld[Coordinate(7,7)].addContent(ContentType::Robot);

           AgentSmith->trueworld[Coordinate(2,2)].addContent(ContentType::Wall);
            AgentSmith->trueworld[Coordinate(2,3)].addContent(ContentType::Wall);
             AgentSmith->trueworld[Coordinate(2,4)].addContent(ContentType::Wall);
             AgentSmith->trueworld[Coordinate(2,5)].addContent(ContentType::Wall);
             AgentSmith->trueworld[Coordinate(2,6)].addContent(ContentType::Wall);
              AgentSmith->trueworld[Coordinate(2,7)].addContent(ContentType::Wall);
            AgentSmith->trueworld[Coordinate(2,8)].addContent(ContentType::Wall);
             AgentSmith->trueworld[Coordinate(3,4)].addContent(ContentType::Wall);
             AgentSmith->trueworld[Coordinate(3,5)].addContent(ContentType::Wall);
             AgentSmith->trueworld[Coordinate(3,6)].addContent(ContentType::Wall);
/** end test **/

    GridGUI TrueGUI = GridGUI(&AgentSmith->trueworld,5);
         GridGUI  KnownGUI=GridGUI(AgentSmith->getKnownGrid(),500);
       TrueGUI.paint();
       AgentSmith->lookAround();

       KnownGUI.updateSize();

       KnownGUI.paint();

	#else
		Agent* AgentSmith= new ImpementAgent();

		//read file of just relay for agent
		readfileRelay(AgentSmith, RELAYFILE);
	#endif



;
	//Agent run
	//while(AgentSmith->done()) //loop until robot job is done.
	{
		AgentSmith->findPath(goalLocation);
		AgentSmith->tryPath();

	}
	char x;
	cin>>x;
}
