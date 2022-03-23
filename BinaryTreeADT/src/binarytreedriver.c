/**************************************************************************
 File name:  binarytreedriver.c
 Author:     Ashley Ung
 Date:	     11/12/2021
 Class:		   CS300
 Assignment: Huffman Compression
 Purpose:    A test driver for the binary tree ADT
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../../PriorityQueueADT/include/pqueue.h"
#include "../../BinaryTreeADT/include/binarytree.h"

/**************************************************************************
 Function:    validateFile

 Description: Checks if the file was opened successfully.

 Parameters:  inFile - the file to validate

 Returned:    None
 *************************************************************************/

void validateFile (FILE *inFile)
{
	if (NULL == inFile)
	{
		printf ("Could not open file.\n");
		exit (EXIT_FAILURE);
	}
}

/**************************************************************************
 Function: 	 	main

 Description: Tests the functionality of the binary tree ADT.

 Parameters:	argc - number of command line arguments
 	 	 	        argv - the command line arguments

 Returned:	 	Exit Status
**************************************************************************/

int main (int argc, char **argv)
{
	const int CONVERSION_TO_FLOAT = 100000;
	const int SIZE_ONE = 1;
	const int SPACE_INDEX = 0;

	char alphabet;
	float probability;
	int leftPriority;
	int rightPriority;
	BTNode psParent;
	BTNode psLeftChild;
	BTNode psRightChild;
	PriorityQueue sTheQueue;

	pqueueCreate (&sTheQueue);

	FILE* inFile = NULL;

	inFile = fopen ("data/data.txt", "r");

	validateFile (inFile);

	puts ("\nPrinting the read in data from the file.");
	while (!feof (inFile))
	{
		fscanf (inFile, "%c %f\n", &alphabet, &probability);
		printf ("The read in data is: %c %.4f\n", alphabet, probability);
		createTree (&psParent, probability);
		psParent.szData = alphabet;
		pqueueEnqueue (&sTheQueue, &psParent, sizeof (BTNode), (int)
					        (probability * CONVERSION_TO_FLOAT));
	}

	puts ("\nPrinting the left and right side frequencies.");
	while (pqueueSize (&sTheQueue) > SIZE_ONE)
	{
		pqueueDequeue (&sTheQueue, &psLeftChild, sizeof (BTNode),
					         &leftPriority);
		printf ("Left-side frequency: %d\n", leftPriority);
		pqueueDequeue (&sTheQueue, &psRightChild, sizeof (BTNode),
				 	         &rightPriority);
		printf ("Right-side frequency: %d\n", rightPriority);
		createTree (&psParent, leftPriority + rightPriority);
		combineTree (&psParent, &psLeftChild, &psRightChild);
		pqueueEnqueue (&sTheQueue, &psParent, sizeof (BTNode),
				          leftPriority + rightPriority);
		printf ("Frequency sum: %d\n", leftPriority + rightPriority);
	}

	puts ("Printing the tree.");
	printTree (&psParent, SPACE_INDEX);

	terminateTree (psParent.psLeftChild);
	terminateTree (psParent.psRightChild);
	pqueueTerminate (&sTheQueue);

	fclose (inFile);
	return 0;
}

