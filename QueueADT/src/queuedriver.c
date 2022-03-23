/**************************************************************************
 File name:  queuedriver.c
 Author:     Ashley Ung
 Date:	     10.24.21
 Class:		   CS300
 Assignment: Queue
 Purpose:    Test driver for queue backed by a priority queue ADT.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#include "../include/queue.h"

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
 Function: 	 	makeBigQueue

 Description: Creates a big queue.

 Parameters:	psQueue  - a pointer to a queue
 	 	 	 				max      - the maximum number of elements in the queue.

 Returned:	 	none
**************************************************************************/

void makeBigQueue (QueuePtr psQueue, int max)
{
	for (int i = 0; i < max; ++i)
	{
		queueEnqueue (psQueue, &i, sizeof (int));
	}

	assert (max == queueSize (psQueue), "The queue size is max",
			    "The queue size is not max");

	assert (!queueIsEmpty (psQueue), "The queue is NOT empty",
			    "The queue is empty");
}

/**************************************************************************
 Function: 	 	main

 Description: Tests all the functionality of the queue.

 Parameters:	none

 Returned:	 	Exit Status
**************************************************************************/

int main ()
{
	const int SIZE_ZERO = 0;
	const int SIZE_ONE = 1;
	const int SIZE_TWO = 2;
	const int MAX_ITEMS = 4;
	const int REINITIALIZE_BUFFER = 0;
	const int BIG_Q_SIZE = 10000;
	const char LETTER_Z = 'Z';
	const char LETTER_A = 'A';

  Queue sTheQueue;
  Queue sTheSecondQueue;
  int valOne = 1;
  int valTwo = 2;
  int intBuffer;
  int intSecondBuffer;
  int maxInt = INT_MAX;
  char charBuffer;
  char maxChar = CHAR_MAX;
  double doubleBuffer;
  double maxDouble = DBL_MAX;
  float floatBuffer;
  float maxFloat = FLT_MAX;
  short shortBuffer;
  short maxShort = SHRT_MAX;
	long long longBuffer;
	long long maxLongLong = LLONG_MAX;
	bool bTrue = true;
	char letter;
	char storedLetter;

	puts ("Program Start\n");
	puts ("SUCCESS TESTS:\n");

	//Checking if the error messages have been loaded
	queueLoadErrorMessages ();
	success ("Loaded Queue Error Messages");
	pqueueLoadErrorMessages ();
	success ("Loaded Priority Queue Error Messages");
	lstLoadErrorMessages ();
	success ("Loaded List Error Messages");

	//Testing Errors
	//Testing queueCreate for error no queue created
	//queueCreate (NULL);
	//Testing queueTerminate for error invalid queue
	//queueTerminate (NULL);
	//Testing queueSize for error invalid queue
	//queueSize (NULL);
	//Testing queueIsEmpty for error invalid queue
	//queueIsEmpty (NULL);
	//Testing queueEnqueue for error invalid queue
	//queueEnqueue (NULL, &valOne, sizeof (int));
	//Testing queueEnqueue for error null pointer
	//queueEnqueue (&sTheQueue, NULL, sizeof (int));
	//Testing queuePeek for error null pointer
	//queuePeek (&sTheQueue, NULL, sizeof (int));
	//Testing queuePeek for error invalid queue
	//queuePeek (NULL, &intBuffer, sizeof (int));
	//Testing queueDequeue for error invalid queue
	//queueDequeue (NULL, &valOne, sizeof (int));
	//Testing pqueueDequeue for error null pointer
	//queueDequeue (&sTheQueue, NULL, sizeof (int));

	//Creating a queue
	queueCreate (&sTheQueue);
	success ("Queue Created");

	//Checking queueIsEmpty
	assert (queueIsEmpty (&sTheQueue), "Queue is empty",
			"Queue is not empty");

	//Checking queueSize
	assert (queueSize (&sTheQueue) == SIZE_ZERO,
		      "Queue size is 0", "Queue size is NOT 0");

	//Checking queueEnqueue, queueDequeue, queuePeek
	queueEnqueue (&sTheQueue, &valOne, sizeof (int));
	assert (queueSize (&sTheQueue) == SIZE_ONE,
		      "Queue size is 1", "Queue size is NOT 1");
	assert (!queueIsEmpty (&sTheQueue), "Queue is not empty",
			    "Queue is empty");
	queuePeek (&sTheQueue, &intBuffer, sizeof (int));
	assert (intBuffer == valOne, "The peeked data is correct.",
			    "The peeked data is incorrect.");
	intBuffer = REINITIALIZE_BUFFER;
	queueEnqueue (&sTheQueue, &valTwo, sizeof (int));
	assert (queueSize (&sTheQueue) == SIZE_TWO,
		      "Queue size is 2", "Queue size is NOT 2");
	queuePeek (&sTheQueue, &intBuffer, sizeof (int));
	assert (intBuffer == valOne, "The peeked data is correct.",
			    "The peeked data is incorrect.");
	queueDequeue (&sTheQueue, &intBuffer, sizeof (int));
    assert (intBuffer == valOne, "The peeked data is correct.",
			    "The peeked data is incorrect");
    assert (queueSize (&sTheQueue) == SIZE_ONE,
		      "Queue size is 1", "Queue size is NOT 1");
	queuePeek (&sTheQueue, &intBuffer, sizeof (int));
	assert (intBuffer == valTwo, "The peeked data is correct.",
			    "The peeked data is incorrect.");
	intBuffer = REINITIALIZE_BUFFER;

	//Checking queueTerminate
	queueTerminate (&sTheQueue);
	success ("Queue Terminated");

	//Checking queueEnqueue using different data types
	queueCreate (&sTheQueue);
	success ("Queue Created");

	assert (queueIsEmpty (&sTheQueue), "Queue is empty",
			    "Queue is not empty");

	maxInt = 0;
	queueEnqueue (&sTheQueue, &maxInt, sizeof (int));
	queuePeek (&sTheQueue, &intBuffer, sizeof (int));
	assert (intBuffer == maxInt, "Max int correct", "Max int incorrect");
	assert (queueSize (&sTheQueue) == SIZE_ONE,
		      "Queue size is 1", "Queue size is NOT 1");
	intBuffer = REINITIALIZE_BUFFER;
	queueDequeue (&sTheQueue, &intBuffer, sizeof (int));
	assert (intBuffer == maxInt, "The peeked data is correct.",
			    "The peeked data is incorrect");
	assert (queueSize (&sTheQueue) == SIZE_ZERO,
		      "Queue size is 0", "Queue size is NOT 0");

	queueEnqueue (&sTheQueue, &maxChar, sizeof (char));
	queuePeek (&sTheQueue, &charBuffer, sizeof (char));
	assert (CHAR_MAX == maxChar, "Max char correct", "Max char incorrect");
	charBuffer = REINITIALIZE_BUFFER;
	queueDequeue (&sTheQueue, &charBuffer, sizeof (char));
	assert (charBuffer == maxChar, "The peeked character is correct.",
			    "The peeked character is incorrect");
	assert (queueSize (&sTheQueue) == SIZE_ZERO,
		      "Queue size is 0", "Queue size is NOT 0");

	queueEnqueue (&sTheQueue, &maxDouble, sizeof (double));
	queuePeek (&sTheQueue, &doubleBuffer, sizeof (double));
	assert (DBL_MAX == maxDouble, "Max double correct",
			    "Max double incorrect");

	queueEnqueue (&sTheQueue, &maxFloat, sizeof (float));
	queuePeek (&sTheQueue, &floatBuffer, sizeof (float));
	assert (FLT_MAX == maxFloat, "Max float correct", "Max float incorrect");

	queueEnqueue (&sTheQueue, &bTrue, sizeof (bool));
	queuePeek (&sTheQueue, &bTrue, sizeof (bool));
	assert (true == bTrue, "Max TRUE correct", "Max TRUE incorrect");

	queueEnqueue (&sTheQueue, &maxShort, sizeof (short));
	queuePeek (&sTheQueue, &shortBuffer, sizeof (short));
	assert (SHRT_MAX == maxShort, "Max short correct",
			    "Max short incorrect");

	queueEnqueue (&sTheQueue, &maxLongLong, sizeof (long long));
	queuePeek (&sTheQueue, &longBuffer, sizeof (long long));
	assert (LLONG_MAX == maxLongLong, "Max long long correct",
			   "Max long long incorrect");

	queueTerminate (&sTheQueue);
	success ("Queue Terminated");

  //Creating 2 Queues
	queueCreate (&sTheQueue);
	success ("First Queue Created");
	queueCreate (&sTheSecondQueue);
	success ("Second Queue Created");

	assert (queueIsEmpty (&sTheQueue), "First Queue is empty",
				  "First Queue is not empty");
	assert (queueIsEmpty (&sTheSecondQueue),
					"Second Queue is empty", "Second Queue is not empty");

	assert (queueSize (&sTheQueue) == SIZE_ZERO,
		      "First Queue size is 0", "First Queue size is NOT 0");
	assert (queueSize (&sTheSecondQueue) == SIZE_ZERO,
		      "Second Queue size is 0", "Second Queue size is NOT 0");
	makeBigQueue (&sTheQueue, BIG_Q_SIZE);
	makeBigQueue (&sTheSecondQueue, BIG_Q_SIZE);

	assert (queueSize (&sTheQueue) == BIG_Q_SIZE,
		      "First Queue size is 10000", "First Queue size is NOT 10000");
	assert (queueSize (&sTheSecondQueue) == BIG_Q_SIZE,
		      "Second Queue size is 10000", "Second Queue size is NOT 10000");

	while (!queueIsEmpty (&sTheQueue))
	{
		queueDequeue (&sTheQueue, &intBuffer, sizeof (int));
		queueDequeue (&sTheSecondQueue, &intSecondBuffer, sizeof (int));
	}
	assert (intBuffer == intSecondBuffer, "Big Q buffers match",
			    "Big Q buffers do not match");

	queueTerminate (&sTheQueue);
	success ("First Queue Terminated");
	queueTerminate (&sTheSecondQueue);
	success ("Second Queue Terminated");


	//Enqueue & Dequeue the alphabets
	queueCreate (&sTheQueue);
	success ("Queue Created");

	for (letter = LETTER_A ; letter <= LETTER_Z; ++letter)
	{
		queueEnqueue (&sTheQueue, &maxChar, sizeof (char));
		queuePeek (&sTheQueue, &storedLetter, sizeof (char));

		if (letter != storedLetter)
		{
			assert (letter != storedLetter, "Valid letter data",
				      "Invalid letter data");
		}
	}

	for (letter = LETTER_Z; letter >= LETTER_A; --letter)
	{
		queueDequeue (&sTheQueue, &storedLetter, sizeof (char));
		if (letter != storedLetter)
		{
			assert (letter != storedLetter, "Valid letter data",
				      "Invalid letter data");
		}
	}

	assert (queueIsEmpty (&sTheQueue), "First Queue is empty",
			    "First Queue is not empty");
	assert (queueIsEmpty (&sTheSecondQueue),
					"Second Queue is empty",
			    "Second Queue is not empty");

	assert (queueSize (&sTheQueue) == SIZE_ZERO,
		      "First Queue size is 0",
					"First Queue size is NOT 0");
	assert (queueSize (&sTheSecondQueue) == SIZE_ZERO,
		      "Second Queue size is 0",
					"Second Queue size is NOT 0");

	queueTerminate (&sTheSecondQueue);
	success ("Queue Terminated");

	queueCreate (&sTheQueue);
	success ("Queue Created");

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		queueEnqueue (&sTheQueue, &i, sizeof (int));
	}

	assert (MAX_ITEMS == queueSize (&sTheQueue), "queueSize is correct",
			"queueSize is incorrect");

	queueTerminate (&sTheSecondQueue);
	success ("Queue Terminated, Horray :-)");


	puts ("\nProgram End");

	return 0;
}
