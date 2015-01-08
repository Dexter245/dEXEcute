/*
 * main.c
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "tests.h"

//command line arguments
const char CMD_ARG_LOGLEVEL[] = "-l";
const char CMD_ARG_LINE_TESTS[] = "-lt";
const char CMD_ARG_FILE_TESTS[] = "-ft";

int main(int argc, char *argv[]){
	int returnValue = 0;

	bool runLineTests = true;
	bool runFileTests = true;
	int logLevel = 0;

	//cmd line arguments
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], CMD_ARG_LOGLEVEL) == 0 && argc > i+1){
			logLevel = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], CMD_ARG_LINE_TESTS) == 0 && argc > i+1){
			runLineTests = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], CMD_ARG_FILE_TESTS)== 0 && argc > i+1){
			runFileTests = atoi(argv[i+1]);
		}
	}

	returnValue = runTests(runLineTests, runFileTests, logLevel);











	return returnValue;
}




