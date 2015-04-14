/*
 * emulator.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <stdbool.h>

extern const int NUM_REGISTERS;

struct registers{
	unsigned short r0;
	unsigned short r1;
	unsigned short r2;
	unsigned short r3;
	unsigned short r4;
	unsigned short r5;
	unsigned short r6;
	unsigned short r7;
	unsigned short l0;//internal
	unsigned short l1;//internal
	unsigned short sr;//internal
	unsigned short ip;
	unsigned short ir;//internal
	unsigned short rp0;//internal
	unsigned short rp1;//internal
	unsigned short unused4;
} reg;

extern unsigned char opcode_numArgs[];

extern unsigned short **regPtrs;


extern unsigned char *rom;
extern unsigned char *ram;

extern bool emuRunning;
extern bool continExec;
extern int execSpeed;
extern bool maxExecSpeed;
extern int instructionsExecuted;

int initEmulator(char dexeFilename[]);
int exeNextInstruction();
int shutdownEmulator();

#endif /* EMULATOR_H_ */
