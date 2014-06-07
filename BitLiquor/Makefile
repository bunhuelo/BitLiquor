# Compiler
CC=gcc
# Remove
RM=rm -rf
# Compiler flags
CFLAGS=-Ofast -Wpedantic

# Here we go:
all: blpipe

clean:
	$(RM) blpipe blcipher.o
  
blcipher.o: blcipher.c blcipher.h
	$(CC) $(CFLAGS) -c blcipher.c
	
blpipe: blcipher.o blpipe.c blpipe.h
	$(CC) $(CFLAGS) -o blpipe blcipher.o blpipe.c
  