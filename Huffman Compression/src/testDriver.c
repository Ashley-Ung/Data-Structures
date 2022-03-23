/**************************************************************************
 File name:  testDriver.c
 Author:     Ashley Ung
 Date:	     11/12/2021
 Class:		   CS300
 Assignment: Huffman Compression
 Purpose:    A test driver for Huffman Compression.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/huffman.h"
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

 Description: Tests the functionality of the Huffman Compression

 Parameters:	argc - number of command line arguments
 	 	 	        argv - the command line arguments

 Returned:	 	Exit Status
**************************************************************************/

int main (int argc, char **argv)
{
	const char *DATA_FILE = "data/data.txt";
	const char *PRINT_OPT = "-p", *ENCODE_OPTION = "-e", *DECODE_OPTION = "-d";
	const char *READ = "r";
	const int MAX_CHARS = 1000;
	const int STARTING_INDEX = 0;
	const int ARGUMENT_TWO = 1;
	const int ARGUMENT_THREE = 2;
	const int SPACE_INDEX = 0;

	char alphabet;
	float probability;
	int aEncode[MAX_CHARS];
	char encodeMessage = '\0';
	char decodeMessage[MAX_CHARS];
	BTNode psParent;
	PriorityQueue sTheQueue;

	pqueueCreate (&sTheQueue);

	FILE* inFile = NULL;
	FILE* dataFile = NULL;

	inFile = fopen (DATA_FILE, READ);
	validateFile (inFile);

	while (!feof (inFile))
	{
		fscanf (inFile, "%c %f\n", &alphabet, &probability);
		buildFrequencyTable (&psParent, &sTheQueue, probability, alphabet);
	}

	huffmanBuildTree (&psParent, &sTheQueue);

	if (!strcmp (PRINT_OPT, argv[ARGUMENT_TWO]))
	{
		printTree (&psParent, SPACE_INDEX);
	}
	else
	{
		dataFile = fopen (argv[ARGUMENT_THREE], "r");
		validateFile (dataFile);

		if (!strcmp (ENCODE_OPTION, argv[ARGUMENT_TWO]))
		{
			while ((encodeMessage = fgetc (dataFile)) != EOF)
			{
				if (encodeMessage == ' ')
				{
					encodeMessage = '-';
				}
				huffmanCompress (&psParent, encodeMessage, aEncode,
						             STARTING_INDEX);
			}
			printf ("\n");
		}
		else if (!strcmp (DECODE_OPTION, argv[ARGUMENT_TWO]))
		{
			while ((fscanf (dataFile, "%[^\n]", decodeMessage)) != EOF)
			{
				fgetc (dataFile);
				huffmanDecompress (&psParent, decodeMessage);
			}
		}
		fclose (dataFile);
	}

	terminateHuffmanTree (&psParent, &sTheQueue);

	fclose (inFile);
	return 0;
}
