/*
 * consoleInterface.c
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include <stdio.h>
#include <ncurses.h>
#include "consoleInterface.h"
#include "../global.h"
#include "../emulator.h"

void initConsoleInterface(){
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr,TRUE);
	curs_set(false);
	printw("fds");
}

void updateConsoleInterface(){

	erase();

	//check for keyPresses
	int keyPressed = getch();
	//printf("keyPressed: %d\n", keyPressed);
	//printf("keyPressed as char: %c\n", (char) keyPressed);
	if(keyPressed == 32){
		exeNextInstruction();
	}

	//general info
	printw("General Info\n");
	printw("============\n");
	printw("Running: %d\tcontinExec: %d\tmaxSpeed: %d\texecSpeed: %dmHz\t",
			emuRunning, continExec, maxExecSpeed, execSpeed);
	printw("instrExecuted: %d\n", instructionsExecuted);
	printw("\n");

	//registers
	printw("Registers\n");
	printw("=========\n");
	printw("r0: %d\tr1: %d\tr2: %d\tr3: %d\t", reg.r0, reg.r1, reg.r2, reg.r3);
	printw("r4: %d\tr5: %d\tr6: %d\tr7: %d\n", reg.r4, reg.r5, reg.r6, reg.r7);

	printw("r0: %X\tr1: %X\tr2: %X\tr3: %X\t", reg.r0, reg.r1, reg.r2, reg.r3);
	printw("r4: %X\tr5: %X\tr6: %X\tr7: %X\n", reg.r4, reg.r5, reg.r6, reg.r7);

	printw("\n");
	printw("l0: %d\tl1: %d\tsr: %d\tip: %d\n", reg.l0, reg.l1, reg.sr, reg.ip);
	printw("l0: %X\tl1: %X\tsr: %X\tip: %X\n", reg.l0, reg.l1, reg.sr, reg.ip);
	printw("\n");

	//first 64 bytes of ram
	printw("RAM (First 64 bytes)\n");
	printw("====================\n");
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 16; j++){
			printw("%d ", ram[i*16 + j]);
		}
		printw("\n");
	}
	printw("\n");

	//first 64 bytes of rom
	printw("ROM (64 bytes of it)\n");
	printw("====================\n");
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 16; j++){
			printw("%d ", rom[i*16 + j]);
		}
		printw("\n");
	}

	printw("\n");

	//log
	printw("Log\n");
	printw("===\n");
	printw(logString);



	refresh();

}

void shutdownConsoleInterface(){

}









