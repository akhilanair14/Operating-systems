CC=gcc
CFLAGS=-I.
DEPS =
OBJ = os_prog1_test.o
LIBS = -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: p1test test1 test2 test3 test4 test5

p1test: os_prog1_test.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test1: test1.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test2: test2.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test3: test3.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test4: test4.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test5: test5.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

#clean: 
