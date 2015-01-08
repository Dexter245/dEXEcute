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
#include "assembler.h"

int main(int argc, char *argv[]) {

	int returnValue = 0;
	char *inputFilename;
	char *outputFilename;

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
