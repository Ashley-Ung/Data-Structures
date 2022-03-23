#############################################################################
# File name:  Makefile
# Author:     Computer Science, Pacific University
# Date:       9.28.16
# Class:      CS 300
# Assignment: CharacterStaticStack
# Purpose: 	  This is the Makefile for the CharacterStaticStack    
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/stkdriver bin/stktester

bin: 
	mkdir -p bin

bin/stkdriver: bin/stkdriver.o bin/stk.o
	${CC} ${CFLAGS} bin/stkdriver.o bin/stk.o -o bin/stkdriver

bin/stkdriver.o: src/stkdriver.c include/stk.h
	${CC} ${CFLAGS} -c src/stkdriver.c -o bin/stkdriver.o

bin/stktester: bin/stktester.o bin/stk.o
	${CC} ${CFLAGS} bin/stktester.o bin/stk.o -o bin/stktester

bin/stktester.o: src/stktester.c include/stk.h
	${CC} ${CFLAGS} -c src/stktester.c -o bin/stktester.o
	 
bin/stk.o: src/stk.c include/stk.h
	${CC} ${CFLAGS} -c src/stk.c -o bin/stk.o
 	
tarball: clean
	tar czf ../cs300_1_khoj0332.tar.gz ../CharacterStaticStack

clean:
	rm -rf bin/*.o bin/stkdriver bin/stktester