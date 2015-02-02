/*
 * main_test.cpp
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include "main_test.h"
#include "assemblerTester.h"
#include <cstdlib>

const std::string CMD_ARG_LOGLEVEL = "-l";
const std::string CMD_ARG_LINE_TESTS = "-lt";
const std::string CMD_ARG_FILE_TESTS = "-ft";

int main(int argc, char *argv[]){

    bool runLineTests = true;
    bool runFileTests = true;
    int logLevel = 1;

    for(int i = 0; i < argc; i++){
        std::string argString(argv[i]);
        if(argString == CMD_ARG_LOGLEVEL && argc > i+1){
            logLevel = atoi(argv[i+1]);
        }
        else if(argString == CMD_ARG_LINE_TESTS && argc > i+1){
            runLineTests = atoi(argv[i+1]);
        }
        else if(argString == CMD_ARG_FILE_TESTS && argc > i+1){
            runFileTests = atoi(argv[i+1]);
        }
    }

    AssemblerTester assemblerTester(logLevel);

    if(runLineTests){
        assemblerTester.runLineTests();
    }
    if(runFileTests){
        assemblerTester.runFileTests();
    }

    return 0;
}

