###########################################################################
# File name:  Makefile
# Author:     Ashley Ung
# Date:       11.12.21
# Class:      CS 300
# Assignment: Huffman Compression
# Purpose:    This is the Makefile for the Binary Tree ADT 
###########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean valgrind

all: bin bin/binarytreedriver

bin: 
	mkdir -p bin
	
bin/binarytreedriver: bin/binarytreedriver.o bin/binarytree.o \
	../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/binarytreedriver.o bin/binarytree.o \
	../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o \
	-o bin/binarytreedriver

bin/binarytreedriver.o: src/binarytreedriver.c include/binarytree.h
	${CC} ${CFLAGS} -c src/binarytreedriver.c -o bin/binarytreedriver.o
	 
bin/binarytree.o: src/binarytree.c include/binarytree.h \
	../PriorityQueueADT/include/pqueue.h ../ListADT/include/list.h
	${CC} ${CFLAGS} -c src/binarytree.c -o bin/binarytree.o
	
../PriorityQueueADT/bin/pqueue.o:
	cd ../PriorityQueueADT; mkdir -p bin; make bin/pqueue.o
			 
../ListADT/bin/list.o:
	cd ../ListADT; mkdir -p bin; make bin/list.o

valgrind: bin/binarytreedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/binarytreedriver data/data.txt

clean:
	rm -rf bin/*.o bin/binarytreedriver; cd ../PriorityQueueADT; make clean