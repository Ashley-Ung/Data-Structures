/**************************************************************************
 File name:  stk.c
 Author:     Ashley Ung
 Date:	     9.9.21
 Class:		   CS300
 Assignment: Static Generic Stack
 Purpose:    Implementation for a static stack of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/stk.h"

char gszErrors[STK_NUMBER_OF_ERRORS][STK_MAX_ERROR_CHARS];

/**************************************************************************
 Function: 	 	processError (DO NOT EDIT)

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
              errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/

static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	stkLoadErrorMessages (DO NOT EDIT)

 Description: Initializes the string of error messages. LOAD_ERRORS is a
              macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/

void stkLoadErrorMessages ()
{
	LOAD_ERRORS
}

/**************************************************************************
 Function: 	 	stkCreate

 Description: Initializes the top of the stack to empty. The stack is empty
              at this point.

 Parameters:	psStack - pointer to a stack

 Returned:	 	None
 *************************************************************************/

void stkCreate (StackPtr psStack)
{
	const int INDEX_OFFSET = -1;

	if (NULL == psStack)
	{
		processError ("stkCreate", STK_NO_CREATE_ERROR);
	}
	psStack->top = INDEX_OFFSET;

	for (int i = 0; i < STK_MAX_ELEMENTS; i++)
	{
		psStack->pData[i] = '\0';
	}
}

/**************************************************************************
 Function: 	 	stkTerminate

 Description: Sets the top of the stack to empty.

 Parameters:	psStack - pointer to a stack

 Returned:	 	None
 *************************************************************************/

void stkTerminate (StackPtr psStack)
{
	if (NULL == psStack)
	{
		processError ("stkTerminate", STK_NO_TERMINATE_ERROR);
	}

	psStack->pData[psStack->top] = '\0';
}

/**************************************************************************
 Function: 	 	stkIsFull

 Description: Checks if the stack is full

 Parameters:	psStack - pointer to a stack

 Returned:	 	Returns true if stack is full otherwise false
 *************************************************************************/

bool stkIsFull (const StackPtr psStack)
{
	const int LAST_INDEX = 1;

	if (NULL == psStack)
	{
		processError ("stkISFull", STK_FULL_ERROR);
	}

	return psStack->top == STK_MAX_ELEMENTS - LAST_INDEX;
}

/**************************************************************************
 Function: 	 	stkIsEmpty

 Description: Checks if the stack is empty

 Parameters:	psStack - pointer to a stack

 Returned:	 	Returns true if stack is empty otherwise false
 *************************************************************************/

bool stkIsEmpty (const StackPtr psStack)
{
	const int INDEX_OFFSET = -1;

	if (NULL == psStack)
	{
		processError ("stkIsEmpty", STK_EMPTY_ERROR);
	}

	return (psStack->top == INDEX_OFFSET);
}

/**************************************************************************
 Function: 	 	stkPush

 Description: Adds a new item on top of the stack if stack is not full.

 Parameters:	pStack     - pointer to stack struct
              data	     - the character to push

 Returned:	 	None
 *************************************************************************/

void stkPush (StackPtr psStack, char data)
{
	const int INCREMENT = 1;

	if (NULL == psStack)
	{
		processError ("stkPush", STK_NO_MEMORY_ERROR);
	}

	if (stkIsFull(psStack))
	{
		processError ("stkPush", STK_FULL_ERROR);
	}

	psStack->pData[psStack->top] = data;
	psStack->top = psStack->top + INCREMENT;
}

/**************************************************************************
 Function: 	 	stkPop

 Description: Removes top item of stack

 Parameters:	psStack  - pointer to stack struct
 	 	 	 	 	 	 	pBuffer  - character pointer to use to store the top of the
 	 	 	 	 	 	 						 stack

 Returned:	 	Pointer to the buffer of the popped value
 **************************************************************************/

char* stkPop (StackPtr psStack, char *pBuffer)
{
	const int DECREMENT_VALUE = 1;

	if (NULL == psStack)
	{
		processError ("stkPop", STK_NO_MEMORY_ERROR);
	}

	if (NULL == pBuffer)
	{
		processError ("stkPop", STK_NO_BUFFER_ERROR);
	}

	if (stkIsEmpty (psStack))
	{
		processError ("stkPop", STK_EMPTY_ERROR);
	}
	*pBuffer = psStack->pData[psStack->top - DECREMENT_VALUE];
	psStack->top--;

	return pBuffer;
}

/**************************************************************************
 Function: 	  stkPeek

 Description: Looks at the value at the top of the stack

 Parameters:  psStack  - characterStaticStack
              pBuffer  - character pointer to use to store the top of the
                         stack

 Returned:	  Pointer to the buffer of the peek value
 *************************************************************************/

char* stkPeek (StackPtr psStack, char *pBuffer)
{
	const int DECREMENT_VALUE = 1;

	if (NULL == psStack)
	{
		processError ("stkPeek", STK_NO_MEMORY_ERROR);
	}

	if (NULL == pBuffer)
	{
		processError ("stkPeek", STK_NO_BUFFER_ERROR);
	}

	if (stkIsEmpty(psStack))
	{
		processError ("stkPeek", STK_EMPTY_ERROR);
	}

	*pBuffer = psStack->pData[psStack->top - DECREMENT_VALUE];

	return pBuffer;
}

/**************************************************************************
 Function: 	 	stkSize

 Description: Returns the number of elements on the stack

 Parameters:	psStack - a pointer to a stack

 Returned:	  Number of elements in the stack
 *************************************************************************/

int stkSize (const StackPtr psStack)
{
	const int INDEX_OFFSET = 1;
	return psStack->top + INDEX_OFFSET;
}

