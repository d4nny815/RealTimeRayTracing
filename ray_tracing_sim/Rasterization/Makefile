CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g
LDFLAGS = -lm
MAIN = test_Rasterization

OBJS = Rasterization ArrayList Primitives
PROGS = $(MAIN)

all : $(PROGS)

$(MAIN) : $(MAIN).c $(OBJS:%=%.o)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

Rasterization.o : Rasterization.c Rasterization.h
	$(CC) $(CFLAGS) -c $<

ArrayList.o : 
	cp ../build/ArrayList.o .

Primitives.o :
	cp ../build/Primitives.o .

clean :
	rm -f $(PROGS) *.o

