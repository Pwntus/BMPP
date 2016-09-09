CC = gcc
CFLAGS = -g -Wall
DEPS = bmpplib.h
OBJ = bmpp.o bmpplib.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

bmpp: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^