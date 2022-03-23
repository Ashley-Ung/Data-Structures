/**************************************************************************
 File name:	  binarytree.h
 Author:      Ashley Ung
 Date:		    11/12/2021
 Class:       CS300
 Assignment:  Huffman Compression
 Purpose:     This file defines the constants, data structures, and
              function prototypes for implementing the Binary Tree ADT
 *************************************************************************/

#ifndef INCLUDE_BINARYTREE_H_
#define INCLUDE_BINARYTREE_H_

#include <stdbool.h>

//*************************************************************************
// User-defined types
//*************************************************************************

typedef struct BTNode *BTNodePtr;
typedef struct BTNode
{
	BTNodePtr psLeftChild;
	BTNodePtr psRightChild;
	float probability;
	char szData;
} BTNode;

/**************************************************************************
* Allocation and Deallocation
**************************************************************************/

extern void createTree (BTNodePtr psNode, float probability);

extern void terminateTree (BTNodePtr psNode);

/**************************************************************************
* Binary Tree Operations
**************************************************************************/

extern void combineTree (BTNodePtr psRoot, BTNodePtr psLeftChild,
										     BTNodePtr psRightChild);

extern bool bIsLeafNode (BTNodePtr psRoot);

/**************************************************************************
* Display Binary Tree
**************************************************************************/

extern void printTree (BTNodePtr psRoot, int space);

#endif /* INCLUDE_BINARYTREE_H_ */
