/**************************************************************************
 File name:	  huffman.h
 Author:      Ashley Ung
 Date:		  	11/12/2021
 Class:       CS300
 Assignment:  Huffman Compression
 Purpose:     This file defines the constants, data structures, and
              function prototypes for implementing the huffman
              compression.
 *************************************************************************/

#ifndef INCLUDE_HUFFMAN_H_
#define INCLUDE_HUFFMAN_H_

#include "../../PriorityQueueADT/include/pqueue.h"
#include "../../BinaryTreeADT/include/binarytree.h"

/**************************************************************************
* Huffman Operations
**************************************************************************/

extern void buildFrequencyTable (BTNodePtr psParent,
																 PriorityQueuePtr psThePQueue,
																 float probability, char alphabet);

extern void huffmanBuildTree (BTNodePtr psParent,
					          					PriorityQueuePtr psThePQueue);

extern void createHuffmanTree (BTNodePtr psRoot);

extern void huffmanCompress (BTNodePtr psRoot, char prefix,
							 	 	 	 	 	 	   int aCurrentEncoding[], int index);

extern void huffmanDecompress (BTNodePtr psRoot, char aEncoding[]);

extern void terminateHuffmanTree (BTNodePtr psParent,
																	PriorityQueuePtr psThePQueue);

#endif /* INCLUDE_HUFFMAN_H_ */
