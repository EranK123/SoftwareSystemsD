CC=gcc
AR=ar
FLAGS= -g -Wall
LM = -lm
RCS = -rcs
SHARED = -shared
C = -c
O = -o

all: graph

graph: libmygraph.a
		$(CC) $(FLAGS) -o graph libmygraph.a

libmygraph.a: graph.o
	$(AR) $(RCS) libmygraph.a graph.o

graph.o: graph.c graph.h
		$(CC) $(FLAGS) -c graph.c


.PHONY: clean all

clean:
	rm -f *.o *.a graph