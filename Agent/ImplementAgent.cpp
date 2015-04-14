void SimulationAgent::setRelayCount(int numberofRelays)
{
	//will do nothing if already has more then number told. but this should only be called on startups once.
	
	//has too few?
 	while(heldRelays.size()<numberofRelays)
	{
		heldRelays.push_back( ImpementRelay());
	}
}
