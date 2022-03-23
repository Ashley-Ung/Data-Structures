###########################################################################
# File name:  Makefile
# Author:     Ashley Ung
# Date:       10.24.21
# Class:      CS 300
# Assignment: Queue 
# Purpose:    This is the Makefile for the Queue   
###########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean valgrind

all: bin bin/queuedriver

bin: 
	mkdir -p bin

bin/queuedriver: bin/queuedriver.o bin/queue.o \
  ../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/queuedriver.o bin/queue.o \
	../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o -o \
	bin/queuedriver -o bin/queuedriver 

bin/queuedriver.o: src/queuedriver.c include/queue.h
	${CC} ${CFLAGS} -c src/queuedriver.c -o bin/queuedriver.o
	
bin/queue.o: src/queue.c include/queue.h \
	../PriorityQueueADT/include/pqueue.h ../ListADT/include/list.h
	${CC} ${CFLAGS} -c src/queue.c -o bin/queue.o

../PriorityQueueADT/bin/pqueue.o:
			 cd ../PriorityQueueADT; mkdir -p bin; make bin/pqueue.o
			 
../ListADT/bin/list.o:
			 cd ../ListADT; mkdir -p bin; make bin/list.o

valgrind: bin/queuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/queuedriver
	
clean:
	rm -rf bin/*.o bin/queuedriver; cd ../PriorityQueueADT; make clean