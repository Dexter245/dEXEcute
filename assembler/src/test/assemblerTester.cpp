/*
 * assemblerTester.cpp
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include "assemblerTester.h"
#include <fstream>
#include <sstream>
#include <iostream>

AssemblerTester::AssemblerTester(int logLevel)
    :
    assembler(Assembler(logLevel))
{
    this->logLevel = logLevel;
    numLineTestsPassed = 0;
    numLineTestsFailed = 0;
    numFileTestsPassed = 0;
    numFileTestsFailed = 0;



    addLineTest("add r0 r0 r0/\n", 		{0, 0, 0, 0, 0, 0});//0
    addLineTest("add r1 r1 r1//\n", 	{0, 1, 1, 1, 0, 0});
    addLineTest("add r2 r2 r2//a\n",	{0, 2, 2, 2, 0, 0});
    addLineTest("add r0 r1 r2\n", 		{0, 0, 1, 2, 0, 0});
    addLineTest("add r2 r1 r0\n", 		{0, 2, 1, 0, 0, 0});
    addLineTest("add r0 r0 r2\n", 		{0, 0, 0, 2, 0, 0});//5
    addLineTest("sub r1 r1 r1\n", 		{4, 1, 1, 1, 0, 0});
    addLineTest("mult r0 r1 r2\n", 		{2*4, 0, 1, 2, 0, 0});
    addLineTest("div r0 r1 r2\n", 		{3*4, 0, 1, 2, 0, 0});
    addLineTest("mod r0 r1 r2\n", 		{4*4, 0, 1, 2, 0, 0});
    addLineTest("and r0 r1 r2\n", 		{5*4, 0, 1, 2, 0, 0});//10
    addLineTest("or r0 r1 r2\n", 		{6*4, 0, 1, 2, 0, 0});
    addLineTest("xor r0 r1 r2\n", 		{7*4, 0, 1, 2, 0, 0});
    addLineTest("nand r0 r1 r1\n", 		{8*4, 0, 1, 1, 0, 0});
    addLineTest("not r0 r1\n", 			{9*4, 0, 1, 0, 0, 0});
    addLineTest("cmp r0 r1 r2\n", 		{10*4, 0, 1, 2, 0, 0});//15
    addLineTest("mr r0 r1\n", 			{11*4, 0, 1, 0, 0, 0});
    addLineTest("mw r0 r1\n", 			{12*4, 0, 1, 0, 0, 0});
    addLineTest("mov r0 r1\n", 			{13*4, 0, 1, 0, 0, 0});
    addLineTest("put 173 r7\n", 		{14*4+2, 0, 173, 7, 0, 0});
    addLineTest("put 255 r7\n",			{14*4+2, 0, 255, 7, 0, 0});//20
    addLineTest("put 256 r7\n", 		{14*4+2, 1, 0, 7, 0, 0});
    addLineTest("put 65535 r7\n",		{14*4+2, 255, 255, 7, 0, 0});
    addLineTest("put 65536 r7\n",		{14*4+2, 0, 0, 7, 0, 0});
    addLineTest("jmp 17 r3 r6\n", 		{15*4+2, 0, 17, 3, 6, 0 });
    addLineTest("hlt\n", 				{16*4, 0, 0, 0, 0, 0});//25


}

void AssemblerTester::addLineTest(std::string input,
        std::array<unsigned char, 6> output){

    lineTestsInput.push_back(input);
    std::vector<unsigned char> newVec;
    for(auto a : output)
        newVec.push_back(a);
    lineTestsExpectedOutput.push_back(newVec);

}

bool AssemblerTester::isLineTestCorrect(std::vector<unsigned char> &expected,
        std::vector<unsigned char> &written){

    bool hasError = false;
    int pos = 0;
    auto expectedIt = expected.begin();
    auto writtenIt = written.begin();
    while(expectedIt != expected.end() && writtenIt != written.end()){
        if(*writtenIt != *expectedIt){
            hasError = true;
            if(logLevel >= 1){
                std::cout << "Error at byte " << pos << ": " << std::endl;
                std::cout << "Expected: " << (int) *expectedIt << ", found: " <<
                    (int) *writtenIt << std::endl;
            }
        }
        ++pos;
        ++expectedIt;
        ++writtenIt;
    }

    return !hasError;
}

bool AssemblerTester::isFileTestCorrect(std::string &expectedOutputFilename,
        std::string &writtenOutputFilename){

    std::ifstream e_ifs(expectedOutputFilename);
    std::ifstream w_ifs(writtenOutputFilename);
    int pos = 0;
    bool correct = true;

    while(e_ifs.good()){
        unsigned int e = static_cast<unsigned int>(e_ifs.get());
        unsigned int w = static_cast<unsigned int>(w_ifs.get());
        //std::cout << "Expected: " << e << ", found: " << w << std::endl;
        if(e != w){
            correct = false;
            std::cout << "Error at pos " << pos << ". " <<
                "Expected: " << e << ", found: " << w << std::endl;
        }
        pos++;
    }

    return correct;
}

void AssemblerTester::runLineTests(){

    int testNum = 0;
    for(auto it = lineTestsInput.begin(); it != lineTestsInput.end(); ++it){
        lineTestsWrittenOutput.push_back(std::vector<unsigned char>());
    }
    auto itOut = lineTestsWrittenOutput.begin();
    auto itOutExpected = lineTestsExpectedOutput.begin();
    auto itIn = lineTestsInput.begin();
    for(; itIn != lineTestsInput.end();){

        assembler.assembleLine(*itIn, *itOut);

        if(!isLineTestCorrect(*itOutExpected, *itOut)){
            numLineTestsFailed++;
            if(logLevel >= 1){
                std::cout << "Line test #" << testNum << " FAILED." <<
                    std::endl << std::endl;
            }
        }
        else{
            numLineTestsPassed++;
            if(logLevel >= 2){
                std::cout << "Line test #" << testNum << " successful." <<
                    std::endl << std::endl;
            }
        }

        ++itOut;
        ++itOutExpected;
        ++itIn;
        ++testNum;

    }

    std::cout << std::endl << std::endl;
    std::cout << "Num LineTests: " << testNum << std::endl;
    std::cout << "Successful: " << numLineTestsPassed << std::endl;
    std::cout << "Failed: " << numLineTestsFailed << std::endl;
    std::cout << std::endl << std::endl;

}

void AssemblerTester::runFileTests(){

    std::string inputFilename;
    std::string expectedOutputFilename;
    std::string writtenOutputFilename;
    std::ostringstream oss;

    for(int testNum = 0; testNum < NUM_FILE_TESTS; testNum++){

        //construct filenames
        inputFilename.erase();
        expectedOutputFilename.erase();
        writtenOutputFilename.erase();

        oss << "fileTests/in" << testNum << ".dasm";
        inputFilename = oss.str();
        oss.str("");

        oss << "fileTests/out" << testNum << ".dexe";
        expectedOutputFilename = oss.str();
        oss.str("");

        oss << "fileTests/out" << testNum << "_written.dexe";
        writtenOutputFilename = oss.str();
        oss.str("");

        if(logLevel >= 2){
            std::cout << "Assembling File #" << testNum << ": " <<
                inputFilename << std::endl;
            std::cout << "=========================================" << std::endl;
        }

        //assemble file
        assembler.assembleFile(inputFilename, writtenOutputFilename);

        //compare output files
        int res = isFileTestCorrect(expectedOutputFilename, writtenOutputFilename);

        if(res == true){
            numFileTestsPassed++;
            std::cout << "Filetest #" << testNum << " was successful." <<
                std::endl << std::endl;
        }
        else{
            numFileTestsFailed++;
            std::cout << "Filetest #" << testNum << " was NOT successful." <<
                std::endl << std::endl;
        }

    }

    std::cout << std::endl << std::endl;
    std::cout << "Num Filetests: " << NUM_FILE_TESTS << std::endl;
    std::cout << "Num Filetests passed: " << numFileTestsPassed << std::endl;
    std::cout << "Num Filetests failed: " << numFileTestsFailed << std::endl;

}



