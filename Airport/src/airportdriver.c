/**************************************************************************
 File name:  airportdriver.c
 Author:     Ashley Ung
 Date:	     10.31.21
 Class:		   CS300
 Assignment: Airport Simulation
 Purpose:    A program to run the airport simulation.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../../QueueADT/include/queue.h"
#include "../include/airport.h"

/**************************************************************************
 Function: 	 	main

 Description: Runs the airport simulation.

 Parameters:	argc - number of command line arguments
 	 	 	 	 	 	 	argv - the command line arguments

 Returned:	 	Exit Status
**************************************************************************/

int main (int argc, char **argv)
{
	const int RESET_VALUE = 0;
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
		planeTakeOffs = RESET_VALUE;
		planeLands = RESET_VALUE;
		aPlaneFuel[PLANE_ONE] = RESET_VALUE;
		aPlaneFuel[PLANE_TWO] = RESET_VALUE;
		aPlaneFuel[PLANE_THREE] = RESET_VALUE;

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
