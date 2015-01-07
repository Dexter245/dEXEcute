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
#include <ctype.h>
#include <stdbool.h>

#include "main.h"
#include "constants.h"
#include "utils.h"
#include "tests.h"
#include "assembler.h"

//command line arguments
const char CMD_ARG_TEST[] = "-test";
const char CMD_ARG_LOGLEVEL[] = "-l";
const char CMD_ARG_LINE_TESTS[] = "-lt";
const char CMD_ARG_FILE_TESTS[] = "-ft";

int main(int argc, char *argv[]) {

	int returnValue = 0;
	char *inputFilename;
	char *outputFilename;

	//run tests if requested
	bool runTests_ = false;
	bool runLineTests = true;
	bool runFileTests = true;
	int logLevel = 0;

	//cmd line arguments
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], CMD_ARG_TEST) == 0){
			runTests_ = true;
		}
		else if(strcmp(argv[i], CMD_ARG_LOGLEVEL) == 0 && argc > i+1){
			logLevel = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], CMD_ARG_LINE_TESTS) == 0 && argc > i+1){
			runLineTests = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], CMD_ARG_FILE_TESTS)== 0 && argc > i+1){
			runFileTests = atoi(argv[i+1]);
		}
	}

	if(runTests_){
		runTests(runLineTests, runFileTests, logLevel);
		return 0;
	}

	//no tests requested, assemble file
	if(argc < 2){
		printf("No input file given. Nothing to assemble.\n");
		return ERROR_NO_INPUTFILE;
	}
	else{
		inputFilename = argv[1];

		if(argc == 2){
			printf("No outputFilename given, defaulting to \"%s\"\n",
					DEFAULT_OUTPUT_FILENAME);
			outputFilename = DEFAULT_OUTPUT_FILENAME;
		}
		else
			outputFilename = argv[2];

		returnValue = assembleFile(inputFilename, outputFilename, 2);




	}



	return returnValue;
}
