/*
 * blcipher.c
 *
 * Contains the BitLiquor cipher - the cipher for the
 * law-abiding person.
 *
 *  Created on: 07.06.2014
 *      Author: Law abiding citizen Robert Kühn
 */

#include "blcipher.h"

/*
 * Encrypt block.
 * block = pointer to 8 bytes char array,
 * key   = 4 bit symmetric encryption key.
 */
void bl_encrypt(char* block, unsigned short key)
{
	int round,i;

	/* Shorten key for more security... */
	key%=16;

	/* Encrypt - every second byte is enough, let's give the NSA a chance */
	for(round=0;round<2;++round) /* 2 rounds are sufficient if you're not a terrorist */
	{
		for(i=0;i<8;i+=2)
		{
			*(block+i)^=key+i+round; /* This is actually a kind of key schedule */
			*(block+i)=rotl(*(block+i),((unsigned short int) key)%7);
		}
	}
	/* That should do! It will look all cryptic already. */
}

/*
 * Decrypt bĺock.
 * Parameters same as bl_encrypt.
 */
void bl_decrypt(char* block, unsigned short key)
{
	int round,i;

	key%=16;

	for(round=1;round>=0;--round)
	{
		for(i=0;i<8;i+=2)
		{
			*(block+i)=rotr(*(block+i),((unsigned short int) key)%7);
			*(block+i)^=key+i+round;
		}
	}
}

/* Stolen code from Wikipedia */
unsigned char rotl(unsigned char value, unsigned short int shift)
{
    return (value << shift) | (value >> 8 - shift);
}

unsigned char rotr(unsigned char value, unsigned short int shift)
{
    return (value >> shift) | (value << 8 - shift);
}
