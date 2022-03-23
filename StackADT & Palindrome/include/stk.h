/**************************************************************************
 File name:  stk.h
 Author:     Computer Science, Pacific University
 Date:			 10.11.17 - modified on 9/7/21
 Class:			 CS300
 Assignment: Character Static Stack
 Purpose:    Interface for a static stack of generic elements
 *************************************************************************/

#ifndef STK_H_
#define STK_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//*************************************************************************
// Constants
//*************************************************************************
#define STK_MAX_ERROR_CHARS 64
#define STK_MAX_ELEMENTS 100
#define STK_EMPTY 0

enum {STK_NO_ERROR = 0,
	    STK_EMPTY_ERROR,         // there are no elements in the stack
			STK_FULL_ERROR,          // the stack is full
			STK_NO_CREATE_ERROR,     // psStack is NULL in stkCreate()
			STK_NO_TERMINATE_ERROR,  // psStack is NULL in stkTerminate()
			STK_NO_MEMORY_ERROR,     // psStack is NULL in other functions
			STK_NO_BUFFER_ERROR}; 	 // pBuffer is NULL in functions
			// If the error names change, change stmt below
#define STK_NUMBER_OF_ERRORS STK_NO_BUFFER_ERROR - STK_NO_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_ERRORS strcpy (gszErrors[STK_NO_ERROR], "No Error.");\
strcpy (gszErrors[STK_EMPTY_ERROR], "Error: Empty Stack.");\
strcpy (gszErrors[STK_FULL_ERROR], "Error: Full Stack.");\
strcpy (gszErrors[STK_NO_CREATE_ERROR], "Error: No Stack Create.");\
strcpy (gszErrors[STK_NO_TERMINATE_ERROR], "Error: No Stack Terminate.");\
strcpy (gszErrors[STK_NO_MEMORY_ERROR], "Error: No Stack Memory.");\
strcpy (gszErrors[STK_NO_BUFFER_ERROR], "Error: No Buffer.");


//*************************************************************************
// User-defined types
//*************************************************************************
typedef struct Stack *StackPtr;
typedef struct Stack
{
	char pData[STK_MAX_ELEMENTS];
	int top;
} Stack;

//*************************************************************************
// Function prototypes
//*************************************************************************
extern void stkLoadErrorMessages ();
extern void stkCreate (StackPtr psStack);
extern void stkTerminate (StackPtr psStack);
extern bool stkIsFull (const StackPtr psStack);
extern bool stkIsEmpty (const StackPtr psStack);
extern void stkPush (StackPtr psStack, char data);
extern char *stkPop (StackPtr psStack, char* data);
extern char *stkPeek (const StackPtr psStack, char *data);
extern int stkSize (const StackPtr psStack);

#endif /* STK_H_ */
