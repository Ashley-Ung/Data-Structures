/**************************************************************************
 File name:  binarytree.c
 Author:     Ashley Ung
 Date:	     11/12/21
 Class:		 	 CS300
 Assignment: Huffman Compression
 Purpose:    Implementation of a binary tree.
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/binarytree.h"

/**************************************************************************
 Function: 	 		createTree

 Description:   If the binary tree can be created, then the binary tree
 	 	 	 					exists and is empty; otherwise, if psNode is NULL, the
 	 	 	    			program exits.

 Parameters:		psNode      - pointer to a binary tree
 	 	 	 					probability - the frequency value

 Returned:	 	  None
 *************************************************************************/

 void createTree (BTNodePtr psNode, float probability)
{
	if (NULL == psNode)
	{
		return;
	}

	psNode->psLeftChild = NULL;
	psNode->psRightChild = NULL;
	psNode->szData = '\0';
	psNode->probability = probability;
}

 /**************************************************************************
  Function: 	 terminateTree

  Description: Recursively frees all memory associated with the binary
  	  	  	   tree.

  Parameters:	 psNode - pointer to a binary tree

  Returned:	   None
  *************************************************************************/

 void terminateTree (BTNodePtr psNode)
 {
	 if (NULL == psNode)
	 {
		 return;
	 }
	 terminateTree (psNode->psLeftChild);
	 terminateTree (psNode->psRightChild);
	 free (psNode);
 }

 /**************************************************************************
  Function: 	  combineTree

  Description:  Combines the left and right node that is connected to the
  	  	  	  	current root node.

  Parameters:	  psRoot       - pointer to the root node of the tree
  	  	  	  	psLeftChild  - pointer to the left node of the tree
  	  	  	  	psRightChild - pointer to the right node of the tree

  Returned:	 	  None
  *************************************************************************/

 void combineTree (BTNodePtr psRoot, BTNodePtr psLeftChild,
		               BTNodePtr psRightChild)
 {
	 BTNodePtr psLeft;
	 BTNodePtr psRight;

	 if (NULL == psRoot || NULL == psLeftChild || NULL == psRightChild)
	 {
		 return;
	 }

	 psLeft = (BTNodePtr) malloc (sizeof (BTNode));
	 memcpy (psLeft, psLeftChild, sizeof (BTNode));
	 psRight = (BTNodePtr) malloc (sizeof (BTNode));
	 memcpy (psRight, psRightChild, sizeof (BTNode));

	 psRoot->psLeftChild = psLeft;
	 psRoot->psRightChild = psRight;
 }

 /**************************************************************************
  Function: 	  printTree

  Description:  Prints the binary tree on it's side.

  Parameters:	  psNode - pointer to the root node of the tree
  	  	  	    space  - the spacing gap between the nodes

  Returned:	 	  None
  *************************************************************************/

 void printTree (BTNodePtr psRoot, int space)
 {
	const int HEIGHT = 1;
	const int CONVERSION_TO_FLOAT = 100000;

    if (NULL == psRoot)
    {
    	return;
    }

    space += HEIGHT;

    printTree (psRoot->psRightChild, space);

    printf ("\n");
    for (int i = HEIGHT; i < space; i++)
    {
    	printf ("\t");
    }
    printf ("%c - %.4f\n", psRoot->szData,
    		    psRoot->probability/CONVERSION_TO_FLOAT);

    printTree (psRoot->psLeftChild, space);
}

 /**************************************************************************
  Function: 	  bIsLeafNode

  Description:  A utility function to check if the tree contains a single
  	  	  	  	node; that is, if the tree contains a leaf node.

  Parameters:	  psRoot - pointer to the root node of the tree

  Returned:	   	True, if the tree contains a lead node; else, false.
  *************************************************************************/

bool bIsLeafNode (BTNodePtr psRoot)
{
	if (NULL == psRoot)
	{
		return 0;
	}
	return (NULL == psRoot->psLeftChild && NULL == psRoot->psRightChild);
}
