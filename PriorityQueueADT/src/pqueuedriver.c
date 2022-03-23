/**************************************************************************
 File name:  pqueuedriver.c
 Author:     Ashley Ung
 Date:	     10.11.21
 Class:		   CS300
 Assignment: Priority Queue
 Purpose:    Test driver for priority queue backed by a list ADT.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#include "../include/pqueue.h"

/**************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	pszStr - the message to print

 Returned:	 	none
**************************************************************************/

static void success (char *pszStr)
{
	printf ("SUCCESS: %s\n", pszStr);
}

/**************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	pszStr - the message to print

 Returned:	 	none
**************************************************************************/

static void failure (char *pszStr)
{
	printf ("FAILURE: %s\n", pszStr);
}

/**************************************************************************
 Function: 	 	assert

 Description: If the expression is true, assert success; otherwise,
              assert failure

 Parameters:	bExpression - the expression to evaluate
 	 	 	 				pTrue 		  - the true boolean
 	 	 	 				pFalse 		  - the false boolean

 Returned:	 	none
**************************************************************************/

static void assert (bool bExpression, char *pTrue, char *pFalse)
{
	if (bExpression)
	{
		success (pTrue);
	}
	else
	{
		failure (pFalse);
	}
}

/**************************************************************************
 Function: 	 	makeBigPriorityQueue

 Description: Creates a big priority queue.

 Parameters:	psPQueue - a pointer to a priority queue
 	 	 	 				max      - the maximum number of elements in the priority
 	 	 	 	 	 	   	 	 	 	 	 queue.

 Returned:	 	none
**************************************************************************/

void makeBigPriorityQueue (PriorityQueuePtr psPQueue, int max)
{
	for (int i = 0; i < max; ++i)
	{
		pqueueEnqueue (psPQueue, &i, sizeof (int), i);
	}

	assert (max == pqueueSize (psPQueue), "The priority queue size is max",
			    "The priority queue size is not max");

	assert (!pqueueIsEmpty (psPQueue), "The priority queue is NOT empty",
			    "The priority queue is empty");
}

/**************************************************************************
 Function: 	 	printList

 Description: A helper function that prints the lists' data and the
              priority number in the queue.

 Parameters:	psList - the list passed in

 Returned:	 	none
**************************************************************************/

//static void printList (ListPtr *psList)
//{
//	PriorityQueueElement sPQElement;
//	int numElements = lstSize (psList);
//	int data;
//	int priority;
//
//	printf ("\n\nPrinting List (data,priority): ");
//
//	lstFirst (psList);
//
//	for (int i = 0; i < numElements; i++)
//	{
//		lstPeek (psList, &sPQElement, sizeof (PriorityQueueElement));
//		priority = sPQElement.priority;
//		data = *((int*)sPQElement.pData);
//		printf ("%d,%d-", data, priority);
//		lstNext (psList);
//	}
//}

/**************************************************************************
 Function: 	 	main

 Description: Tests all the functionality of the priority queue.

 Parameters:	none

 Returned:	 	Exit Status
**************************************************************************/

int main ()
{
	const int SIZE_ZERO = 0;
	const int SIZE_ONE = 1;
	const int SIZE_TWO = 2;
	const int REINITIALIZE_BUFFER = 0;
	const int BIG_PQ_SIZE = 1000;
	const char LETTER_Z = 'Z';
	const char LETTER_A = 'A';

	PriorityQueue sTheQueue;
	PriorityQueue sTheSecondQueue;
	int valOne = 1;
	int valTwo = 2;
	int highPriorityVal = 0;
	int priorityBuffer;
	int secondPriorityBuffer;
	int buffer;
	double doubleBuffer;
	float floatBuffer;
	short shortBuffer;
	long long longBuffer;
	char charBuffer;
	int secondBuffer;
	int maxInt = INT_MAX;
	char maxChar = CHAR_MAX;
	double maxDouble = DBL_MAX;
	float maxFloat = FLT_MAX;
	bool bTrue = true;
	short maxShort = SHRT_MAX;
	long long maxLongLong = LLONG_MAX;
	char letter;
	char storedLetter;

	puts ("Program Start\n");
	puts ("SUCCESS TESTS:\n");

	//Checking if the error messages have been loaded
	pqueueLoadErrorMessages ();
	success ("Loaded Priority Queue Error Messages");
	lstLoadErrorMessages ();
	success ("Loaded List Error Messages");

	//Testing Errors
	//Testing pqueueCreate for error no priority queue created
	//pqueueCreate (NULL);
	//Testing pqueueSize for error invalid priority queue
	//pqueueSize (NULL);
	//Testing pqueueIsEmpty for error invalid priority queue
	//pqueueIsEmpty (NULL);
	//Testing pqueueEnqueue for error invalid priority queue
	//pqueueEnqueue (NULL, &valOne, sizeof (int), valOne);
	//Testing pqueueEnqueue for error null pointer
	//pqueueEnqueue (&sTheQueue, NULL, sizeof (int), valOne);
	//Testing pqueuePeek for error invalid priority queue
	//pqueuePeek (NULL, &valOne, sizeof (int), &valOne);
	//Testing pqueuePeek for error null pointer
	//pqueuePeek (&sTheQueue, NULL, sizeof (int), &valOne);
	//Testing pqueueDequeue for error invalid priority queue
	//pqueueDequeue (NULL, &valOne, sizeof (int), &valOne);
	//Testing pqueueDequeue for error null pointer
	//pqueueDequeue (&sTheQueue, NULL, sizeof (int), &valOne);
	//Testing pqueueTerminate for error invalid priority queue
	//pqueueTerminate (NULL);
	//Testing pqueueChangePriority for error invalid priority queue
	//pqueueChangePriority (NULL, valOne);

	//Checking pqueueCreate
	pqueueCreate (&sTheQueue);
	success ("Priority Queue Created");

	//Checking pqueueIsEmpty
	assert (pqueueIsEmpty (&sTheQueue), "Queue is empty",
			    "Queue is not empty");

	//Checking pqueueSize
	assert (pqueueSize (&sTheQueue) == SIZE_ZERO,
		      "Queue size is 0", "Queue size is NOT 0");

	//Checking pqueueEnqueue
	pqueueEnqueue (&sTheQueue, &valOne, sizeof (int), highPriorityVal);
	assert (pqueueSize (&sTheQueue) == SIZE_ONE,
		      "Queue size is 1", "Queue size is NOT 1");
	assert (!pqueueIsEmpty (&sTheQueue), "Queue is not empty",
			    "Queue is empty");

	//Checking pequeueChangePriority, pqueuePeek & pqueueDequeue
	pqueueChangePriority (&sTheQueue, 2);
	pqueuePeek (&sTheQueue, &buffer, sizeof (int), &priorityBuffer);
	assert (priorityBuffer == 2, "Priority int correct",
			    "Priority int incorrect");
	pqueuePeek (&sTheQueue, &buffer, sizeof (int), &priorityBuffer);
	assert (buffer == valOne, "The peeked data is correct.",
			    "The peeked data is incorrect.");
	buffer = REINITIALIZE_BUFFER;
	pqueueEnqueue (&sTheQueue, &valTwo, sizeof (int), highPriorityVal);
	assert (pqueueSize (&sTheQueue) == SIZE_TWO,
		      "Queue size is 2", "Queue size is NOT 2");
	pqueueChangePriority (&sTheQueue, 100);
	pqueuePeek (&sTheQueue, &buffer, sizeof (int), &priorityBuffer);
	assert (priorityBuffer == 100, "Priority int correct",
			    "Priority int incorrect");
	pqueueDequeue (&sTheQueue, &buffer, sizeof (int), &priorityBuffer);
	assert (buffer == valTwo, "The peeked data is correct.",
			    "The peeked data is incorrect");
	assert (pqueueSize (&sTheQueue) == SIZE_ONE,
		      "Queue size is 1", "Queue size is NOT 1");
	pqueuePeek (&sTheQueue, &buffer, sizeof (int), &priorityBuffer);
	assert (buffer == valOne, "The peeked data is correct.",
			    "The peeked data is incorrect.");
	buffer = REINITIALIZE_BUFFER;
	pqueueTerminate (&sTheQueue);
	success ("Priority Queue Terminated");

	//Checking pqueueEnqueue using different data types
	pqueueCreate (&sTheQueue);
	success ("Priority Queue Created");

	assert (pqueueIsEmpty (&sTheQueue), "Queue is empty",
			    "Queue is not empty");

	maxInt = 0;
	pqueueEnqueue (&sTheQueue, &maxInt, sizeof (int), highPriorityVal);
	pqueuePeek (&sTheQueue, &buffer, sizeof (int), &priorityBuffer);
	assert (buffer == maxInt, "Max int correct", "Max int incorrect");
	assert (priorityBuffer == highPriorityVal, "Priority int correct",
			    "Priority int incorrect");
	assert (pqueueSize (&sTheQueue) == SIZE_ONE,
		      "Queue size is 1", "Queue size is NOT 1");
	buffer = REINITIALIZE_BUFFER;
	pqueueDequeue (&sTheQueue, &buffer, sizeof (int), &highPriorityVal);
	assert (buffer == maxInt, "The peeked data is correct.",
			    "The peeked data is incorrect");
	assert (pqueueSize (&sTheQueue) == SIZE_ZERO,
		      "Queue size is 0", "Queue size is NOT 0");

	pqueueEnqueue (&sTheQueue, &maxChar, sizeof (char), highPriorityVal);
	pqueuePeek (&sTheQueue, &charBuffer, sizeof (char), &priorityBuffer);
	assert (CHAR_MAX == maxChar, "Max char correct", "Max char incorrect");
	assert (priorityBuffer == highPriorityVal, "Priority int correct",
			    "Priority int incorrect");
	charBuffer = REINITIALIZE_BUFFER;
	pqueueDequeue (&sTheQueue, &charBuffer, sizeof (char), &highPriorityVal);
	assert (charBuffer == maxChar, "The peeked character is correct.",
			    "The peeked character is incorrect");
	assert (pqueueSize (&sTheQueue) == SIZE_ZERO,
		      "Queue size is 0", "Queue size is NOT 0");

	pqueueEnqueue (&sTheQueue, &maxDouble, sizeof (double), highPriorityVal);
	pqueuePeek (&sTheQueue, &doubleBuffer, sizeof (double), &priorityBuffer);
	assert (DBL_MAX == maxDouble, "Max double correct",
			    "Max double incorrect");
	assert (priorityBuffer == highPriorityVal, "Priority int correct",
			    "Priority int incorrect");

	pqueueEnqueue (&sTheQueue, &maxFloat, sizeof (float), 1);
	pqueuePeek (&sTheQueue, &floatBuffer, sizeof (float), &priorityBuffer);
	assert (FLT_MAX == maxFloat, "Max float correct", "Max float incorrect");
	assert (priorityBuffer == highPriorityVal, "Priority int correct",
			    "Priority int incorrect");

	pqueueEnqueue (&sTheQueue, &bTrue, sizeof (bool), highPriorityVal);
	pqueuePeek (&sTheQueue, &bTrue, sizeof (bool), &priorityBuffer);
	assert (true == bTrue, "Max TRUE correct", "Max TRUE incorrect");
	assert (priorityBuffer == highPriorityVal, "Priority int correct",
			    "Priority int incorrect");

	pqueueEnqueue (&sTheQueue, &maxShort, sizeof (short), highPriorityVal);
	pqueuePeek (&sTheQueue, &shortBuffer, sizeof (short), &priorityBuffer);
	assert (SHRT_MAX == maxShort, "Max short correct",
			    "Max short incorrect");
	assert (priorityBuffer == highPriorityVal, "Priority int correct",
			    "Priority int incorrect");

	pqueueEnqueue (&sTheQueue, &maxLongLong, sizeof (long long),
			           highPriorityVal);
	pqueuePeek (&sTheQueue, &longBuffer, sizeof (long long),
			        &priorityBuffer);
	assert (LLONG_MAX == maxLongLong, "Max long long correct",
			   "Max long long incorrect");
	assert (priorityBuffer == highPriorityVal, "Priority int correct",
			    "Priority int incorrect");

	pqueueTerminate (&sTheQueue);
	success ("Priority Queue Terminated");

  //Creating 2 Queues
	pqueueCreate (&sTheQueue);
	success ("First Priority Queue Created");
	pqueueCreate (&sTheSecondQueue);
	success ("Second Priority Queue Created");

	assert (pqueueIsEmpty (&sTheQueue), "First Priority Queue is empty",
			    "First Priority Queue is not empty");
	assert (pqueueIsEmpty (&sTheSecondQueue),
					"Second Priority Queue is empty",
			    "Second Priority Queue is not empty");

	assert (pqueueSize (&sTheQueue) == SIZE_ZERO,
		      "First Priority Queue size is 0",
					"First Priority Queue size is NOT 0");
	assert (pqueueSize (&sTheSecondQueue) == SIZE_ZERO,
		      "Second Priority Queue size is 0",
					"Second Priority Queue size is NOT 0");

	makeBigPriorityQueue (&sTheQueue, BIG_PQ_SIZE);
	makeBigPriorityQueue (&sTheSecondQueue, BIG_PQ_SIZE);

	assert (pqueueSize (&sTheQueue) == BIG_PQ_SIZE,
		      "First Priority Queue size is 1000",
					"First Priority Queue size is NOT 1000");
	assert (pqueueSize (&sTheSecondQueue) == BIG_PQ_SIZE,
		      "Second Priority Queue size is 1000",
					"Second Priority Queue size is NOT 1000");

	while (!pqueueIsEmpty (&sTheQueue))
	{
		pqueueDequeue (&sTheQueue, &buffer, sizeof (int), &priorityBuffer);
		pqueueDequeue (&sTheSecondQueue, &secondBuffer, sizeof (int),
				           &secondPriorityBuffer);
	}
	assert (buffer == secondBuffer, "Big PQ buffers match",
			    "Big PQ buffers do not match");
	assert (priorityBuffer == secondPriorityBuffer,
			    "Big PQ priority buffers match",
					"Big PQ priority buffers do not match");
	assert (pqueueSize (&sTheQueue) == SIZE_ZERO,
		      "First Priority Queue size is 0",
					"First Priority Queue size is NOT 0");
	assert (pqueueSize (&sTheQueue) == SIZE_ZERO,
		      "Second Priority Queue size is 0",
					"Second Priority Queue size is NOT 0");

	pqueueTerminate (&sTheQueue);
	success ("First Priority Queue Terminated");
	pqueueTerminate (&sTheSecondQueue);
	success ("Second Priority Queue Terminated");

	//Enqueue & Dequeue the alphabets
	pqueueCreate (&sTheQueue);
	success ("Priority Queue Created");

	for (letter = LETTER_A ; letter <= LETTER_Z; ++letter)
	{
		pqueueEnqueue (&sTheQueue, &maxChar, sizeof (char), highPriorityVal);
		pqueuePeek (&sTheQueue, &storedLetter, sizeof (char), &priorityBuffer);

		if (letter != storedLetter)
		{
			assert (letter != storedLetter, "Valid letter data",
				      "Invalid letter data");
		}
	}

	assert (priorityBuffer == 0, "Priority int correct",
			    "Priority int incorrect");
	pqueueChangePriority (&sTheQueue, 14);
	pqueuePeek (&sTheQueue, &charBuffer, sizeof (char), &priorityBuffer);
	assert (priorityBuffer == 14, "Priority int correct",
			    "Priority int incorrect");

	for (letter = LETTER_Z; letter >= LETTER_A; --letter)
	{
		pqueueDequeue (&sTheQueue, &storedLetter, sizeof (char),
									 &priorityBuffer);
		if (letter != storedLetter)
		{
			assert (letter != storedLetter, "Valid letter data",
				      "Invalid letter data");
		}
	}

	assert (pqueueIsEmpty (&sTheQueue), "First Priority Queue is empty",
			    "First Priority Queue is not empty");
	assert (pqueueIsEmpty (&sTheSecondQueue),
					"Second Priority Queue is empty",
			    "Second Priority Queue is not empty");

	assert (pqueueSize (&sTheQueue) == SIZE_ZERO,
		      "First Priority Queue size is 0",
					"First Priority Queue size is NOT 0");
	assert (pqueueSize (&sTheSecondQueue) == SIZE_ZERO,
		      "Second Priority Queue size is 0",
					"Second Priority Queue size is NOT 0");

	pqueueTerminate (&sTheSecondQueue);
	success ("Priority Queue Terminated, Horray :-)");

	return EXIT_SUCCESS;
}


