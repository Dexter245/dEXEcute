/*
 * main.c
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include "main.h"
#include "emulator.h"
#include "interface/consoleInterface.h"

const char CMD_ARG_CONTINUOUS_EXECUTION[] = "-ce";
const char CMD_ARG_EXEC_FREQ[] = "-f";
const char CMD_ARG_MAX_EXEC_SPEED[] = "-m";

const char DEFAULT_DEXE_FILENAME[] = "binary.dexe";
const int MILLI_TO_NANO = 1000000;

int mainLoop(){
	int returnValue = 0;

	//logStringPtr += sprintf(logString, "%smainLoop\n", logString);
	//refresh();
	clock_t time1 = clock();

	exeNextInstruction();
	updateConsoleInterface();

	//sleep so emuCPU clockrate is as desired
	if(!maxExecSpeed){
		clock_t time2 = clock();
		clock_t timeDiff = time2 - time1;
			float seconds = timeDiff/(float)CLOCKS_PER_SEC;
			int targetTime_ms = (1/(float) execSpeed) * 1000000;
			int remainTime_ms = targetTime_ms - seconds*1000;
			struct timespec sleepDuration;
			sleepDuration.tv_sec = remainTime_ms/1000;
			sleepDuration.tv_nsec = (remainTime_ms - sleepDuration.tv_sec*1000) *
					MILLI_TO_NANO;
			nanosleep(&sleepDuration, NULL);
	}

	return returnValue;
}

int main(int argc, char *argv[]){
	int returnValue = 0;

	char *dexeFilename;

	//cmd line args
	if(argc < 2){
		printf("No dexe file specified, defaulting to %s\n", DEFAULT_DEXE_FILENAME);
		dexeFilename = (char*) DEFAULT_DEXE_FILENAME;
	}
	else{
		dexeFilename = argv[1];
	}
	for(int i = 2; i < argc; i++){
		if(strcmp(argv[i], CMD_ARG_CONTINUOUS_EXECUTION) == 0 && argc > i+1){
			continExec = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], CMD_ARG_EXEC_FREQ) == 0 && argc > i+1){
			execSpeed = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], CMD_ARG_MAX_EXEC_SPEED) == 0){
			maxExecSpeed = true;
		}
	}

	logString = calloc(1000000, 1);
	logStringPtr = logString;
	initConsoleInterface();
	initEmulator(dexeFilename);
	updateConsoleInterface();


	while(emuRunning && returnValue == 0){
		//while(1){
		returnValue = mainLoop();
	}

	shutdownEmulator();
	shutdownConsoleInterface();
	free(logString);
	logString = 0;
	logStringPtr = 0;

	return returnValue;
}
