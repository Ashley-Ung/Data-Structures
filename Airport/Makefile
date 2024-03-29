###########################################################################
# File name:  Makefile
# Author:     Ashley Ung
# Date:       10.30.21
# Class:      CS 300
# Assignment: Airport Simulation
# Purpose:    This is the Makefile for the Airport Simulation   
###########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean valgrind

all: bin bin/airportdriver bin/airporttestdriver

bin: 
	mkdir -p bin

bin/airportdriver: bin/airportdriver.o bin/airport.o \
	../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o \
	../QueueADT/bin/queue.o
	${CC} ${CFLAGS} bin/airportdriver.o bin/airport.o \
	../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o \
	../QueueADT/bin/queue.o -o bin/airportdriver -o bin/airportdriver 

bin/airportdriver.o: src/airportdriver.c include/airport.h
	${CC} ${CFLAGS} -c src/airportdriver.c -o bin/airportdriver.o
	
bin/airporttestdriver: bin/airporttestdriver.o bin/airport.o \
	../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o \
	../QueueADT/bin/queue.o
	${CC} ${CFLAGS} bin/airporttestdriver.o bin/airport.o \
	../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o \
	../QueueADT/bin/queue.o -o bin/airporttestdriver -o \
	bin/airporttestdriver 

bin/airporttestdriver.o: src/airporttestdriver.c include/airport.h
	${CC} ${CFLAGS} -c src/airporttestdriver.c -o bin/airporttestdriver.o
	
bin/airport.o: src/airport.c include/airport.h \
	../PriorityQueueADT/include/pqueue.h ../ListADT/include/list.h \
	../QueueADT/include/queue.h
	${CC} ${CFLAGS} -c src/airport.c -o bin/airport.o

../QueueADT/bin/queue.o:
			 cd ../QueueADT; mkdir -p bin; make bin/queue.o
			 
../PriorityQueueADT/bin/pqueue.o:
			 cd ../PriorityQueueADT; mkdir -p bin; make bin/pqueue.o
			 
../ListADT/bin/list.o:
			 cd ../ListADT; mkdir -p bin; make bin/list.o

valgrind: bin/airportdriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/airportdriver data/airport.txt
	
clean:
	rm -rf bin/*.o bin/airportdriver bin/airporttestdriver; cd ../QueueADT; \
	make clean