###########################################################################
# File name:  Makefile
# Author:     Ashley Ung
# Date:       10.11.21
# Class:      CS 300
# Assignment: Priority Queue 
# Purpose:    This is the Makefile for the Priority Queue   
###########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean valgrind

all: bin bin/pqueuedriver bin/pqdriver1 bin/pqdriver2 bin/pqMemTest

bin: 
	mkdir -p bin

bin/pqueuedriver: bin/pqueuedriver.o bin/pqueue.o ../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/pqueuedriver.o bin/pqueue.o ../ListADT/bin/list.o \
	-o bin/pqueuedriver 

bin/pqueuedriver.o: src/pqueuedriver.c include/pqueue.h
	${CC} ${CFLAGS} -c src/pqueuedriver.c -o bin/pqueuedriver.o

bin/pqdriver1: bin/pqdriver1.o bin/pqueue.o ../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/pqdriver1.o bin/pqueue.o ../ListADT/bin/list.o \
	-o bin/pqdriver1 

bin/pqdriver1.o: src/pqdriver1.c include/pqueue.h
	${CC} ${CFLAGS} -c src/pqdriver1.c -o bin/pqdriver1.o

bin/pqdriver2: bin/pqdriver2.o bin/pqueue.o ../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/pqdriver2.o bin/pqueue.o ../ListADT/bin/list.o \
	-o bin/pqdriver2

bin/pqdriver2.o: src/pqdriver2.c include/pqueue.h
	${CC} ${CFLAGS} -c src/pqdriver2.c -o bin/pqdriver2.o

bin/pqMemTest: bin/pqMemTest.o bin/pqueue.o ../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/pqMemTest.o bin/pqueue.o ../ListADT/bin/list.o \
	-o bin/pqMemTest

bin/pqMemTest.o: src/pqMemTest.c include/pqueue.h
	${CC} ${CFLAGS} -c src/pqMemTest.c -o bin/pqMemTest.o
	
bin/pqueue.o: src/pqueue.c include/pqueue.h ../ListADT/include/list.h 
	${CC} ${CFLAGS} -c src/pqueue.c -o bin/pqueue.o
	
../ListADT/bin/list.o:
			 cd ../ListADT; mkdir -p bin; make bin/list.o

valgrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/pqueuedriver
	
clean:
	rm -rf bin/*.o bin/pqueuedriver bin/pqdriver1 bin/pqdriver2 \
	bin/pqMemTest; cd ../ListADT; make clean
	