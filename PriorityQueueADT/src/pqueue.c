/**************************************************************************
 File name:  pqueue.c
 Author:     Ashley Ung
 Date:	     10.11.21
 Class:		   CS300
 Assignment: Priority Queue
 Purpose:    Implementation for a priority queue backed by a list ADT.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/pqueue.h"
#include "../../ListADT/include/list.h"

char gszPQErrors[NUMBER_OF_PQ_ERRORS][MAX_ERROR_PQ_CHARS];

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
			    gszPQErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	pqueueLoadErrorMessages

 Description: Loads the error message strings for the error handler to
 	 	 	        use no error conditions. LOAD_PQ_ERRORS is a macro
 	 	 	        defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/

void pqueueLoadErrorMessages ()
{
	LOAD_PQ_ERRORS
	lstLoadErrorMessages ();
}

/**************************************************************************
 Function: 	 	pqueueCreate

 Description: If the priority queue can be created, then the priority queue
 	 	 	 	 	 	 	exists and is empty; otherwise, if psQueue is NULL, then an
 	 	 	 	 	 	 	error message is displayed.

 Parameters:  psQueue - pointer to a priority queue

 Returned:	 	None
 *************************************************************************/

void pqueueCreate (PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("pqueueCreate", ERROR_NO_PQ_CREATE);
	}
	lstCreate (&psQueue->sTheList);
}

/**************************************************************************
 Function: 	 	pqueueSize

 Description: Obtains the number of elements in the priority queue.

 Parameters:  psQueue - pointer to a priority queue

 Returned:    The number of elements in the priority queue.
 *************************************************************************/

int pqueueSize (const PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("pqueueSize", ERROR_INVALID_PQ);
	}

	return lstSize (&psQueue->sTheList);
}

/**************************************************************************
 Function: 	 	pqueueIsEmpty

 Description: Checks if the priority queue is empty.

 Parameters:  psQueue - pointer to a priority queue

 Returned:    Returns true if the priority queue is empty, else, false.
 *************************************************************************/

bool pqueueIsEmpty (const PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("pqueueIsEmpty", ERROR_INVALID_PQ);
	}

	return lstIsEmpty (&psQueue->sTheList);
}

/**************************************************************************
 Function: 	 	pqueueEnqueue

 Description: Inserts the element into the priority queue based on the
 	 	 	 	 	 	 	priority of the element.

 Parameters:  psQueue  - pointer to a priority queue
 	 	 	 	 	 	 	pBuffer   - the data passed in
 	 	 	 	 	 	 	size     - the size of the data in bytes
 	 	 	 	 	 	 	priority - the priority of the data

 Returned:	 	None
 *************************************************************************/

void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority)
{
	const int SIZE_ONE = 1;

	PriorityQueueElement sNewNode;
	PriorityQueueElement sBuffer;

	if (NULL == psQueue)
	{
		processError ("pqueueEnqueue", ERROR_INVALID_PQ);
	}

	if (NULL == pBuffer)
	{
		processError ("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}

	sNewNode.pData = (void*) malloc (size);
	memcpy (sNewNode.pData, pBuffer, size);
	sNewNode.priority = priority;

	if (lstIsEmpty (&psQueue->sTheList))
	{
		lstInsertAfter (&psQueue->sTheList, &sNewNode,
				            sizeof (PriorityQueueElement));
	}
	else if (SIZE_ONE == lstSize (&psQueue->sTheList))
	{
		lstFirst (&psQueue->sTheList);
		lstPeek (&psQueue->sTheList, &sBuffer, sizeof (PriorityQueueElement));
		if (sNewNode.priority >= sBuffer.priority)
		{
			lstInsertAfter ((&psQueue->sTheList), &sNewNode,
					             sizeof (PriorityQueueElement));
		}
		else {
			lstInsertBefore (&psQueue->sTheList, &sNewNode,
				               sizeof (PriorityQueueElement));
		}
	}
	else
	{
		lstFirst (&psQueue->sTheList);
		lstPeek (&psQueue->sTheList, &sBuffer, sizeof (PriorityQueueElement));
		while (sNewNode.priority >= sBuffer.priority &&
				   lstHasNext (&psQueue->sTheList))
		{
			lstNext (&psQueue->sTheList);
			lstPeek (&psQueue->sTheList, &sBuffer, sizeof (PriorityQueueElement));
		}
		if (!lstHasNext (&psQueue->sTheList))
		{
			if (sNewNode.priority >= sBuffer.priority)
			{
				lstInsertAfter ((&psQueue->sTheList), &sNewNode,
						             sizeof (PriorityQueueElement));
			}
			else {
				lstInsertBefore (&psQueue->sTheList, &sNewNode,
					               sizeof (PriorityQueueElement));
			}
		}
		else
		{
			lstInsertBefore (&psQueue->sTheList, &sNewNode,
				               sizeof (PriorityQueueElement));
		}
	}
}

/**************************************************************************
 Function: 	 		pqueueDequeue

 Description:   Removes the element from the front of a non-empty queue.

 Parameters:    psQueue  - pointer to a priority queue
 	 	 	 					pBuffer  - the data passed in
 	 	 	 					size     - the size of the data in bytes
 	 	 	 					priority - the priority of the data

 Returned:			The value of the element that was removed from the priority
 	 	 	 	 	 	 		queue.
 *************************************************************************/

void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
										 int size, int *pPriority)
{
	PriorityQueueElement sBuffer;

	if (NULL == psQueue)
	{
		processError ("pqueueDequeue", ERROR_INVALID_PQ);
	}

	if (NULL == pBuffer)
	{
		processError ("pqueueDequeue", ERROR_NULL_PQ_PTR);
	}

	if (pqueueIsEmpty (psQueue))
	{
		processError ("pqueueDequeue", ERROR_EMPTY_PQ);
	}

	lstFirst (&psQueue->sTheList);
	lstDeleteCurrent (&psQueue->sTheList, &sBuffer,
			  	  	  		sizeof (PriorityQueueElement));

	memcpy (pBuffer, sBuffer.pData, size);
	*pPriority = sBuffer.priority;
	free (sBuffer.pData);
	sBuffer.pData = NULL;

	return pBuffer;
}

/**************************************************************************
 Function: 	 	pqueueTerminate

 Description: If the priority queue can be terminated, then the priority
 	 	 	 	 	 	 	queue no longer exists and is empty; otherwise, the priority
 	 	 	 	 	 	 	queue does not terminate so the entire program terminates.

 Parameters:  psQueue  - pointer to a priority queue

 Returned:	 	None
 *************************************************************************/

void pqueueTerminate (PriorityQueuePtr psQueue)
{
	PriorityQueueElement sBuffer;

	if (NULL == psQueue)
	{
		processError ("pQueueTerminate", ERROR_NO_PQ_TERMINATE);
	}

	if (!pqueueIsEmpty (psQueue))
	{
		lstFirst (&psQueue->sTheList);
	}

	while (!(lstIsEmpty (&psQueue->sTheList)))
	{
		lstDeleteCurrent (&psQueue->sTheList, &sBuffer,
				              sizeof (PriorityQueueElement));
		free (sBuffer.pData);
		sBuffer.pData = NULL;
	}
	lstTerminate (&psQueue->sTheList);
}

/**************************************************************************
 Function: 	 	pqueuePeek

 Description: Obtains the priority and value of the first element.

 Parameters:  psQueue  - pointer to a priority queue
 	 	 	 	 	 	 	pBuffer   - the data passed in
 	 	 	 	 	 	 	size     - the size of the data in bytes
 	 	 	 	 	 	 	priority - the priority of the data

 Returned:	  Returns the priority and value of the first element.
 *************************************************************************/

void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
								  int *priority)
{
	PriorityQueueElement sBuffer;

	if (NULL == psQueue)
	{
		processError ("pqueuePeek", ERROR_INVALID_PQ);
	}

	if (NULL == pBuffer)
	{
		processError ("pqueuePeek", ERROR_NULL_PQ_PTR);
	}

	if (pqueueIsEmpty (psQueue))
	{
		processError ("pqueuePeek", ERROR_EMPTY_PQ);
	}

	lstFirst (&psQueue->sTheList);
	lstPeek (&psQueue->sTheList, &sBuffer, sizeof (PriorityQueueElement));
	memcpy (pBuffer, sBuffer.pData, size);
	*priority = sBuffer.priority;

	return pBuffer;
}

/**************************************************************************
 Function: 	 	pqueueChangePriority

 Description: Accepts an integer (positive or negative) and adds that
 	 	 	 	 	 	  integer to the priority of every item in the queue.

 Parameters:  psQueue  - pointer to a priority queue
 	 	 	 	 	 	 	change   - the value to increment by

 Returned:	 	None
 *************************************************************************/

void pqueueChangePriority (PriorityQueuePtr psQueue,
													 int change)
{
	PriorityQueueElement sTemp;

	if (NULL == psQueue)
	{
		processError ("pqueueChangePriority", ERROR_INVALID_PQ);
	}

	lstFirst (&psQueue->sTheList);
	if (!(lstIsEmpty (&psQueue->sTheList)))
	{
		for (int i = 0; i < lstSize (&psQueue->sTheList); i++)
		{
			lstPeek (&psQueue->sTheList, &sTemp, sizeof (PriorityQueueElement));
			sTemp.priority += change;
			lstUpdateCurrent (&psQueue->sTheList, &sTemp,
												sizeof (PriorityQueueElement));
			lstNext (&psQueue->sTheList);
		}
	}
}
