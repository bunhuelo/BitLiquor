/*
 * blcipher.h
 *
 *  Contains header file for blcipher.c, which contains the
 *  BitLiquor block cipher.
 *
 *  Created on: 07.06.2014
 *      Author: Law abiding citizen Robert Kühn
 */

#ifndef BLCIPHER_H_
#define BLCIPHER_H_

void bl_encrypt(char* block, unsigned short key);
void bl_decrypt(char* block, unsigned short key);

unsigned char rotl(unsigned char value, unsigned short int shift);
unsigned char rotr(unsigned char value, unsigned short int shift);

#endif /* BLCIPHER_H_ */
