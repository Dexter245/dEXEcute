/*
 * utils.c
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "assembler.h"

int getRegisterNum(char *regName){
	for(int i = 0; i < NUM_REGISTERS; i++){
		if(strcmp(registers[i], regName) == 0)
			return i;
	}

	return -1;
}

int getOpcodeNum(char *opName){
	for(int i = 0; i < NUM_OPCODES; i++){
		if(strcmp(opcodes[i], opName) == 0)
			return i;
	}

	return -1;
}

void printLiteralError(int line){
	printf("\n\n");
	printf("ERROR in line %d\n", line);
	printf("error regarding literals\n");
	printf("\n\n");
}

void printUnknownRegisterError(int line, char *_register){
	printf("\n\n");
	printf("ERROR in line %d\n", line);
	printf("Unknown register\"%s\"\n", _register);
	printf("\n\n");
}

void printUnknownInstructionError(int line, char *instruction){
	printf("\n\n");
	printf("ERROR in line %d\n", line);
	printf("Unknown instruction \"%s\"\n", instruction);
	printf("\n\n");
}

void printNumArgsError(int line, int expected, int found){
	printf("\n\n");
	printf("ERROR in line %d\n", line);
	printf("Wrong number of arguments. Expected: %d, found: %d\n",
			expected, found);
	printf("\n\n");
}

bool hasArgNumError(int numArgsNeeded,
		char *arg0, char *arg1, char *arg2){
	int numArgs = getNumArgs(_args_);
	if(numArgs >= numArgsNeeded)
		return false;
	else
		return true;
}

int getNumArgs(char *arg0, char *arg1, char *arg2){
	int numArgs = 0;
	if(arg0 != 0)
		++numArgs;
	if(arg1 != 0)
		++numArgs;
	if(arg2 != 0)
		++numArgs;
	return numArgs;
}

bool isArgLit(char *arg){
	if(arg == 0)
		return false;
	else if(arg[0] == 'r')
		return false;
	else if(arg[0] == 's' && arg[1] == 'r')
		return false;
	else if(arg[0] == 'i' && arg[1] == 'p')
		return false;
	else
		return true;
}

bool isArgJumpLit(char *arg){
	if(arg[0] == ':')
		return true;
	else
		return false;
}

bool hasArgLitError(bool arg0Lit, bool arg1Lit, bool arg2Lit,
		char *arg0, char *arg1, char *arg2){
	if(isArgLit(arg0) && !arg0Lit)
		return true;
	if(isArgLit(arg1) && !arg1Lit)
		return true;
	if(isArgLit(arg2) && !arg2Lit)
		return true;
	return false;
}

bool doesJumpToLocExist(char *jName){
	int pos = 1;
	for(int i = 0; i < numJumpToLocs; i++){
		if(strcmp(jName, (char *) jumpToLocs[pos]) == 0)
			return true;
		pos += 2;
	}
	return false;
}















