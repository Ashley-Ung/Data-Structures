/**************************************************************************
 File name:  stkdriver.c
 Author:     Computer Science, Pacific University
 Date:			 9.9.21
 Class:			 CS300
 Assignment: Static Generic Stack
 Purpose:    Test driver for a static stack of generic elements
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/stk.h"

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the stack

 Parameters:	none

 Returned:	 	Exit Status
**************************************************************************/

int main ()
{
	const int EVEN = 2;

	Stack sTheStack;
	char data;
	char input[STK_MAX_ELEMENTS];
	int i = 0;
	int middleChar;
	bool bIsMatch = true;

	printf ("Enter a word: ");
	scanf ("%s", input);

	while (strcmp (input, "QUIT"))
	{
		middleChar = (strlen (input) / EVEN);

		for (i = 0; i < middleChar; i++)
		{
			stkPush (&sTheStack, input[i]);
		}

		if (strlen (input) % EVEN != 0)
		{
			i++;
		}

		while (input[i] != '\0')
		{
			stkPop (&sTheStack, &data);

			if (input[i] != data)
			{
				bIsMatch = false;
			}
			i++;
		}

		if (!bIsMatch)
		{
			printf ("%s is NOT a Palindrome \n", input);
		}

		else
		{
			printf("%s is a Palindrome\n", input);
		}

		printf ("Enter a word: ");
		bIsMatch = true;
		scanf ("%s", input);
	}

	return EXIT_SUCCESS;
}
