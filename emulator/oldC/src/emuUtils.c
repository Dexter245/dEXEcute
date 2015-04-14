/*
 * emuUtils.c
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include <stdlib.h>
#include <stdio.h>
#include "emuUtils.h"
#include "global.h"
#include "emulator.h"

int _64k = 65536;

void resetRegisters(){
	reg.r0 = 0;
	reg.r1 = 0;
	reg.r2 = 0;
	reg.r3 = 0;
	reg.r4 = 0;
	reg.r5 = 0;
	reg.r6 = 0;
	reg.r7 = 0;
	reg.l0 = 0;
	reg.l1 = 0;
	reg.sr = 0;
	reg.ip = 0;
}

void resetRam(){
	if(ram != 0)
		free(ram);
	ram = calloc(_64k, 1);
}

void resetRom(){
	if(rom != 0)
		free(rom);
	rom = calloc(_64k, 1);
}

int loadDexeToRom(char dexeFilename[]){
	FILE *dFile = fopen(dexeFilename, "r");
	if(dFile == 0){
		logStringPtr += printf(logStringPtr,
				"ERROR: dexe file %s doesn't exist!\n",
				dexeFilename);
		return -1;
	}
	else{
		if(rom == 0){
			logStringPtr += sprintf(logStringPtr,
					"ERROR: rom is NULL!\n");
			return -1;
		}
		logStringPtr += sprintf(logStringPtr,
				"Reading dexe file %s to rom.\n", dexeFilename);

		char *buf = calloc(_64k, 1);
		fgets(buf, _64k, dFile);
		for(int i = 0; i < _64k; i++)
			rom[i] = (unsigned char) buf[i];

		fclose(dFile);
		free(buf);

		return 0;
	}
}

void setRegPtrs(){
	regPtrs = calloc(NUM_REGISTERS, sizeof(unsigned short*));
	unsigned short *ptrToFirst = &reg.r0;
	for(int i = 1; i < NUM_REGISTERS; i++){
		regPtrs[i] = ptrToFirst;
		ptrToFirst++;
	}
}

unsigned char getRegNumber(unsigned short reg_){
	int offset = (&reg_ - &(reg.r0))/ sizeof(unsigned short);
	unsigned char offsetChar = ((unsigned int) offset) & 0x0F;
	return offsetChar;
}

void fetchOp(){
	romReadByte(reg.ip, &reg.ir);//read next instruction
	reg.ip++;
	logStringPtr += sprintf(logString, "%sreg.ip: %d\n", logString, reg.ip);
}

void decodeOp(){
	//get num args for op and store in ip
	unsigned char opcodeWithoutFlags = ((reg.ip & (0xFF - 3)) >> 2) / 4;
	unsigned char numArgs = opcode_numArgs[opcodeWithoutFlags];
	unsigned short numArgs_ = (unsigned short) numArgs;
	numArgs_ = numArgs << 14;
	reg.ip = reg.ip & numArgs_;

	if( (reg.ip & 0x4000) > 0){//first operand necessary

		if( (reg.ip & 0x02) == 2){//first operand is literal
			reg.l0 = readNextShort();
			reg.rp0 = getRegNumber(reg.l0) << 8;
		}
		else{//first operand is register
			reg.rp0 = readNextChar() << 8;
		}

	}
	if( (reg.ip & 0x8000) > 0){//second operand necessary

		if( (reg.ip & 0x01) == 1){//second operand is literal
			reg.l1 = readNextShort();
			reg.rp0 = reg.rp0 | getRegNumber(reg.l1);
		}
		else{//second operand is register
			reg.rp0 = reg.rp0 | readNextChar();
		}

	}
	if( (reg.ip & 0xC000) > 0){//third operand necessary
		reg.rp1 = readNextChar() << 8;
	}

}

void execute(){

}

unsigned char readNextChar(){
	unsigned char value = rom[reg.ip];
	reg.ip++;
	return value;
}

unsigned short readNextShort(){
	unsigned short value = (rom[reg.ip] << 8) | (rom[reg.ip+1]);
	reg.ip += 2;
	return value;
}

void romReadByte(unsigned short addr, unsigned short *reg_){
	*reg_ = rom[addr];
}

void ramReadByte(unsigned short addr, unsigned short *reg_){
	*reg_ = ram[addr];
}

void ramWriteByte(unsigned short addr, unsigned short *reg_){
	ram[addr] = *reg_;
}










