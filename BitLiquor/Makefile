all: blpipe

clean:
	rm -rf blpipe 
	rm -rf *.o
  
blcipher.o:
	gcc -c blcipher.c
	
blpipe: blcipher.o
	gcc -O3 -o blpipe -Wpedantic blcipher.o blpipe.c
  