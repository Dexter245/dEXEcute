/*
 * assemblerTester.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef ASSEMBLER_TESTER_H_
#define ASSEMBLER_TESTER_H_

#include <vector>
#include <array>
#include <string>
#include "../assembler.h"

class AssemblerTester{

    public:
        AssemblerTester(int logLevel);
        void runLineTests();
        void runFileTests();


    private:

        void addLineTest(std::string input, std::array<unsigned char, 6> output);
        bool isLineTestCorrect(std::vector<unsigned char> &expected,
                std::vector<unsigned char> &written);
        bool isFileTestCorrect(std::string &expectedOutputFilename,
                std::string &writtenOutputFilename);

        const int NUM_FILE_TESTS = 4;

        Assembler assembler;

        std::vector<std::string> lineTestsInput;
        std::vector<std::vector<unsigned char> > lineTestsExpectedOutput;
        std::vector<std::vector<unsigned char> > lineTestsWrittenOutput;
        int numLineTestsPassed;
        int numLineTestsFailed;
        int numFileTestsPassed;
        int numFileTestsFailed;
        int logLevel;











};

#endif
