/**************************************************************************
 File name:  queue.c
 Author:     Ashley Ung
 Date:	     10.24.21
 Class:		   CS300
 Assignment: Queue
 Purpose:    Implementation for a priority queue backed by a priority queue
             ADT.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/queue.h"
#include "../../PriorityQueueADT/include/pqueue.h"

char gszQErrors[NUMBER_OF_Q_ERRORS][MAX_ERROR_Q_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
              errorCode 	    - identifies the list error

 Returned:	 	None
 *************************************************************************/

static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
			    gszQErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	queueLoadErrorMessages

 Description: Loads the error message strings for the error handler to
 	 	 	        use no error conditions. LOAD_Q_ERRORS is a macro defined
 	 	 	        in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/

void queueLoadErrorMessages ()
{
	LOAD_Q_ERRORS
	pqueueLoadErrorMessages ();
}

/**************************************************************************
 Function: 	 	queueCreate

 Description: If the queue can be created, then the queue exists and is
 	 	 	    		empty; otherwise, if psQueue is NULL, then an error message
 	 	 	    		is displayed.

 Parameters:  Queue - pointer to a priority queue

 Returned:	 	None
 *************************************************************************/

void queueCreate (QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueCreate", ERROR_NO_Q_CREATE);
	}
	pqueueCreate (&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueTerminate

 Description: If the queue can be terminated, then the queue no longer
   	 	 	 			exists and is empty; otherwise, the queue does not terminate
   	 	 	 			so the entire program terminates.

 Parameters:  psQueue  - pointer to a priority queue

 Returned:	 	None
 *************************************************************************/

void queueTerminate (QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueTerminate", ERROR_NO_Q_TERMINATE);
	}

	pqueueTerminate (&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	  queueSize

 Description: Obtains the number of elements in the queue.

 Parameters:  psQueue - pointer to a queue

 Returned:    The number of elements in the queue.
 *************************************************************************/

int queueSize (const QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueSize", ERROR_INVALID_Q);
	}

	return pqueueSize (&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	  queueIsEmpty

 Description: Checks if the queue is empty.

 Parameters:  psQueue - pointer to a queue

 Returned:    Returns true if the queue is empty, else, false.
 *************************************************************************/

bool queueIsEmpty (const QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueIsEmpty", ERROR_INVALID_Q);
	}

	return pqueueIsEmpty (&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueEnqueue

 Description: Inserts an element into the FIFO queue.

 Parameters:  psQueue  - pointer to a queue
 	 	 	 	 	 	 	pBuffer   - the data passed in
 	 	 	 	 	 	 	size     - the size of the data in bytes

 Returned:	 	None
 *************************************************************************/

void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size)
{
	const int ZERO_PRIORITY = 0;

	if (NULL == psQueue)
	{
		processError ("queueEnqueue", ERROR_INVALID_Q);
	}

	if (NULL == pBuffer)
	{
		processError ("queueEnqueue", ERROR_NULL_Q_PTR);
	}
	pqueueEnqueue (&psQueue->sTheQueue, pBuffer, size, ZERO_PRIORITY);
}

/**************************************************************************
 Function: 	 	queueDequeue

 Description: Removes the element from the front of a non-empty queue

 Parameters:  psQueue  - pointer to a queue
 	 	 	 	 	 	 	pBuffer   - the data passed in
 	 	 	 	 	 	 	size     - the size of the data in bytes

 Returned:	 	None
 *************************************************************************/

void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size)
{
	int buffer;

	if (NULL == psQueue)
	{
		processError ("queueDequeue", ERROR_INVALID_Q);
	}

	if (NULL == pBuffer)
	{
		processError ("queueDequeue", ERROR_NULL_Q_PTR);
	}

	if (queueIsEmpty (psQueue))
	{
		processError ("queueDequeue", ERROR_EMPTY_Q);
	}

	pqueueDequeue (&psQueue->sTheQueue, pBuffer, size, &buffer);
	return pBuffer;
}

/**************************************************************************
 Function: 	  queuePeek

 Description: Peeks the queue's first element.

 Parameters:  psQueue  - pointer to a queue
 	 	 	  			pBuffer  - the data passed in
 	 	 	  			size     - the size of the data in bytes

 Returned:	  Returns the value of the first element.
 *************************************************************************/

void *queuePeek (QueuePtr psQueue, void *pBuffer, int size)
{
	int buffer;

	if (NULL == psQueue)
	{
		processError ("queuePeek", ERROR_INVALID_Q);
	}

	if (NULL == pBuffer)
	{
		processError ("queuePeek", ERROR_NULL_Q_PTR);
	}

	if (queueIsEmpty (psQueue))
	{
		processError ("queuePeek", ERROR_EMPTY_Q);
	}

	pqueuePeek (&psQueue->sTheQueue, pBuffer, size, &buffer);

	return pBuffer;
}
