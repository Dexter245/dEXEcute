/*
 * assembler.c
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "assembler.h"
#include "constants.h"
#include "utils.h"
#include "tests.h"

int assembleLine(char *line, unsigned char *output,
		unsigned char **outputPtr, int lineNum, int logLevel){

	//"remove" comment if existing
	unsigned char *commentPos = strchr(line, '/');
	if(commentPos != 0){
		*commentPos = '\0';
	}

	char delimiters[] = " \n";
	char *word = 0;
	char *arg0 = 0;
	char *arg1 = 0;
	char *arg2 = 0;
	int returnValue = 0;
	int numArgsNeeded = 0;


	//break down line to its parts
	word = strtok(line, delimiters);
	arg0 = strtok(0, delimiters);
	arg1 = strtok(0, delimiters);
	arg2 = strtok(0, delimiters);

	//everything to lowercase
	if(word != 0)
		for(int i = 0; word[i] != '\0' ; i++)
			word[i] = tolower(word[i]);
	if(arg0 != 0)
		for(int i = 0; arg0[i] != '\0'; i++)
			arg0[i] = tolower(arg0[i]);
	if(arg1 != 0)
		for(int i = 0; arg1[i] != '\0'; i++)
			arg1[i] = tolower(arg1[i]);
	if(arg2 != 0)
		for(int i = 0; arg2[i] != '\0'; i++)
			arg2[i] = tolower(arg2[i]);

	//check for errors in line
	int opcodeNum = getOpcodeNum(word);
	if(opcodeNum == -1){
		if(logLevel >= 1)
			printUnknownInstructionError(lineNum, word);
		returnValue = -1;
	}
	numArgsNeeded = opcode_numArgs[opcodeNum];
	if(hasArgNumError(numArgsNeeded,  _args_)){
		if(logLevel >= 1)
			printNumArgsError(lineNum, numArgsNeeded, getNumArgs(_args_));
		returnValue = -1;
	}
	if(hasArgLitError(opcode_argsLit[opcodeNum][0],
			opcode_argsLit[opcodeNum][1],
			opcode_argsLit[opcodeNum][2], _args_)){

		if(logLevel >= 1)
			printNumArgsError(lineNum, numArgsNeeded, getNumArgs(_args_));
		returnValue = -1;
	}

	//write opcode
	unsigned char opcode = (unsigned char) opcodeNum;
	opcode <<= 2;
	bool isArg0Lit = isArgLit(arg0);
	bool isArg1Lit = isArgLit(arg1);
	if(isArg0Lit)
		opcode |= 0b00000010;
	if(isArg1Lit)
		opcode |= 0b00000001;

	**outputPtr = opcode;
	++(*outputPtr);

	//write arg0
	if(numArgsNeeded > 0){
		//jump arg0 jumpLit
		if(opcode == 62 && isArgJumpLit(arg0)){//62 = 15*4+2, jmp :bla

			jumpAddrInsLocs[jumpAddrInsLocsIndex][0] =
					(unsigned char) ((outputOffset+1)>>8);
			jumpAddrInsLocs[jumpAddrInsLocsIndex][1] =
					(unsigned char) ((outputOffset+1)&0x00FF);
			if(logLevel >= 2){
				printf("argJumpLit: %s\n", arg0);
				printf("jumpAddrInsLoc: %u\n", outputOffset+1);
				printf("written addr: %u %u\n",
					jumpAddrInsLocs[jumpAddrInsLocsIndex][0],
					jumpAddrInsLocs[jumpAddrInsLocsIndex][1]);
			}
			strcpy(jumpAddrInsLocs[jumpAddrInsLocsIndex+1], arg0);
			jumpAddrInsLocsIndex += 2;
			*outputPtr += 2;
		}
		else if(isArg0Lit){
			unsigned int arg0int = atoi(arg0);
			**outputPtr = (unsigned char) (arg0int>>8);
			++(*outputPtr);
			//output[outputPtr] = (arg0int<<24)>>24;
			**outputPtr = (unsigned char) (arg0int & 0x00FF);
			++(*outputPtr);
		}else{
			int rNum = getRegisterNum(arg0);
			if(rNum == -1){
				if(logLevel >= 1)
					printUnknownRegisterError(lineNum, arg0);
				returnValue = -1;
			}
			**outputPtr = (unsigned char) (rNum & 0x000000FF);
			++(*outputPtr);
		}
	}

	//write arg1
	if(numArgsNeeded > 1){
		if(isArg1Lit){
			unsigned int arg1int = atoi(arg1);
			**outputPtr = (unsigned char) (arg1int>>24);//24 instead of 8?
			++(*outputPtr);
			//output[outputPtr] = (arg1int<<24)>>24;
			**outputPtr = (unsigned char) (arg1int & 0x000000FF);
			++(*outputPtr);
		}else{
			int rNum = getRegisterNum(arg1);
			if(rNum == -1){
				if(logLevel >= 1)
					printUnknownRegisterError(lineNum, arg1);
				returnValue = -1;
			}
			**outputPtr = (unsigned char) (rNum & 0x000000FF);
			++(*outputPtr);
		}
	}


	//write arg2
	if(numArgsNeeded > 2){
		int rNum = getRegisterNum(arg2);
		if(rNum == -1){
			if(logLevel >= 1)
				printUnknownRegisterError(lineNum, arg2);
			returnValue = -1;
		}
		**outputPtr = (unsigned char) (rNum & 0x000000FF);
		++(*outputPtr);
	}


	return returnValue;
}

int insertJumpAddresses(unsigned char *output, int logLevel){

	//return 0;
	int returnValue = 0;

	int len = (jumpAddrInsLocsIndex-1)*2;
	int len2 = numJumpToLocs*2;
	if(logLevel >= 2){
		printf("jumpAddrInsLocsIndex: %d\n", jumpAddrInsLocsIndex);
		printf("numJumpLocs: %d\n", numJumpToLocs);
	}
	for(int i = 0; i < len; i+=2){
		char *jName = jumpAddrInsLocs[i+1];
		for(int j = 0; j < len2; j+=2){
			if(strcmp(jName, jumpToLocs[j]) == 0){
				if(logLevel >= 2)
					printf("inserting jumpAddr\n");
				//get outputAddress to write to
				unsigned short wAddr = (jumpAddrInsLocs[i][0]<<8) |
						(jumpAddrInsLocs[i][1]);
				//write where to jump to
				output[wAddr] = jumpToLocs[j+1][0];
				output[wAddr+1] = jumpToLocs[j+1][1];
				break;
			}
		}
	}


	return returnValue;
}


int assembleFile(char *inputFilename, char *outputFilename, int logLevel){

	//init arrays
	for(int i = 0; i < 256; i++){
		for(int j = 0; j < 64; j++){
			jumpToLocs[i][j] = 0;
			jumpAddrInsLocs[i][j] = 0;
		}
	}

	int returnValue = 0;
	FILE *inputFile;//dasm source code
	FILE *outputFile;//dexe binary executable

	jumpAddrInsLocsIndex = 0;
	numJumpToLocs = 0;

	unsigned char *output = malloc(_64k);
	for(int i = 0; i < _64k; i++)
		output[i] = 0;

	inputFile = fopen(inputFilename, "r");
	if(inputFile == 0){
		printf("dasm file \"%s\" doesn't exist. Nothing to asm.\n",
				inputFilename);
		return ERROR_NO_INPUTFILE;
	}

	outputFile = fopen(outputFilename, "wb+");
	if(outputFile == 0){
		printf("Couldn't write \"%s\". Do you have permissions "
				"to write there?\n", outputFilename);
	}




	unsigned char line[256];
	int lineNum = 0;
	bool writeToFile = true;
	unsigned char *outputPtr = output;//which part of output to write to
	const unsigned char *outputPtr0 = output;//always points at beginning
		//of output
	outputOffset = 0;
	int jumpLocsIndex = 0;

	//write dexe-header
	for(int i = 0; i < DEXE_HEADER_SIZE; i++){
		*outputPtr = DEXE_HEADER[i];
		++outputPtr;
	}

	//main asm loop
	while(1){

		outputOffset = (unsigned short) (outputPtr - outputPtr0);

		fgets(line, 255, inputFile);
		if(logLevel >= 2)
			printf("\n\nline: %s", line);

		//reached EOF
		if(feof(inputFile)){
			if(lineNum == 0){
				printf("Given inputfile is (effectively) empty. Nothing to asm.\n");
				return ERROR_EMPTY_INPUTFILE;
			}
			else{
				if(logLevel >= 2)
					printf("Job done.\n");
				break;
			}
		}

		//empty line
		if(line[0] == '\n'){
			if(logLevel >= 2)
				printf("empty line detected, skipping.\n");
			++lineNum;
			continue;
		}

		//line starting with comment
		if(line[0] == '/'){
			if(logLevel >= 2)
				printf("line starting with comment detected, skipping.\n");
			++lineNum;
			continue;
		}

		//"remove" comments
		if(line != 0){
			unsigned char *commentPos = strchr(line, '/');
			if(commentPos != 0){
				*commentPos = '\0';
			}
		}


		//jump position
		if(line[0] == ':'){
			//remove '\n'
			char *nPos = strchr(line, '\n');
			if(nPos != 0)
				*nPos = '\0';
			//copy jump name
			strcpy(jumpToLocs[jumpLocsIndex], line);
			//copy addr
			jumpToLocs[jumpLocsIndex+1][0] = (unsigned char) ((outputOffset&0xFF00)>>8);
			jumpToLocs[jumpLocsIndex+1][1] = (unsigned char) (outputOffset&0x00FF);
			if(logLevel >= 2){
				printf("jump addr: %u\n", outputOffset);
				printf("written jumpAddr: %u %u\n", jumpToLocs[jumpLocsIndex+1][0],
					jumpToLocs[jumpLocsIndex+1][1]);
				printf("written jName: %s\n", jumpToLocs[jumpLocsIndex]);
			}

			++numJumpToLocs;
			jumpLocsIndex += 2;
			++lineNum;
			continue;
		}


		++lineNum;

		int ret = assembleLine(line, output, &outputPtr, lineNum, logLevel);
		if(writeToFile && ret != 0)
			writeToFile = false;


	}//end main asm loop


	//insert jump adresses
	insertJumpAddresses(output, logLevel);


	//write to file
	if(writeToFile){
		int bytesWritten = fwrite(output, 1, _64k, outputFile);
		if(logLevel >= 2)
			printf("bytes written to outputfile: %d\n", bytesWritten);
		if(bytesWritten <= 0){
			printf("\n\n");
			printf("Couldn't write output file.\n");
			return -1;
		}

	}


	free(output);


	return returnValue;
}










