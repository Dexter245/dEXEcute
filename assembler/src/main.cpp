/*
 * main.cpp
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "main.h"
#include "dconst.h"
#include "assembler.h"

const std::string CMD_ARG_LOGLEVEL("-l");

int main(int argc, char*argv[]){

    std::string inputFilename;
    std::string outputFilename;
    int logLevel = 1;

    if(argc < 2){
        std::cout << "No input file given. Nothing to assemble." << std::endl;
        return dconst::ERROR_NO_INPUTFILE;
    }
    else{
        inputFilename = std::string(argv[1]);

        if(argc == 2){
            std::cout << "No outputFilename given, defaulting to " <<
                dconst::DEFAULT_DEXE_FILENAME << std::endl;
            outputFilename = dconst::DEFAULT_DEXE_FILENAME;
        }
        else{
            outputFilename = std::string(argv[2]);
            if(argc >= 5){
                if(CMD_ARG_LOGLEVEL.compare(argv[3]) == 0){
                    logLevel = atoi(argv[4]);
                }
            }
        }

        Assembler assembler(logLevel);

        assembler.assembleFile(inputFilename, outputFilename);

    }

    return 0;
}
