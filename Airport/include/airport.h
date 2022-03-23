/**************************************************************************
 File name:		airport.h
 Author:      Ashley Ung
 Date:		    10/30/2021
 Class:       CS300
 Assignment:  Airport Simulation
 Purpose:     This file defines the constants, data structures, and
              function prototypes for implementing the airport
              simulation.
 *************************************************************************/

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include <stdbool.h>
#include "../../QueueADT/include/queue.h"

//*************************************************************************
// Constants
//*************************************************************************

#define RUNWAYS 3

//*************************************************************************
// User-defined types
//*************************************************************************

typedef struct Statistics
{
	int takeoffCounter;
	int landingCounter;
	double groundTime;
	double flightTime;
	double fuelSum;
	int crashCounter;
	int crashSum;
} Statistics;

typedef struct Airport *AirportPtr;
typedef struct Airport
{
	Queue sQPlaneToTakeoff;
	PriorityQueue sPQPlaneToLand;
	Statistics sStats;
	int turnCounter;
	int runwayCounter;
	int landingWithZeroFuelCounter;
	char aRunway[RUNWAYS];
} Airport;

/**************************************************************************
* Allocation and Deallocation
**************************************************************************/

extern void createAirport (AirportPtr psAirport);

extern void terminateAirport (AirportPtr psAirport);

/**************************************************************************
* Airplane Landing and Take off Operations
**************************************************************************/

extern void enqueuePlane (AirportPtr psAirport, int planeTakeoffs,
						  						int planeLands, int aPlaneFuel[]);

extern void emergencyLanding (AirportPtr psAirport, int *planeFuel,
		                      		char aRunway[]);

extern void *dequeuePlane (AirportPtr psAirport, int *planeFuel,
						   	 	 	 	 	 	 char aRunway[]);

/**************************************************************************
* Checking number of elements in airport
**************************************************************************/

extern bool airportIsEmpty (const AirportPtr psAirport);

/**************************************************************************
* Printing Airport data
**************************************************************************/

extern void printHeader (AirportPtr psAirport);

extern void printAirportData (AirportPtr psAirport, int planeTakeOffs,
							  							int planeLands, int aPlaneFuel[],
															char aRunway[]);

extern void printSummaryStatistics (AirportPtr psAirport);

#endif /* AIRPORT_H_ */
