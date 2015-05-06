/**                                                                 *
 *   Read in header file, decleration of readin methods             *
 *   Navigating robot                                               *
 *   @author Phillip C. Smith                                       *
 *   @version 1.0                                                   *
 *   @date 23/3/13                                                  *
 *                                                                **/
 #ifndef READIN_H
#define READIN_H

#include "Grid/Grid.h"
#include "Agent/SimulationAgent.h"


using namespace environment;
using namespace Agentspace;

        /**
        read the text file, adding the test case data, grid size, wall locations, starting point, goal
        @param grid, the grid to be resized and added to.
        */
       RelativeCoordinate readfileGrid(SimulationAgent &agent, string filename); //read file for grid creation, simultion only
       void readfileRelay(SimulationAgent &agent, string filename); //read file for number of relays and relay sizes.

	   //randomly generate a grid to explore (still buggy, but not core)
	   void makefile();

#endif // READIN_H
