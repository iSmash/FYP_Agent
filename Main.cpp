
#define GRIDFILE "RelayTestGrid"
#define RELAYFILE "RelayTestRelay"

#define Simulation
//if commented out then implementation
 
int main()
{
	//make agent
	#ifdef Simulation
		Agent AgentSmith= simulationAgent();
		static Grid trueworld;
		//read file 
		Coordinate goalLocation= readfile(AgentSmith, GRIDFILE);

	#else	
		Agent AgentSmith= ImpementAgent();
	#endif	
	
		readfile(
	
	//make GUI
	#ifdef Simulation
		GridGUI True = GridGUI(AgentSmith.getTrue());
	#endif
;
	//Agent run
	while(AgentSmith.done()) //loop until robot job is done. 
	{
		AgentSmith.findPath(goalLocation);
		AgentSmith.tryPath();
		
	}
}
