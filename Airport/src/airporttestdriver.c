/**************************************************************************
 File name:  airporttestdriver.c
 Author:     Ashley Ung
 Date:	     10.30.21
 Class:		   CS300
 Assignment: Airport Simulation
 Purpose:    A test driver used to thoroughly test the functionality of
  			     the airport simulation.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../../QueueADT/include/queue.h"
#include "../include/airport.h"

/**************************************************************************
 Function: 	  main

 Description: Tests all the functionality of the airport simulation.

 Parameters:  argc - number of command line arguments
 	 	 	 	 	 	 	argv - the command line arguments

 Returned:	  Exit Status
**************************************************************************/

int main (int argc, char **argv)
{
	const int REINITIALIZE_VALUE = 0;
	const int NUMBER_OF_RUNWAYS = 3;
	const int PLANE_ONE = 0;
	const int PLANE_TWO = 1;
	const int PLANE_THREE = 2;

	int planeLands;
	int planeTakeOffs;
	int priorityFuel = 0;
	char aRunway[NUMBER_OF_RUNWAYS];
	int aPlaneFuel[NUMBER_OF_RUNWAYS];

	queueLoadErrorMessages ();
	pqueueLoadErrorMessages ();
	lstLoadErrorMessages ();

	Airport sTheAirport;
	createAirport (&sTheAirport);

	FILE* inFile = NULL;

	inFile = fopen (argv[1], "r");

	if (inFile == NULL)
	{
		printf ("Could not open file");
		exit (EXIT_FAILURE);
	}

	while (!feof (inFile) || !(airportIsEmpty (&sTheAirport)))
	{
		printHeader (&sTheAirport);
		planeTakeOffs = REINITIALIZE_VALUE;
		planeLands = REINITIALIZE_VALUE;
		aPlaneFuel[0] = REINITIALIZE_VALUE;
		aPlaneFuel[1] = REINITIALIZE_VALUE;
		aPlaneFuel[2] = REINITIALIZE_VALUE;

		fscanf (inFile, "%d %d %d %d %d", &planeTakeOffs, &planeLands,
						&aPlaneFuel[PLANE_ONE], &aPlaneFuel[PLANE_TWO],
						&aPlaneFuel[PLANE_THREE]);

		enqueuePlane (&sTheAirport, planeTakeOffs, planeLands, aPlaneFuel);
		emergencyLanding (&sTheAirport, &priorityFuel, aRunway);
		dequeuePlane (&sTheAirport, &priorityFuel, aRunway);
		printAirportData (&sTheAirport, planeTakeOffs, planeLands, aPlaneFuel,
				          		aRunway);
	}

	printSummaryStatistics (&sTheAirport);
	terminateAirport (&sTheAirport);

	fclose (inFile);

	return 0;
}
