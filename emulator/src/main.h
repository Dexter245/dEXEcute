/*
 * main.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>

//command line arguments
extern const char CMD_ARG_CONTINUOUS_EXECUTION[];
extern const char CMD_ARG_EXEC_FREQ[];//in mHz, 1/1000 Hz
extern const char CMD_ARG_MAX_EXEC_SPEED[];

extern const char DEFAULT_DEXE_FILENAME[];
extern const int MILLI_TO_NANO;


int mainLoop();

#endif /* MAIN_H_ */
