/*
 * emuUtils.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef EMUUTILS_H_
#define EMUUTILS_H_

extern int _64k;

extern void resetRegisters();
extern void resetRam();
extern void resetRom();
extern int loadDexeToRom(char dexeFilename[]);
extern void setRegPtrs();
extern unsigned char getRegNumber(unsigned short reg_);

extern void fetchOp();
extern void decodeOp();
extern void execute();

//reads next 1 or 2 bytes at rom address in ip
//and increases ip
extern unsigned char readNextChar();
extern unsigned short readNextShort();

extern void romReadByte(unsigned short addr,
		unsigned short *reg_);
extern void ramReadByte(unsigned short addr,
		unsigned short *reg_);
extern void ramWriteByte(unsigned short addr,
		unsigned short *reg_);



#endif /* EMUUTILS_H_ */
