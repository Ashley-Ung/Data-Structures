###########################################################################
# File name:  Makefile
# Author:     Ashley Ung
# Date:       9.19.21
# Class:      CS 300
# Assignment: Dynamic List 
# Purpose: 	  This is the Makefile for the Dynamic List     
###########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean valgrind

all: bin bin/listdriver bin/smallListDriver bin/bigListDriver

bin: 
	mkdir -p bin

bin/listdriver: bin/listdriver.o bin/list.o
	${CC} ${CFLAGS} bin/listdriver.o bin/list.o -o bin/listdriver

bin/listdriver.o: src/listdriver.c include/list.h
	${CC} ${CFLAGS} -c src/listdriver.c -o bin/listdriver.o
	 
bin/list.o: src/list.c include/list.h
	${CC} ${CFLAGS} -c src/list.c -o bin/list.o
	
bin/smallListDriver: bin/smallListDriver.o bin/list.o 
	${CC} ${CFLAGS} bin/smallListDriver.o bin/list.o -o bin/smallListDriver

bin/smallListDriver.o: src/smallListDriver.c include/list.h
	${CC} ${CFLAGS} -c src/smallListDriver.c -o bin/smallListDriver.o
	
bin/bigListDriver: bin/bigListDriver.o bin/list.o 
	${CC} ${CFLAGS} bin/bigListDriver.o bin/list.o -o bin/bigListDriver

bin/bigListDriver.o: src/bigListDriver.c include/list.h
	${CC} ${CFLAGS} -c src/bigListDriver.c -o bin/bigListDriver.o

clean:
	rm -rf bin/*.o bin/listdriver bin/smallListDriver bin/bigListDriver