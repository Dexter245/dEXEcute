/*
 * tests.c
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

#include "constants.h"
#include "tests.h"
#include "assembler.h"

void runTests(bool lineTests, bool fileTests, int logLevel){

	if(lineTests){
		runLineTests(logLevel);
	}
	if(fileTests){
		runFileTests(logLevel);
	}

}

void runLineTests(int logLevel){

	int numLineTests = 26;
	int numLineTestsPassed = 0;
	int numLineTestsFailed = 0;

	unsigned char lineTests[32*2][64] = {
		"add r0 r0 r0/\n", 		{0, 0, 0, 0, 0, 0},//0
		"add r1 r1 r1//\n", 	{0, 1, 1, 1, 0, 0},
		"add r2 r2 r2//a\n",	{0, 2, 2, 2, 0, 0},
		"add r0 r1 r2\n", 		{0, 0, 1, 2, 0, 0},
		"add r2 r1 r0\n", 		{0, 2, 1, 0, 0, 0},
		"add r0 r0 r2\n", 		{0, 0, 0, 2, 0, 0},//5
		"sub r1 r1 r1\n", 		{4, 1, 1, 1, 0, 0},
		"mult r0 r1 r2\n", 		{2*4, 0, 1, 2, 0, 0},
		"div r0 r1 r2\n", 		{3*4, 0, 1, 2, 0, 0},
		"mod r0 r1 r2\n", 		{4*4, 0, 1, 2, 0, 0},
		"and r0 r1 r2\n", 		{5*4, 0, 1, 2, 0, 0},//10
		"or r0 r1 r2\n", 		{6*4, 0, 1, 2, 0, 0},
		"xor r0 r1 r2\n", 		{7*4, 0, 1, 2, 0, 0},
		"nand r0 r1 r1\n", 		{8*4, 0, 1, 1, 0, 0},
		"not r0 r1\n", 			{9*4, 0, 1, 0, 0, 0},
		"cmp r0 r1 r2\n", 		{10*4, 0, 1, 2, 0, 0},//15
		"mr r0 r1\n", 			{11*4, 0, 1, 0, 0, 0},
		"mw r0 r1\n", 			{12*4, 0, 1, 0, 0, 0},
		"mov r0 r1\n", 			{13*4, 0, 1, 0, 0, 0},
		"put 173 r7\n", 		{14*4+2, 0, 173, 7, 0, 0},
		"put 255 r7\n",			{14*4+2, 0, 255, 7, 0, 0},//20
		"put 256 r7\n", 		{14*4+2, 1, 0, 7, 0, 0},
		"put 65535 r7\n",		{14*4+2, 255, 255, 7, 0, 0},
		"put 65536 r7\n",		{14*4+2, 0, 0, 7, 0, 0},
		"jmp 17 r3 r6\n", 		{15*4+2, 0, 17, 3, 6, 0 },
		"hlt\n", 				{16*4, 0, 0, 0, 0, 0}//25
	};

	unsigned char *input = malloc(64);
	unsigned char *output = malloc(6);
	int outputLen = 6;
	unsigned char *outputPtr = output;

	int j = 0;
	for(int testNum = 0; testNum < numLineTests; ++testNum){

		strcpy(input, lineTests[j]);
		outputPtr = output;
		assembleLine(input, output, &outputPtr, 0, logLevel);

		bool testPassed = true;
		for(int i = 0; i < outputLen; i++){
			if((unsigned char) (output[i]) != lineTests[j+1][i])
				testPassed = false;
		}
		if(testPassed){
			++numLineTestsPassed;
		}
		else{
			++numLineTestsFailed;
		}

		if(logLevel >= 1){

			if(logLevel >= 2 || !testPassed){

				printf("\ntestNum: %d\n", testNum);
				printf("input: %s", lineTests[j]);

				printf("output: \t\t");
				for(int i = 0; i < outputLen; i++){
					printf("%u ", (unsigned char) output[i]);
				}
				printf("\n");
				printf("expected output: \t");
				for(int i = 0; i < outputLen; i++){
					printf("%u ", lineTests[j+1][i]);
				}
				printf("\n");

				if(testPassed){
					printf("test %d successful!\n", testNum);
				}
				else{
					printf("test %d was NOT successful!\n", testNum);
				}

			}

		}

		//re-initialize array as if this test didnt happen for the next test
		for(int i = 0; i < outputLen; i++){
			output[i] = 0;
		}

		j += 2;




	}

	printf("\n\n");
	printf("num lineTests: %d\n", numLineTests);
	printf("num lineTests passed: %d\n", numLineTestsPassed);
	printf("num lineTests failed: %d\n", numLineTestsFailed);


	free(input);
	free(output);

}

int cmpOutFiles(char *filenameExpected, char *filenameWritten,
		int testNum, int logLevel){

	int returnValue = 0;
	FILE *fexp = fopen(filenameExpected, "r");
	FILE *fwrit = fopen(filenameWritten, "r");
	char f1c;
	char f2c;
	int pos = 0;

	while(!feof(fexp) && !feof(fwrit)){
		f1c = getc(fexp);
		f2c = getc(fwrit);
		if(pos < DEXE_HEADER_SIZE){//skip checking dexe header
			++pos;
			continue;
		}
		if(f1c != f2c){
			returnValue = -1;
			if(logLevel >= 1){
				printf("\ncmp_ERROR in test %d:\n", testNum);
				printf("At pos %d, expected:%X, written:%X\n\n",
						pos, f1c, f2c);
			}
			//return returnValue;
		}

		++pos;
	}

	if(logLevel >= 2)
		printf("bytes checked: %d", pos);


	return returnValue;
}

void runFileTests(int logLevel){

	printf("\nstarting fileTests.\n");

	int numFileTests = 1;
	int numFileTestsPassed = 0;
	int numFileTestsFailed = 0;
	const int arrSize = numFileTests*2;


	for(int i = 0; i < numFileTests; i++){

		char inputFilename[256];
		char outputFilename[256];

		//check if inputFile exists
		sprintf(inputFilename, "../fileTests/in%d.dasm", i);
		FILE *in = fopen(inputFilename, "r");
		if(in == 0){
			printf("File %s doesnt exist, continuing with next fileTest.\n",
					inputFilename);
			continue;
		}

		fclose(in);

		//check if outputFile exists
		sprintf(outputFilename, "../fileTests/out%d.dexe", i);
		FILE *out = fopen(outputFilename, "r");
		if(out == 0){
			printf("File %s doesnt exist, continuing with next fileTest.\n",
					outputFilename);
			continue;
		}

		fclose(out);

		//asm inputFile
		char writtenOutFilename[256];
		sprintf(writtenOutFilename, "../fileTests/out%d_written.dexe", i);
		assembleFile(inputFilename, writtenOutFilename, logLevel);

		//cmp outFiles
		int ret = cmpOutFiles(outputFilename, writtenOutFilename,
				i, logLevel);
		if(ret == 0)
			numFileTestsPassed++;
		else
			numFileTestsFailed++;


	}

	printf("\nNum fileTests: %d\n", numFileTests);
	printf("Num fileTests passed: %d\n", numFileTestsPassed);
	printf("Num fileTests failed: %d\n", numFileTestsFailed);
	printf("\n");








}


