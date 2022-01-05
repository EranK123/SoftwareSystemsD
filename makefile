CC=gcc
AR=ar
FLAGS= -g -Wall
LM = -lm
RCS = -rcs
SHARED = -shared
C = -c
O = -o

all: graph

graph: graph.o
		$(CC) $(FLAGS) -o graph graph.o

graph.o: graph.c graph.h
		$(CC) $(FLAGS) -c graph.c


.PHONY: clean all

clean:
	rm -f *.o graph
