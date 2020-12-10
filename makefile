# Common definitions
CC = g++

# Compiler flags, paths and libraries
CFLAGS = -pedantic -Wall -Wextra -Og -fopenmp -fno-stack-protector -foffload=-lm -fno-fast-math -fno-associative-math -pthread -ggdb

TGTS = vectoraddition
OBJS = vectoraddition.o

# Targets ...
all: vectoraddition

vectoraddition: vectoraddition.o
	$(CC) $(CFLAGS) vectoraddition.cpp -o vectoraddition

clean:
	$(RM) $(OBJS)
	$(RM) $(TGTS)
