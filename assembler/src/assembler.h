/*
 * assembler.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

unsigned char jumpToLocs[256][64];//locations in code
	//where jumping to is possible
unsigned char jumpAddrInsLocs[256][64];//locations in
	//code where the destination addr of the jump
	//needs to be inserted
int jumpAddrInsLocsIndex;
int numJumpToLocs;
unsigned short outputOffset;

int assembleLine(char *line, unsigned char *output,
		unsigned char **outputPtr, int lineNum,
		int logLevel);
int assembleFile(char *inFilename, char *outFilename,
		int logLevel);
int insertJumpAddresses(unsigned char *output,
		int logLevel);


#endif /* ASSEMBLER_H_ */
