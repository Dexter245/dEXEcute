/*
 * emulator.c
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include <stdio.h>
#include <stdlib.h>
#include "emulator.h"
#include "global.h"
#include "emuUtils.h"

const int NUM_REGISTERS = 16;

unsigned char opcode_numArgs[] = {
		3,//0
		3,
		3,
		3,
		3,
		3,//5
		3,
		3,
		3,
		2,
		3,//10
		2,
		2,
		2,
		2,
		3,//15
		0
};

unsigned short **regPtrs;
unsigned char *rom;
unsigned char *ram;

bool emuRunning = false;
bool continExec = true;
int execSpeed = 1000;//1Hz
bool maxExecSpeed = false;
int instructionsExecuted = 0;

int initEmulator(char dexeFilename[]){
	logStringPtr += sprintf(logStringPtr,
			"Initializing Emulator.\n");
	resetRegisters();
	resetRam();
	resetRom();
	int res = loadDexeToRom(dexeFilename);
	if(res != 0)
		return res;
	emuRunning = true;

	return 0;
}

int exeNextInstruction(){

	logStringPtr += sprintf(logString, "%sexeNextInstruction\n", logString);
	fetchOp();
	decodeOp();
	//execute();



	instructionsExecuted++;

	return 404;
}

int shutdownEmulator(){
	logStringPtr += sprintf(logStringPtr,
			"Shutting down emulator.\n");
	if(rom != 0)
		free(rom);
	rom = 0;
	if(ram != 0)
		free(ram);
	ram = 0;
	if(regPtrs != 0)
		free(regPtrs);
	regPtrs = 0;
	return 0;
}








