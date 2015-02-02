/*
 * dconst.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef DCONST_H_
#define DCONST_H_

#include <string>
#include <vector>

namespace dconst{

    extern const int _64k;

    extern const int ERROR_NO_INPUTFILE;
    extern const int ERROR_EMPTY_INPUTFILE;
    extern const int ERROR_UNKNOWN_INSTRUCTION;

    extern const std::string DEFAULT_DEXE_FILENAME;

    extern const std::vector<unsigned char> DEXE_HEADER;
    extern const int DEXE_HEADER_SIZE;

    extern const int NUM_OPCODES;
    extern const int NUM_REGISTERS;

    extern const std::vector<std::string> opcodes;
    extern const std::vector<std::string> registers;
    extern const int opcode_numArgs[];
    extern const bool opcode_argsLit[][3];


}

#endif

