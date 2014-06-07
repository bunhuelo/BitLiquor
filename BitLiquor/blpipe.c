/*
 * blpipe.c
 *
 *  BitLiquor Pipe
 *
 *  Created on: 07.06.2014
 *      Author: Robert Kühn, law-abiding citizen
 */

#include <stdio.h>
#include <stdlib.h>
#include "blcipher.h"
#include "blpipe.h"

int main(int argc, char** argv)
{
	size_t readcount;
	unsigned short int ioblocksize;
	int mode,i;
	unsigned short int key;
	char* buf;

	buf=malloc(8*sizeof(char));

	/* Count parameters */
	if(argc<3) fail_usage();

	/* High-tech command line parameter parsing algorithm */
	if(strcmp(argv[1],"--decrypt")==0)
	{
		mode=M_DECRYPT;
		ioblocksize=8; /* I was too lazy to implement proper padding */
	}
	else if(strcmp(argv[1],"--encrypt")==0)
	{
		mode=M_ENCRYPT;
		ioblocksize=7; /* You're gonna love this */
	}
	else fail_usage();
	key=((unsigned short int) *argv[2])%16;

	/* Open stdin in binary mode :) */
	if(!freopen(NULL,"rb",stdin)) fail_stream();

	/* Read and process */
	while((readcount=fread(buf,sizeof(char),ioblocksize,stdin))>0)
	{
		if(mode==M_DECRYPT)
		{
			bl_decrypt(buf,key);
			fwrite(buf,sizeof(char),(size_t) buf[7],stdout);
		}
		else if(mode==M_ENCRYPT)
		{
			/* Yup, we don't need padding. We use something I called "Bloating
			 * Garbage". Every block is terminated by a byte describing the actual
			 * length of the block.
			 */
			if(readcount<ioblocksize) for(i=readcount;i<7;++i) buf[i]='!';
			buf[7]=(char) readcount;
			bl_encrypt(buf,key);
			fwrite(buf,sizeof(char),8,stdout);
		}
	}

	free(buf);
	return 0;
}

/* Errors */
void fail_usage()
{
	fprintf(stderr,"Usage: blpipe <mode> <key>, where:\n");
	fprintf(stderr,"<mode> is either --encrypt or --decrypt and\n");
	fprintf(stderr,"<key> is a one-character passphrase from which the 4-bit key is derived. All characters except from the first one are omitted for safety reasons.\n\n");
	exit(1);
}

void fail_stream()
{
	fprintf(stderr,"Something went wrong with the input stream.\n\n");
	exit(2);
}

void fail_blocksize()
{
	fprintf(stderr,"Broken data or wrong key! Block size doesn't make sense.\n\n");
	exit(3);
}
