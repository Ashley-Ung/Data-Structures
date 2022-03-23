/**************************************************************************
 File name:  airport.c
 Author:     Ashley Ung
 Date:	     10.30.21
 Class:		   CS300
 Assignment: Airport Simulation
 Purpose:    An airport module that provides all the necessary
  			     functionality of the airport.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/airport.h"
#include "../../QueueADT/include/queue.h"
#include "../../PriorityQueueADT/include/pqueue.h"

/**************************************************************************
 Function: 	 	createAirport

 Description: If the airport can be created, then the airport exists and
 	 	 	        is empty; otherwise, if psAirport is NULL, the program
 	 	 	        exits.

 Parameters:	psAirport - pointer to an airport

 Returned:	 	None
 *************************************************************************/

void createAirport (AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		return;
	}

	queueCreate (&psAirport->sQPlaneToTakeoff);
	pqueueCreate (&psAirport->sPQPlaneToLand);

	psAirport->turnCounter = 0;
	psAirport->runwayCounter = 0;
	psAirport->sStats.takeoffCounter = 0;
	psAirport->sStats.groundTime = 0;
	psAirport->sStats.landingCounter = 0;
	psAirport->sStats.flightTime = 0;
	psAirport->sStats.crashCounter = 0;
	psAirport->landingWithZeroFuelCounter = 0;
	psAirport->sStats.fuelSum = 0;
	psAirport->sStats.crashSum = 0;
}

/**************************************************************************
 Function: 	 	terminateAirport

 Description: If the airport can be terminated, then the airport no
   	 	 	     	longer exists and is empty; otherwise, the airport does not
   	 	 	 			terminate so the entire program terminates.

 Parameters:	psAirport - pointer to an airport

 Returned:	 	None
 *************************************************************************/

void terminateAirport (AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		return;
	}

	queueTerminate (&psAirport->sQPlaneToTakeoff);
	pqueueTerminate (&psAirport->sPQPlaneToLand);
}

/**************************************************************************
 Function: 	 	enqueuePlane

 Description: Enters the new planes into their appropriate data
 	 	 	 				structures. Planes that want to land are enqueued into the
 	 	 	 				priority queue and planes that want to take off are enqueued
 	 	 	 				into the queue.

 Parameters:	psAirport     - pointer to an airport
 	 	 	 				planeTakeOffs - tracks the amount of planes that want to
 	 	 	 												take off
 	 	 	 				planeLands    - tracks the amount of planes that want to land
 	 	 	 				aPlaneFuel    - tracks the amount of fuel on board

 Returned:	 	None
 *************************************************************************/

void enqueuePlane (AirportPtr psAirport, int planeTakeoffs, int planeLands,
				   	 	 	 	 int aPlaneFuel[])
{
	const int DECREMENT_FUEL = -1;

	if (NULL == psAirport)
	{
		return;
	}

	psAirport->sStats.crashCounter = 0;

	for (int i = 0; i < planeTakeoffs; i++)
	{
		queueEnqueue (&psAirport->sQPlaneToTakeoff, &psAirport->turnCounter,
				      		sizeof (int));
	}

	for (int i = 0; i < planeLands; i++)
	{
		pqueueEnqueue (&psAirport->sPQPlaneToLand, &psAirport->turnCounter,
				       	 	 sizeof (int), aPlaneFuel[i]);
	}

	if (!pqueueIsEmpty (&psAirport->sPQPlaneToLand))
	{
		pqueueChangePriority (&psAirport->sPQPlaneToLand, DECREMENT_FUEL);
	}
}

/**************************************************************************
 Function: 	 	emergencyLanding

 Description: If the plane has a priority fuel, a fuel of zero; the plane
 	 	 	 				will have emergency landing; that is, the plane will be
 	 	 	 				prioritized to land first.

 Parameters:	psAirport  - pointer to an airport
 	 	 	 				planeFuel  - keeps track of the amount of fuel on board
 	 	 	 				aRunway    - tracks the amount of run ways occupied

 Returned:	 	None
 *************************************************************************/

void emergencyLanding (AirportPtr psAirport, int *planeFuel,
											 char aRunway[])
{
	const int MINIMUM_WAIT_TIME = 1;
	const int PLANE_ONE = 0;
	const int PLANE_TWO = 1;
	const int PLANE_THREE = 2;
	const int NUMBER_OF_RUNWAYS = 3;
	const char EMERGENCY_LANDING = 'E';
	const char RUNWAY_UNUSED = '-';
	const int ZERO_FUEL = 0;

	int buffer;

	if (NULL == psAirport)
	{
		return;
	}

	aRunway[PLANE_ONE] = RUNWAY_UNUSED;
	aRunway[PLANE_TWO] = RUNWAY_UNUSED;
	aRunway[PLANE_THREE] = RUNWAY_UNUSED;

	if (!pqueueIsEmpty (&psAirport->sPQPlaneToLand))
	{
		pqueuePeek (&psAirport->sPQPlaneToLand, &buffer, sizeof (int),
								planeFuel);
		while (psAirport->runwayCounter < NUMBER_OF_RUNWAYS &&
					 *planeFuel == ZERO_FUEL &&
					 !pqueueIsEmpty (&psAirport->sPQPlaneToLand))
		{
			pqueuePeek (&psAirport->sPQPlaneToLand, &buffer, sizeof (int),
									planeFuel);
			if (*planeFuel == 0)
			{
				pqueueDequeue (&psAirport->sPQPlaneToLand, &buffer, sizeof (int),
											 planeFuel);
				aRunway[psAirport->runwayCounter] = EMERGENCY_LANDING;
				psAirport->runwayCounter++;
				psAirport->sStats.landingCounter++;
				psAirport->landingWithZeroFuelCounter++;
				psAirport->sStats.flightTime += psAirport->turnCounter - buffer +
																				MINIMUM_WAIT_TIME;
				psAirport->sStats.fuelSum += *planeFuel;
			}
		}
	}

	if (!pqueueIsEmpty (&psAirport->sPQPlaneToLand))
	{
		pqueuePeek (&psAirport->sPQPlaneToLand, &buffer, sizeof (int),
								planeFuel);
		while (*planeFuel == ZERO_FUEL &&
				   !pqueueIsEmpty (&psAirport->sPQPlaneToLand))
		{
			pqueueDequeue (&psAirport->sPQPlaneToLand, &buffer, sizeof (int),
										 planeFuel);
			if (!pqueueIsEmpty (&psAirport->sPQPlaneToLand))
			{
				pqueuePeek (&psAirport->sPQPlaneToLand, &buffer, sizeof (int),
										planeFuel);
			}
			psAirport->sStats.crashCounter++;
			psAirport->sStats.landingCounter++;
			psAirport->sStats.crashSum ++;
			psAirport->sStats.flightTime += psAirport->turnCounter - buffer +
																			MINIMUM_WAIT_TIME;
		}
	}
}

/**************************************************************************
 Function: 	 	dequeuePlane

 Description: Services (land or take off) the plane at the head of the
 	 	 	 				larger queue and removes the plane from it's queue. If the
 	 	 	 				queues are the same size, a plane lands.

 Parameters:	psAirport  - pointer to an airport
 	 	 	 				planeFuel  - keeps track of the amount of fuel on board
 	 	 	 				aRunway    - tracks the amount of run ways occupied

 Returned:		Returns the value pointed to by planefuel.
 *************************************************************************/

void *dequeuePlane (AirportPtr psAirport, int *planeFuel, char aRunway[])
{
	const int MINIMUM_WAIT_TIME = 1;
	const int NUMBER_OF_RUNWAYS = 3;
	const int RESET_COUNTER = 0;
	const char LANDING = 'L';
	const char TAKEOFF = 'T';

	int buffer;

	if (NULL == psAirport)
	{
		exit (EXIT_FAILURE);
	}

	while (psAirport->runwayCounter < NUMBER_OF_RUNWAYS &&
			  (!airportIsEmpty (psAirport)))
	{
		if (pqueueSize (&psAirport->sPQPlaneToLand) >=
		    queueSize (&psAirport->sQPlaneToTakeoff))
		{
			if (!pqueueIsEmpty (&psAirport->sPQPlaneToLand))
			{
				pqueueDequeue (&psAirport->sPQPlaneToLand, &buffer, sizeof (int),
				               planeFuel);
				aRunway[psAirport->runwayCounter] = LANDING;
				psAirport->runwayCounter++;
				psAirport->sStats.landingCounter++;
				psAirport->sStats.flightTime += psAirport->turnCounter - buffer +
																				MINIMUM_WAIT_TIME;
				psAirport->sStats.fuelSum += *planeFuel;
			}
		}
		else
		{
			if (!queueIsEmpty (&psAirport->sQPlaneToTakeoff))
			{
				queueDequeue (&psAirport->sQPlaneToTakeoff, &buffer,
											sizeof (int));
				aRunway[psAirport->runwayCounter] = TAKEOFF;
				psAirport->runwayCounter++;
				psAirport->sStats.takeoffCounter++;
				psAirport->sStats.groundTime += psAirport->turnCounter -
																				buffer + MINIMUM_WAIT_TIME;
			}
		}
	}

	psAirport->runwayCounter = RESET_COUNTER;
	return planeFuel;
}

/**************************************************************************
 Function: 	 	airportIsEmpty

 Description: Checks if the airport is empty.

 Parameters:	psAirport - pointer to an airport

 Returned:	 	Returns true if the airport is empty, else, false.
 *************************************************************************/

bool airportIsEmpty (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		exit (EXIT_FAILURE);
	}

	return pqueueIsEmpty (&psAirport->sPQPlaneToLand) &&
		     queueIsEmpty (&psAirport->sQPlaneToTakeoff);
}

/**************************************************************************
 Function: 	  printHeader

 Description: A helper function that prints the airport simulation header.

 Parameters:  psAirport - pointer to an airport

 Returned:	  None
**************************************************************************/

void printHeader (AirportPtr psAirport)
{
	const int TWENTIETH = 20;

	if (0 == ((psAirport->turnCounter) % TWENTIETH))
	{
		printf ("%6s%23s%13s%13s%7s%8s%9s\n", "|", "Planes Added", "|", "Runways",
					  "|", "Queue", "Lengths");
		printf ("%4s%2s%8s%26s%2s%3s%4s%4s%7s%2s%8s%9s\n", "Time", "|", "Takeoff",
					  "Landing (Fuel Remaining)", "|", "1","2","3", "Crash", "|",
					  "Takeoff", "Landing");
		printf ("%4s%2s%8s%26s%2s%4s%4s%4s%6s%2s%8s%9s\n", "----", "|", "-------",
			      "------------------------", "|", "---", "---", "---", "-----", "|",
			      "-------", "-------");
	}
}

/**************************************************************************
 Function: 	 	printAirportData

 Description:	Prints the airport output to the screen

 Parameters:	psAirport     - pointer to an airport
 	 	 	 				planeTakeOffs - tracks the amount of planes that want to
 	 	 	 												take off
 	 	 	 				planeLands    - tracks the amount of planes that want to land
 	 	 	 				aPlaneFuel    - tracks the amount of fuel on board
 	 	 	 				aRunway       - tracks the amount of run ways occupied

 Returned:    None
 *************************************************************************/

void printAirportData (AirportPtr psAirport, int planeTakeOffs,
					   	 	 	 	 	 int planeLands, int aPlaneFuel[], char aRunway[])
{
	const int PLANE_ONE = 0;
	const int PLANE_TWO = 1;
	const int PLANE_THREE = 2;
	const int PLANE_NOT_ADDED = 0;
	const char PLANE_NOT_ADDED_DASH = '-';

	if (NULL == psAirport)
	{
		return;
	}

	printf ("%4d%2s", ++psAirport->turnCounter, "|");
	printf ("%8d", planeTakeOffs);
	printf ("%9d%2s", planeLands, "|");

	if (aPlaneFuel[PLANE_ONE] == PLANE_NOT_ADDED)
	{
		printf ("%4c", PLANE_NOT_ADDED_DASH);
	}
	else
	{
		printf ("%4d", aPlaneFuel[PLANE_ONE]);
	}

	if (aPlaneFuel[PLANE_TWO] == PLANE_NOT_ADDED)
	{
		printf ("%6c", PLANE_NOT_ADDED_DASH);
	}
	else
	{
		printf ("%6d", aPlaneFuel[PLANE_TWO]);
	}

	if (aPlaneFuel[PLANE_THREE] == PLANE_NOT_ADDED)
	{
		printf ("%5c", PLANE_NOT_ADDED_DASH);
	}
	else
	{
		printf ("%5d", aPlaneFuel[PLANE_THREE]);
	}

	printf ("%2s", "|");
	printf ("%3c", aRunway[PLANE_ONE]);
	printf ("%4c", aRunway[PLANE_TWO]);
	printf ("%4c", aRunway[PLANE_THREE]);
	printf ("%7d%2s", psAirport->sStats.crashCounter, "|");
	printf ("%8d", queueSize (&psAirport->sQPlaneToTakeoff));
	printf ("%9d\n", pqueueSize (&psAirport->sPQPlaneToLand));
}

/**************************************************************************
 Function: 	 	summaryStatistics

 Description: Summarizes the Airport data by tracking and calculating the
 	 	 	 	 	 	 	average take off waiting time, average landing waiting time,
 	 	 	 	 	 	 	average flying time remaining on landing, and number of
 	 	 	 	 	 	 	planes landing with zero. The summary statistics includes
 	 	 	 	 	 	 	those planes that crash.

 Parameters:  psAirport - pointer to an airport

 Returned:    None
 *************************************************************************/

void printSummaryStatistics (AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		return;
	}

	printf ("\nAverage takeoff waiting time: %g\n",
			    (double) psAirport->sStats.groundTime /
					psAirport->sStats.takeoffCounter);

	printf ("Average landing waiting time: %g\n",
			    (double) psAirport->sStats.flightTime /
				  (double) psAirport->sStats.landingCounter);

	printf ("Average flying time remaining on landing: %g\n",
			    (double) (psAirport->sStats.fuelSum /
			    psAirport->sStats.landingCounter));

	printf ("Number of planes landing with zero fuel: %d\n",
			    psAirport->landingWithZeroFuelCounter);

	printf ("Number of crashes: %d\n", psAirport->sStats.crashSum);
}
