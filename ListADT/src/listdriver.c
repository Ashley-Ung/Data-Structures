/**************************************************************************
 File name:  listdriver.c
 Author:     Ashley Ung
 Date:	     9.18.21
 Class:		   CS300
 Assignment: Dynamic List
 Purpose:    Test driver for a list of generic elements
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#include "../include/list.h"

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

 Description: if the expression is true, assert success; otherwise,
              assert failure

 Parameters:	bExpression - the expression to evaluate
 	 	 	 				pTrue 		- the true boolean
 	 	 	 				pFalse 		- the false boolean

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
 Function: 	 	printList

 Description: A helper function that prints out the list for a list
 	 	 	 				containing integers.

 Parameters:	sTheList - the list of integers to be printed

 Returned:	 	none
 *************************************************************************/

static void printIntList (List sTheList)
{
	int i, theIntData;

	if (!lstIsEmpty (&sTheList))
	{
		printf ("The values in the list are: ");
		lstFirst (&sTheList);
		for (i = 0; i < lstSize (&sTheList); ++i)
		{
			lstPeek (&sTheList, &theIntData, sizeof (int));
			printf ("%d ", theIntData);

			lstNext (&sTheList);
		}
		printf ("\n");
	}
}

/**************************************************************************
 Function: 	 	lstAppend

 Description:   A function that appends psListTwo to the end of psListOne.

 Parameters:	psListOne - the list to append another list onto.
 	 	 	 	psListTwo - the list that needs to be appended.

 Returned:	 	none
 *************************************************************************/

//static void lstAppend (ListPtr psListOne, ListPtr psListTwo)
//{
//	if (NULL == psListOne || NULL == psListTwo || lstIsEmpty (psListTwo))
//	{
//		return 0;
//	}
//	lstLast (psListOne);
//	lstFirst(psListTwo);
//	ListElementPtr buffer;
//	while (!lstIsEmpty (psListTwo))
//	{
//		lstPeek (psListOne, &buffer, sizeof (ListElementPtr));
//		lstInsertAfter (psListOne, &buffer, sizeof (ListElementPtr));
//		lstDeleteCurrent (psListTwo, &buffer, sizeof (ListElementPtr));
//	}
//
//}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none

 Returned:	 	Exit Status
**************************************************************************/

int main ()
{
	const int MAX_ELEMENTS = 2000;
	const int SIZE_ZERO = 0;
	const int SIZE_ONE = 1;
	const int SIZE_TWO = 2;
	const int SIZE_THREE = 3;
	const int SIZE_FOUR = 4;

	List sTheList;
	//List sTheSecondList;
	char data ='A';
	char secondData = 'B';
	char thirdData = 'C';
	char fourthData = 'D';
	int value = 300;
	int counter = 0;
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int buffer = 0;
	int maxInt = INT_MAX;
	char maxChar = CHAR_MAX;
	char charBuffer;
	double maxDouble = DBL_MAX;
	float maxFloat = FLT_MAX;
	short maxShort = SHRT_MAX;
	long long maxLongLong = LLONG_MAX;
	bool bTrue = true;

	puts ("Program Start\n");

	puts ("SUCCESS TESTS:\n");

	lstLoadErrorMessages ();
	success ("Loaded Error Messages");

	//Checking lstPeek for no current node.
	//lstPeek (&sTheList, &data, sizeof (char));

	//Checking lstFirst for empty list error
	//lstFirst (&sTheList);

	//Testing errors for error Null pointer & error invalid list
	//lstCreate (NULL);
	//Checking lstPeek for error null pointer
	//lstPeek (&sTheList, NULL, sizeof (int));
	//Checking lstPeek for error invalid list
	//lstPeek (NULL, &value, sizeof (int));
	//Checking lstInsertAfter for error null pointer
	//lstInsertAfter (&sTheList, NULL, sizeof (int));
	//Checking lstInsertAfter for error invalid list
	//lstInsertAfter (NULL, &value, sizeof int));
	//Checking lstNext for error invalid list
	//lstNext (NULL);
	//Checking lstHasCurrent for error invalid list
	//lstHasCurrent (NULL);
	//Checking lstHasNext for error invalid list
	//lstHasNext (NULL);
	//Checking lstPeekNext for error invalid list
	//lstPeekNext (NULL, &value, sizeof (int));
	//Checking lstPeekNext for error null pointer
	//lstPeekNext (&sTheList, NULL, sizeof (int));
	//Checking lstLast for error invalid list
	//lstLast (NULL);
	//Checking lstDeleteCurrent for error invalid list
	//lstDeleteCurrent (NULL, &value, sizeof (int));
	//Checking lstDeleteCurrent for error NULL pointer
	//lstDeleteCurrent (&sTheList, NULL, sizeof (int));
	//Checking lstInsertBefore for error invalid list
	//lstInsertBefore (NULL, &value, sizeof (int));
	//Checking lstInsertBefore for error NULL pointer
	//lstInsertBefore (&sTheList, NULL, sizeof (int));
	//Checking lstUpdateCurrent for error invalid list
	//lstUpdateCurrent (NULL, &value, sizeof (int));
	//Checking lstUpdateCurrent for error no pointer
	//lstUpdateCurrent (&sTheList, NULL, sizeof (int));
	//Checking that the reverse function only proceeds when the list is
	//not empty.
	//lstReverse (&sTheList);
	//Checking lstReverse for error invalid list
	//lstReverse (NULL);

	//Testing psCurrent when it is NULL
	//lstCreate (&sTheList);
	//lstInsertAfter (&sTheList, &value, sizeof (int));
	//lstLast (&sTheList);
	//lstNext (&sTheList);
	//lstInsertBefore (&sTheList, &value, sizeof (int));
	//lstTerminate (&sTheList);

	lstCreate (&sTheList);
	success ("List Created");

	//Checking if the lstIsEmpty and lstHasCurrent
	assert (lstIsEmpty (&sTheList), "List is empty", "List is not empty");
	assert (!lstHasCurrent (&sTheList), "List does not have a current",
		     	"List has a current");

	//Checking lstInsertAfter for different data types
	lstInsertAfter (&sTheList, &maxInt, sizeof (int));
	lstInsertAfter (&sTheList, &maxChar, sizeof (char));
	lstInsertAfter (&sTheList, &maxDouble, sizeof (double));
	lstInsertAfter (&sTheList, &maxFloat, sizeof (float));
	lstInsertAfter (&sTheList, &bTrue, sizeof (bool));
	lstInsertAfter (&sTheList, &maxShort, sizeof (short));
	lstInsertAfter (&sTheList, &maxLongLong, sizeof (long long));

	lstFirst (&sTheList);
	maxInt = 0;
	lstPeek (&sTheList, &maxInt, sizeof (int));
	assert (INT_MAX == maxInt, "Max int correct", "Max int incorrect");
	lstNext (&sTheList);

	maxChar = 0;
	lstPeek (&sTheList, &maxChar, sizeof (char));
	assert (CHAR_MAX == maxChar, "Max char correct", "Max char incorrect");
	lstNext (&sTheList);

	maxDouble = 0.0;
	lstPeek (&sTheList, &maxDouble, sizeof (double));
	assert (DBL_MAX == maxDouble, "Max double correct",
		      "Max double incorrect");
	lstNext (&sTheList);

	maxFloat = 0.0;
	lstPeek (&sTheList, &maxFloat, sizeof (float));
	assert (FLT_MAX == maxFloat, "Max float correct",
		      "Max float incorrect");
	lstNext (&sTheList);

	bTrue = false;
	lstPeek (&sTheList, &bTrue, sizeof (bool));
	assert (true == bTrue, "Max TRUE correct", "Max TRUE incorrect");
	lstNext (&sTheList);

	maxShort = 0;
	lstPeek (&sTheList, &maxShort, sizeof (short));
	assert (SHRT_MAX == maxShort, "Max short correct",
		      "Max short incorrect");
	lstNext (&sTheList);

	maxLongLong = 0;
	lstPeek (&sTheList, &maxLongLong, sizeof (long long));
	assert (LLONG_MAX == maxLongLong, "Max long long correct",
		      "Max long long incorrect");
	lstNext (&sTheList);

	lstTerminate (&sTheList);
	success ("List Terminated");

	//Checking lstSize, lstEmpty, lstPeek, and lstHasCurrent
	lstCreate (&sTheList);
	success ("List Created");
	lstInsertAfter (&sTheList, &data, sizeof (char));
	assert (lstSize (&sTheList) == SIZE_ONE,
			    "List size is 1", "List size is NOT 1");
	lstPeek (&sTheList, &buffer, sizeof (char));
	assert (buffer == data, "The value was inserted",
			    "Value was not inserted");
	buffer = 0;
	assert (lstHasCurrent (&sTheList), "List has current",
			    "List does not have current");

	//Checking when the list is not empty & the size of the list
	assert (!lstIsEmpty (&sTheList), "List is not empty", "List is empty");
	lstInsertAfter (&sTheList, &value, sizeof (int));
	assert (lstSize (&sTheList) == SIZE_TWO,
		     "List size is 2", "List size is NOT 2");

	//Checking lstHasNext & lstHasCurrent
	lstFirst (&sTheList);
	assert (lstHasNext (&sTheList), "List has a successor",
		    "List does not have a successor");
	lstNext (&sTheList);
	lstPeek (&sTheList, &value, sizeof (int));
	assert (lstHasCurrent (&sTheList), "List has current node",
			   "List does not have current node");

	lstInsertAfter (&sTheList, &sTheList, sizeof (List));
	assert (lstSize (&sTheList) == SIZE_THREE,
		    	"List size is 3", "List size is NOT 3");

	assert (!lstHasNext (&sTheList),
			   "The current node does not have a successor",
			   "The current node has a successor");
	lstInsertAfter (&sTheList, &bTrue, sizeof (bool));
	assert (lstSize (&sTheList) == SIZE_FOUR,
			    "List size is 4", "List size is NOT 4");

	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		lstInsertAfter (&sTheList, &counter, sizeof (int));
	}
	assert (lstSize (&sTheList) == 2004, "List size is 2004",
		     "List size is NOT 2004");

	lstTerminate (&sTheList);
	success ("List Terminated");

	//Checking lstEmpty function
	lstCreate (&sTheList);
	success ("List Created");
	assert (lstIsEmpty (&sTheList), "List is empty", "List is not empty");
	assert (lstSize (&sTheList) == SIZE_ZERO,
		    	"List size is 0", "List size is NOT 0");
	lstInsertAfter (&sTheList, &value, sizeof (int));
	assert (!lstIsEmpty (&sTheList), "List is not empty", "List is empty");
	lstTerminate (&sTheList);
	success ("List Terminated");

	//Checking lstPeek Function
	lstCreate (&sTheList);
	success ("List Created");
	lstInsertAfter (&sTheList, &secondData, sizeof (char));
	lstInsertAfter (&sTheList, &thirdData, sizeof (char));
	lstInsertAfter (&sTheList, &fourthData, sizeof (char));
	lstPeek (&sTheList, &buffer, sizeof (char));
	assert (buffer == fourthData, "The peeked data is correct.",
			    "The peeked data is incorrect.");
	buffer = 0;
	lstFirst (&sTheList);
	lstNext (&sTheList);
	lstPeek (&sTheList, &data, sizeof (char));
	assert (data == thirdData, "The peeked data is correct.",
			    "The peeked data is incorrect.");
	lstTerminate (&sTheList);
	success ("List Terminated");

	//Check the size of the List
	assert (lstSize (&sTheList) == 0,
			    "List size is 0", "List size is NOT 0");

	//Checking lstInsertBefore & lstUpdateCurrent
	lstCreate (&sTheList);
	success ("List Created");
	lstInsertAfter (&sTheList, &num1, sizeof (int));
	assert (lstHasCurrent (&sTheList), "List has current",
			    "List does not have current");
	lstUpdateCurrent (&sTheList, &num2, sizeof (int));
	lstPeek (&sTheList, &buffer, sizeof (int));
	assert (buffer == num2, "The current has been updated",
			    "The current has not been updated.");
	buffer = 0;
	lstInsertAfter (&sTheList, &num3, sizeof (int));
	lstFirst (&sTheList);
	lstPeekNext (&sTheList, &buffer, sizeof (int));
	assert (buffer == num3, "The peeked data is correct.",
			    "The peeked data is incorrect.");
	assert (lstSize (&sTheList) == SIZE_TWO,
			    "List size is 2", "List size is NOT 2");
	lstDeleteCurrent (&sTheList, &num3, sizeof (int));
	lstPeek (&sTheList, &buffer, sizeof (int));
	assert (buffer != num2, "Value was deleted", "Value was not deleted");
	assert (lstSize (&sTheList) == SIZE_ONE,
			    "List size is 1", "List size is NOT 1");
	buffer = 0;
	lstInsertBefore (&sTheList, &num3, sizeof (int));
	lstPeek (&sTheList, &buffer, sizeof (int));

	assert (buffer == num3, "New element was inserted before.",
	        "Element was not inserted before");
	buffer = 0;
	assert (lstHasNext (&sTheList), "The current node has a successor",
			    "The current node does not have a successor");
	lstLast (&sTheList);
	lstPeek (&sTheList, &buffer, sizeof (int));
	assert (buffer == 3, "The peeked data is correct.",
			    "The peeked data is incorrect.");

	// Inserting a char before, but it is not working
	lstInsertAfter (&sTheList, &data, sizeof (char));
	assert (lstHasCurrent (&sTheList), "List has current",
			    "List does not have current");
	lstUpdateCurrent (&sTheList, &data, sizeof (char));
	lstPeek (&sTheList, &charBuffer, sizeof (char));
	assert (charBuffer == data, "The current has been updated",
			    "The current has not been updated.");
	charBuffer = '0';
	lstInsertAfter (&sTheList, &secondData, sizeof (char));
	lstDeleteCurrent (&sTheList, &secondData, sizeof (char));
	lstPeek (&sTheList, &charBuffer, sizeof (char));
	assert (charBuffer != secondData, "Value was deleted",
			    "Value was not deleted");
	assert (lstSize (&sTheList) == SIZE_THREE,
			    "List size is 3", "List size is NOT 3");
	charBuffer = '0';
	lstInsertBefore (&sTheList, &secondData, sizeof (char));
	lstPeek (&sTheList, &charBuffer, sizeof (char));
	assert (charBuffer == secondData, "New element was inserted before.",
		      "Element was not inserted before");
	charBuffer = '0';
	assert (lstHasNext (&sTheList), "The current node has a successor",
			    "The current node does not have a successor");

	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		lstInsertBefore (&sTheList, &counter, sizeof (int));
	}
	assert (lstSize (&sTheList) == 2004, "List size is 2004",
		      "List size is NOT 2004");

	lstTerminate (&sTheList);
	success ("List Terminated");

	//Checking Reverse Linked List
	printf ("\nChecking reverse linked list \n");
	lstCreate (&sTheList);
	lstInsertAfter (&sTheList, &num1, sizeof (int));
	lstInsertAfter (&sTheList, &num2, sizeof (int));
	lstInsertAfter (&sTheList, &num3, sizeof (int));
	printIntList (sTheList);
	lstReverse (&sTheList);
	printIntList (sTheList);
	printf ("The values in the list has been reversed! Hooray!\n");
	lstTerminate (&sTheList);
	success ("List Terminated");

	//Checking lstAppend
//	lstCreate (&sTheList);
//	success ("List Created");
//	lstCreate (&sTheSecondList);
//	success ("Second List Created");
//
//	lstAppend (&sTheList, &sTheSecondList);
//	assert (lstIsEmpty (&sTheSecondList), "List is empty", "List is not empty");
//
//	lstTerminate (&sTheList);
//	success ("List Terminated");
//	lstTerminate (&sTheSecondList);
//	success ("Second List Terminated");

	return EXIT_SUCCESS;
}
