CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g -O
LDFLAGS = -lm
MAIN = Lighting_tests

OBJS = Lighting Primitives
PROGS = $(MAIN)

all : $(PROGS)

$(MAIN) : $(MAIN).c $(OBJS:%=%.o)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

Lighting.o : Lighting.c Lighting.h
	$(CC) $(CFLAGS) -c -o $@ $<

Primitives.o : 
	cp ../Primitives/Primitives.o .


clean :
	rm -f $(PROGS) *.o

