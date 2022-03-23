/**************************************************************************
 File name:  stktester.c
 Author:     Ashley Ung
 Date:		   9.9.21
 Class:	     CS300
 Assignment: Static Generic Stack
 Purpose:    Test driver for a static stack of generic elements
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/stk.h"

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

 Description: if the expression is true, assert success; otherwise, assert
              failure

 Parameters:	szStr - the message to print

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
 Function: 	 	main

 Description: test all the functionality of the stack

 Parameters:	none

 Returned:	 	Exit Status
**************************************************************************/

int main ()
{
	const char PUSH_CHAR = 'C';

	Stack sTheStack;
	char data;

	puts ("Program Start\n");

	puts ("SUCCESS TESTS:");

	stkLoadErrorMessages ();
	success ("Loaded Error Messages");

	stkCreate (&sTheStack);
	success ("Stack Created");

	assert (stkSize (&sTheStack) == 0, "Stack size is 0", 
			    "Stack size is NOT 0");

	stkTerminate (&sTheStack);
	success ("Stack Terminated");

	//Test the stkCreate is initialized
	stkCreate (&sTheStack);
	success ("Creating another stack.");

	assert (stkIsEmpty(&sTheStack), "Stack is empty", "Stack is not empty");

	stkPush (&sTheStack, PUSH_CHAR);
	assert (stkSize (&sTheStack) == 1, "Stack size is 1", 
			    "Stack size is Not 1");

	stkPop (&sTheStack, &data);
	assert (data == PUSH_CHAR, "Pop data matches push data.",
				  "Pop data does not match push data.");

	puts ("\nProgram End");

	//Push into a full stack
	for (int i = 0; i < (STK_MAX_ELEMENTS); i++) {
		stkPush (&sTheStack, PUSH_CHAR);
	}
	assert (stkIsFull (&sTheStack), "The stack is full.",
			    "The stack is not full.");

	stkPeek (&sTheStack, &data);
	assert (data == PUSH_CHAR, "Peek returned the correct value.",
			    "Peek did not return the correct value.");

	return EXIT_SUCCESS;
}
