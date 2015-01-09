/*
 * utils.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>
#include "constants.h"

int getRegisterNum(char *regName);
int getOpcodeNum(char *opName);

void printLiteralError(int line);
void printUnknownRegisterError(int line, char *_register);
void printUnknownInstructionError(int line, char *instruction);
void printNumArgsError(int line, int expected, int found);

bool hasArgNumError(int numArgsNeeded,
		char *arg0, char *arg1, char *arg2);
int getNumArgs(char *arg0, char *arg1, char *arg2);
bool isArgLit(char *arg);
bool isArgJumpLit(char *arg);
bool hasArgLitError(bool arg0Lit, bool arg1Lit, bool arg2Lit,
		char *arg0, char *arg1, char *arg2);
bool doesJumpToLocExist(char *jName);


#endif /* UTILS_H_ */
