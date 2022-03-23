###########################################################################
# File name:  Makefile
# Author:     Ashley Ung
# Date:       11.12.21
# Class:      CS 300
# Assignment: Huffman Compression 
# Purpose:    This is the Makefile for the huffman compression. 
###########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean valgrind

all: bin bin/Driver bin/testDriver

bin: 
	mkdir -p bin
	
bin/Driver: bin/Driver.o bin/huffman.o ../BinaryTreeADT/bin/binarytree.o \
	../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/Driver.o bin/huffman.o \
	../BinaryTreeADT/bin/binarytree.o ../PriorityQueueADT/bin/pqueue.o \
	../ListADT/bin/list.o -o bin/Driver

bin/Driver.o: src/Driver.c include/huffman.h
	${CC} ${CFLAGS} -c src/Driver.c -o bin/Driver.o
	
bin/testDriver: bin/testDriver.o bin/huffman.o \
	../BinaryTreeADT/bin/binarytree.o ../PriorityQueueADT/bin/pqueue.o \
	../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/testDriver.o bin/huffman.o \
	../BinaryTreeADT/bin/binarytree.o ../PriorityQueueADT/bin/pqueue.o \
	../ListADT/bin/list.o -o bin/testDriver

bin/testDriver.o: src/testDriver.c include/huffman.h
	${CC} ${CFLAGS} -c src/testDriver.c -o bin/testDriver.o
	 
bin/huffman.o: src/huffman.c include/huffman.h \
	../BinaryTreeADT/include/binarytree.h \
	../PriorityQueueADT/include/pqueue.h ../ListADT/include/list.h
	${CC} ${CFLAGS} -c src/huffman.c -o bin/huffman.o
	
../BinaryTreeADT/bin/binarytree.o:
	   cd ../BinaryTreeADT; mkdir -p bin; make bin/binarytree.o

../PriorityQueueADT/bin/pqueue.o:
	   cd ../PriorityQueueADT; mkdir -p bin; make bin/pqueue.o
			 
../ListADT/bin/list.o:
	   cd ../ListADT; mkdir -p bin; make bin/list.o
			 
valgrind: bin/Driver bin/testDriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/Driver bin/testDriver data/data.txt \
	data/encodeMessage.txt
	
clean:
	rm -rf bin/*.o bin/Driver bin/testDriver; cd ../PriorityQueueADT; make clean