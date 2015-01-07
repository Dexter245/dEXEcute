/*
 * constants.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#ifndef _args_
#define _args_ arg0, arg1, arg2
#endif //_args_

extern const int _64k;

extern const int ERROR_NO_INPUTFILE;
extern const int ERROR_EMPTY_INPUTFILE;
extern const int ERROR_UNKNOWN_INSTRUCTION;

extern char DEFAULT_OUTPUT_FILENAME[];

extern const int NUM_OPCODES;
extern const int NUM_REGISTERS;

extern char *opcodes[];
extern char *registers[];
extern int opcode_numArgs[];
extern int opcode_argsLit[][3];

extern const unsigned char DEXE_HEADER[];
extern const int DEXE_HEADER_SIZE;





#endif /* CONSTANTS_H_ */
