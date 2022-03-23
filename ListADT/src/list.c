/**************************************************************************
 File name:  list.c
 Author:     Ashley Ung
 Date:	     9.18.21
 Class:		   CS300
 Assignment: Dynamic List
 Purpose:    Implementation for a list of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/list.h"

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

/**************************************************************************
 Function: 	  processError

 Description: Process the error code passed to this routine

 Parameters:  pszFunctionName - function causing the error
              errorCode 	  - identifies the list error

 Returned:	  None
 *************************************************************************/

static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
			    gszListErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	lstLoadErrorMessages

 Description: Loads the error message strings for the error handler to
 	 	 	        use no error conditions. LOAD_LIST_ERRORS is a macro
 	 	 	        defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/

void lstLoadErrorMessages ()
{
	LOAD_LIST_ERRORS
}

/**************************************************************************
 Function: 	 	lstCreate

 Description: If the list can be created, then the list exists and is
 	 	 	 	      empty; otherwise, if psList is NULL, then an error message
 	 	 	 	      is displayed.

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/

void lstCreate (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstCreate", ERROR_NO_LIST_CREATE);
	}
	psList->psFirst = NULL;
	psList->psLast = NULL;
	psList->psCurrent = NULL;
	psList->numElements = 0;
}

/**************************************************************************
 Function: 	 		lstInsertAfter

 Description:   If the list is not empty, the new element is inserted as
 	 	 	 					the successor of the current element pointed to by
 	 	 	 					psCurrent and the inserted element is made into the
 	 	        		current element pointed to by psCurrent; otherwise, the
 	 	        		element is inserted and made into the current.

 Parameters:		psList  - pointer to a list
 	 	 						pBuffer - data passed in
 	 	 	 					size    - size of the data in bytes

 Returned:		 	None
 *************************************************************************/

void lstInsertAfter (ListPtr psList, const void *pBuffer, int size)
{
	ListElementPtr psNewNode;

	if (NULL == psList)
	{
		processError ("lstInsertAfter", ERROR_INVALID_LIST);
	}

	if (NULL == pBuffer)
	{
		processError ("lstInsertAfter", ERROR_NULL_PTR);
	}

	if (!lstIsEmpty (psList) && NULL == psList->psCurrent)
	{
		processError ("lstInsertAfter", ERROR_NO_CURRENT);
	}

	psNewNode = (ListElementPtr) malloc (sizeof (ListElement));
	psNewNode->pData = (void*) malloc(size);
	psNewNode->psNext = NULL;
	memcpy (psNewNode->pData, pBuffer, size);

	if (lstIsEmpty (psList))
	{
		psList->psFirst = psNewNode;
		psList->psLast = psNewNode;
		psList->psCurrent = psNewNode;
	}
	else if (psList->psCurrent == psList->psLast)
	{
		psList->psLast->psNext = psNewNode;
		psList->psLast = psNewNode;
		psList->psCurrent = psNewNode;
	}
	else
	{
		psNewNode->psNext = psList->psCurrent->psNext;
		psList->psCurrent->psNext = psNewNode;
		psList->psCurrent = psNewNode;
	}
	psList->numElements++;
}

/**************************************************************************
 Function: 	 	lstTerminate

 Description: If the list can be terminated, then the list no longer
 	 	 	 		    exists and is empty; otherwise, ERROR_NO_LIST_TERMINATE

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/

void lstTerminate (ListPtr psList)
{
	ListElementPtr psTemp;
	ListElementPtr psTempNext;

	psTemp = psList->psFirst;

	if (NULL == psList)
	{
		processError ("lstTerminate", ERROR_NO_LIST_TERMINATE);
	}

	while (psTemp != NULL)
	{
		psTempNext = psTemp->psNext;
		free (psTemp->pData);
		free (psTemp);
		psTemp = psTempNext;
	}

	psList->psFirst = NULL;
	psList->psCurrent = NULL;
	psList->psLast = NULL;
	psList->numElements = 0;
}

/**************************************************************************
 Function: 	 	lstSize

 Description: Obtains the number of elements in the list; otherwise,
 	 	 	    	  ERROR_INVALID_LIST.

 Parameters:	psList - pointer to a list

 Returned:	 	The number of elements in the list.
 *************************************************************************/

int lstSize (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstSize", ERROR_INVALID_LIST);
	}
	return psList->numElements;
}

/**************************************************************************
 Function: 	 	lstIsEmpty

 Description: Checks if the list is empty.

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if the list is empty; else, false.
 *************************************************************************/

bool lstIsEmpty (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstIsEmpty", ERROR_INVALID_LIST);
	}

	return lstSize (psList) == 0;
}

/**************************************************************************
 Function: 	 	lstFirst

 Description: If the list is not empty, psCurrent is changed to the first
 	 	 	        element.

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/

void lstFirst (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstFirst", ERROR_INVALID_LIST);
	}

	if (lstIsEmpty (psList))
	{
		processError ("lstFirst", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psFirst;
}

/**************************************************************************
 Function: 	 	lstPeek

 Description: Obtains the value of the current element pointed to by
 	 	 	       	psCurrent.

 Parameters:	psList  - pointer to a list
  	 	 	     	pBuffer  - data passed in
 	 	 	      	size    - size of the data in bytes

 Returned:	 	Returns the value of the current element pointed to by
 	 	 	      	psCurrent.
 *************************************************************************/

void *lstPeek (const ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstPeek", ERROR_INVALID_LIST);
	}

	if (NULL == pBuffer)
	{
		processError ("lstPeek", ERROR_NULL_PTR);
	}

	if (lstIsEmpty (psList))
	{
		processError ("lstPeek", ERROR_EMPTY_LIST);
	}

	if (NULL == psList->psCurrent)
	{
		processError ("lstPeek", ERROR_NO_CURRENT);
	}

	memcpy (pBuffer, psList->psCurrent->pData, size);
	return pBuffer;
}

/**************************************************************************
 Function: 	 	lstNext

 Description: If the list is not empty, psCurrent is changed to the
 	 	 	 	      successor of the current element pointed to by psCurrent

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/

void lstNext (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstNext", ERROR_INVALID_LIST);
	}

	if (lstIsEmpty (psList))
	{
		processError ("lstNext", ERROR_EMPTY_LIST);
	}

	if (NULL == psList->psCurrent)
	{
		processError ("lstNext", ERROR_NO_CURRENT);
	}

	psList->psCurrent = psList->psCurrent->psNext;
}

/**************************************************************************
 Function: 	 	lstHasCurrent

 Description: Checks if the list has a current node.

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if the current node pointed to by psCurrent
 	 	 	 	      is not NULL; otherwise, false is returned.
 *************************************************************************/

bool lstHasCurrent (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstHasCurrent", ERROR_INVALID_LIST);
	}

	return NULL != psList->psCurrent;
}

/**************************************************************************
 Function: 	 	lstHasNext

 Description:   Checks if the current node pointed to by psCurrent has a
 	 	 	 	successor.

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if the current node pointed to by psCurrent
 	 	 	 	has a successor; otherwise, false is returned.
 *************************************************************************/

bool lstHasNext (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstHasNext", ERROR_INVALID_LIST);
	}

	return NULL != psList->psCurrent->psNext;

}

/**************************************************************************
 Function: 	 	lstPeekNext

 Description: Copies the value of the current element pointed to by
 	 	 	 				psCurrent into pBuffer.

 Parameters:	psList  - pointer to a list
  	 	 	     	pBuffer  - data passed in
 	 	 	      	size    - size of the data in bytes

 Returned:    The data value of psCurrent's successor is returned.
 *************************************************************************/

void *lstPeekNext (const ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstPeekNext", ERROR_INVALID_LIST);
	}

	if (NULL == pBuffer)
	{
		processError ("lstPeekNext", ERROR_NULL_PTR);
	}

	if (lstIsEmpty (psList))
	{
		processError ("lstPeekNext", ERROR_EMPTY_LIST);
	}

	if (NULL == psList->psCurrent)
	{
		processError ("lstPeekNext", ERROR_NO_CURRENT);
	}

	if (!lstHasNext (psList))
	{
		processError ("lstPeekNext", ERROR_NO_NEXT);
	}

	memcpy (pBuffer, psList->psCurrent->psNext->pData, size);
	return pBuffer;
}

/**************************************************************************
 Function: 	 	lstLast

 Description: If the list is not empty, psCurrent is changed to psLast.

 Parameters:	psList  - pointer to a list

 Returned:	 	None
 *************************************************************************/

void lstLast (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstLast", ERROR_INVALID_LIST);
	}

	if (lstIsEmpty (psList))
	{
		processError ("lstLast", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psLast;
}

/**************************************************************************
 Function: 	 	lstDeleteCurrent

 Description: The current element is deleted and its successor and
 	 	 	 				predecessor. If the deleted element had a predecessor, then
 	 	 	 				it becomes the new current element; otherwise, the first
 	 	 	 				element is the current if it exists.

 Parameters:	psList  - pointer to a list
  	 	 	     	pBuffer  - data passed in
 	 	 	      	size    - size of the data in bytes

 Returned:		The value of the deleted element.
 *************************************************************************/

void *lstDeleteCurrent (ListPtr psList, void *pBuffer, int size)
{
	const int FIRST_NODE = 1;

	ListElementPtr psPrev;

	if (NULL == psList)
	{
		processError ("lstDeleteCurrent", ERROR_INVALID_LIST);
	}

	if (NULL == pBuffer)
	{
		processError ("lstDeleteCurrent", ERROR_NULL_PTR);
	}

	if (lstIsEmpty (psList))
	{
		processError ("lstDeleteCurrent", ERROR_EMPTY_LIST);
	}

	if (NULL == psList->psCurrent)
	{
		processError ("lstDeleteCurrent", ERROR_NO_CURRENT);
	}

	memcpy (pBuffer, psList->psCurrent->pData, size);

	if (FIRST_NODE == lstSize (psList))
	{
		free (psList->psCurrent->pData);
		free (psList->psCurrent);
		psList->psFirst = NULL;
		psList->psCurrent = NULL;
		psList->psLast = NULL;
	}
	else if (psList->psCurrent == psList->psFirst)
	{
		psPrev = psList->psFirst->psNext;
		free (psList->psFirst->pData);
		free (psList->psFirst);
		psList->psCurrent = psPrev;
		psList->psFirst = psPrev;
	}
	else
	{
		psPrev = psList->psFirst;
		while (psPrev->psNext != psList->psCurrent)
		{
			psPrev = psPrev->psNext;
		}
		psPrev->psNext = psList->psCurrent->psNext;
		free (psList->psCurrent->pData);
		free (psList->psCurrent);
		psList->psCurrent = psPrev;
	}

	psList->numElements--;
	return pBuffer;
}

/**************************************************************************
 Function: 	 	lstInsertBefore

 Description: If the list is not empty, the new element is inserted as
           	  as the predecessor of the current element and the inserted
           	  element is set to the current element; otherwise, the
           	  element is inserted and set to the current.

 Parameters:	psList  - pointer to a list
  	 	 	     	pBuffer  - data passed in
 	 	 	      	size    - size of the data in bytes

 Returned:	 	None
 *************************************************************************/

void lstInsertBefore (ListPtr psList, const void *pBuffer, int size)
{
	ListElementPtr psPrev, psNewNode;

	if (NULL == psList)
	{
		processError ("lstInsertBefore", ERROR_INVALID_LIST);
	}

	if (NULL == pBuffer)
	{
		processError ("lstInsertBefore", ERROR_NULL_PTR);
	}

	if (!lstIsEmpty (psList) && NULL == psList->psCurrent)
	{
		processError ("lstInsertBefore", ERROR_NO_CURRENT);
	}

	if (lstIsEmpty (psList))
	{
		lstInsertAfter (psList, pBuffer, size);
	}
	else if (psList->psFirst == psList->psCurrent)
	{
		psNewNode = (ListElementPtr) malloc (sizeof (ListElement));
		psNewNode->pData = (void*) malloc (size);
		psNewNode->psNext = NULL;
		memcpy (psNewNode->pData, pBuffer, size);
		psNewNode->psNext = psList->psFirst;
		psList->psCurrent = psNewNode;
		psList->psFirst = psNewNode;
		psList->numElements++;
	}
	else
	{
		psPrev = psList->psFirst;
		while (psPrev->psNext != psList->psCurrent)
		{
			psPrev = psPrev->psNext;
		}
		psList->psCurrent = psPrev;

		lstInsertAfter (psList, pBuffer, size);
	}
}

/**************************************************************************
 Function: 	 	lstUpdateCurrent

 Description: The value of pBuffer is copied into the current element.

 Parameters:	psList  - pointer to a list
  	 	 	     	pBuffer  - data passed in
 	 	 	      	size    - size of the data in bytes

 Returned:	 	None
 *************************************************************************/

void lstUpdateCurrent (ListPtr psList, const void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstUpdateCurrent", ERROR_INVALID_LIST);
	}

	if (NULL == pBuffer)
	{
		processError ("lstUpdateCurrent", ERROR_NULL_PTR);
	}

	if (lstIsEmpty (psList))
	{
		processError ("lstUpdateCurrent", ERROR_EMPTY_LIST);
	}

	if (NULL == psList->psCurrent)
	{
		processError ("lstUpdateCurrent", ERROR_NO_CURRENT);
	}

	free (psList->psCurrent->pData);
	psList->psCurrent->pData = (void*) malloc (size);
	memcpy (psList->psCurrent->pData, pBuffer, size);
}

/**************************************************************************
 Function: 	 	lstReverse

 Description: Reverses the List.

 Parameters:	psList  - pointer to a list

 Returned:	 	None
 *************************************************************************/

void lstReverse (ListPtr psList)
{
	ListElementPtr psPrev, psTemp;

	psPrev = NULL;
	psTemp = NULL;

	if (NULL == psList)
	{
		processError ("lstReverseCurrent", ERROR_INVALID_LIST);
	}

	if (lstIsEmpty (psList))
	{
		processError ("lstReverseNext", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psFirst;

	while (psList->psCurrent != NULL)
	{
		psTemp = psList->psCurrent->psNext;
		psList->psCurrent->psNext = psPrev;
		psPrev = psList->psCurrent;
		psList->psCurrent = psTemp;
	}
	psList->psLast = psList->psFirst;
	psList->psFirst = psPrev;
	psList->psCurrent = psList->psFirst;
}
