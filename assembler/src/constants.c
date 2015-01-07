/*
 * constants.c
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

const int _64k = 65536;

const int ERROR_NO_INPUTFILE = -1;
const int ERROR_EMPTY_INPUTFILE = -2;
const int ERROR_UNKNOWN_INSTRUCTION = -3;

char DEFAULT_OUTPUT_FILENAME[] = "binary.dexe";

const int NUM_OPCODES = 17;
const int NUM_REGISTERS = 16;

const unsigned char DEXE_HEADER[12] =
	{0, 1, 0,//dexe version
	0, 0, 0, 0, 0, 0, 0, 0, 0 };//currently unused
const int DEXE_HEADER_SIZE = 12;

char *opcodes[] = {
		"add",//0
		"sub",
		"mult",
		"div",
		"mod",
		"and",//5
		"or",
		"xor",
		"nand",
		"not",
		"cmp",//10
		"mr",
		"mw",
		"mov",
		"put",
		"jmp",//15
		"hlt"
};

char *registers[] = {
		"r0",//0
		"r1",
		"r2",
		"r3",
		"r4",
		"r5",//5
		"r6",
		"r7",
		"l0",		//literal register 0
		"l1",		//literal register 1
		"sr",//10	//status register
		"ip",		//instruction pointer
		"",
		"",
		"",
		""//15
};

int opcode_numArgs[] = {
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

int opcode_argsLit[][3] = {
		{1, 1, 0},//0
		{1, 1, 0},
		{1, 1, 0},
		{1, 1, 0},
		{1, 1, 0},
		{1, 1, 0},//5
		{1, 1, 0},
		{1, 1, 0},
		{1, 1, 0},
		{1, 0, 0},
		{1, 1, 0},//10
		{1, 0, 0},
		{1, 0, 0},
		{0, 0, 0},
		{1, 0, 0},
		{1, 0, 0},//15
		{0, 0, 0}
};
