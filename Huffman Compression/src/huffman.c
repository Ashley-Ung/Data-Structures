/**************************************************************************
 File name:  huffman.c
 Author:     Ashley Ung
 Date:	     11/12/21
 Class:		 	 CS300
 Assignment: Huffman Compression
 Purpose:    Implementation of the huffman compression.
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/huffman.h"
#include "../../PriorityQueueADT/include/pqueue.h"

/**************************************************************************
 Function:    buildFrequencyTable

 Description: Builds a huffman frequency table that contains a distinct
 	 	 	  			character and frequency value.

 Parameters:  psParent    - pointer to the parent node of the tree
 	 	 	  			psThePQueue - pointer to a priority queue

 Returned:    None
 *************************************************************************/

void buildFrequencyTable (BTNodePtr psParent, PriorityQueuePtr psThePQueue,
													float probability, char alphabet)
{
	const int CONVERSION_TO_FLOAT = 100000;

	BTNode psNode;

	createTree (&psNode, probability * CONVERSION_TO_FLOAT);
	psNode.szData = alphabet;
	pqueueEnqueue (psThePQueue, &psNode, sizeof (BTNode), (int)
				  			(probability * CONVERSION_TO_FLOAT));
}

/**************************************************************************
 Function:    huffmanBuildTree

 Description: Creates a huffman tree by making a priority queue of nodes.

 Parameters:  psParent    - pointer to the parent node of the tree
 	 	 	        psThePQueue - pointer to a priority queue

 Returned:    None
 *************************************************************************/

void huffmanBuildTree (BTNodePtr psParent, PriorityQueuePtr psThePQueue)
{
	const int SIZE_ONE = 1;

	BTNode psNode;
	BTNode leftBuffer;
	BTNode rightBuffer;

	int leftPriority;
	int rightPriority;

	while (pqueueSize (psThePQueue) > SIZE_ONE)
	{
		pqueueDequeue (psThePQueue, &leftBuffer, sizeof (BTNode),
					   	 	   &leftPriority);
		pqueueDequeue (psThePQueue, &rightBuffer, sizeof (BTNode),
				 	         &rightPriority);
		createTree (&psNode, leftPriority + rightPriority);
		combineTree (&psNode, &leftBuffer, &rightBuffer);
		pqueueEnqueue (psThePQueue, &psNode, sizeof (BTNode),
				           leftPriority + rightPriority);
	}
	pqueueDequeue (psThePQueue, psParent, sizeof (BTNode), &rightPriority);
}

/**************************************************************************
 Function:     huffmanCompress

 Description:  Traverses the tree and stores the codes.

 Parameters:   psRoot  			    - pointer to the root node of the tree
 	 	 	   	 	 	 prefix  			    - the character to compress
 	 	 	   	 	 	 aCurrentEncoding - the current code to encode
 	 	 	   	 	 	 index			      - a counter to move along the tree

 Returned:     None
 *************************************************************************/

void huffmanCompress (BTNodePtr psRoot, char prefix, int aCurrentEncoding[],
					            int index)
{
	const int LEFT_BRANCH = 0;
	const int RIGHT_BRANCH = 1;
	const int INCREMENT = 1;

	if (NULL == psRoot)
	{
		return;
	}

	if (psRoot->psLeftChild)
	{
		aCurrentEncoding[index] = LEFT_BRANCH;
		huffmanCompress (psRoot->psLeftChild, prefix, aCurrentEncoding,
						         index + INCREMENT);
	}

	if (psRoot->psRightChild)
	{
		aCurrentEncoding[index] = RIGHT_BRANCH;
		huffmanCompress (psRoot->psRightChild, prefix, aCurrentEncoding,
				     	       index + INCREMENT);
	}
	if (bIsLeafNode (psRoot) && psRoot->szData == prefix)
	{
		for (int i = 0; i < index; i++)
		{
			printf ("%d", aCurrentEncoding[i]);
		}
	}
}

/**************************************************************************
 Function:    huffmanDecompress

 Description: Traverses the huffman tree and decodes the encoded array of
 	 	 	        characters.

 Parameters:  psRoot    - a pointer to the root node of the tree
 	 	 	        aEncoding - the code to decode

 Returned:    None
 *************************************************************************/

void huffmanDecompress (BTNodePtr psRoot, char aEncoding[])
{
	const char LEFT_BRANCH = '0';

	BTNodePtr psNode;

	psNode = psRoot;

	if (NULL == psRoot)
	{
		return;
	}

	for (int i = 0; i < strlen (aEncoding); i++)
	{
		if (aEncoding[i] == LEFT_BRANCH)
		{
			psNode = psNode->psLeftChild;
		}
		else
		{
			psNode = psNode->psRightChild;
		}
		if (psNode->szData != '\0')
		{
			if (psNode->szData == '-')
			{
				printf (" ");
			}
			else
			{
				printf ("%c", psNode->szData);
			}
			psNode = psRoot;
		}
	}
	printf ("\n");
}

/**************************************************************************
 Function:    terminateHuffmanTree

 Description: Terminates the nodes that were allocated.

 Parameters:  psParent    - a pointer to the parent node of the tree
 	 	 	        psThePQueue - pointer to a priority queue

 Returned:    None
 *************************************************************************/

void terminateHuffmanTree (BTNodePtr psParent, PriorityQueuePtr psThePQueue)
{
	terminateTree (psParent->psLeftChild);
	terminateTree (psParent->psRightChild);
	pqueueTerminate (psThePQueue);
}
