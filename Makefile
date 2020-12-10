# Common definitions
CC = g++

# Compiler flags, paths and libraries
CFLAGS = -pedantic -Wall -Wextra -Og -fopenmp -fno-stack-protector -foffload=-lm -fno-fast-math -fno-associative-math -pthread -ggdb

TGTS = openmp-example
OBJS = openmp-example.o

# Targets ...
all: openmp-example

openmp-example: openmp-example.o
	$(CC) $(CFLAGS) openmp-example.cpp -o openmp-example

clean:
	$(RM) $(OBJS)
	$(RM) $(TGTS)
