/*
 * assembler.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include <string>
#include <vector>
#include <map>

class Assembler{

    public:

        Assembler(int logLevel);
        bool assembleLine(std::string line,
               std::vector<unsigned char> &output);
        bool assembleFile(const std::string &inFilename,
                const std::string &outFilename);



    private:

        //locations in code where jumping to is possible
        std::map<std::string, unsigned short> jumpToLocs;
        //locations in code where the destination addr of
        //the jump needs to be inserted
        std::map<std::string, std::vector<unsigned short> > jumpAddrInsLocs;
        int bytesWritten;
        int logLevel;
        int lineNum;

        struct Args{
            std::string arg0;
            std::string arg1;
            std::string arg2;
        } args_;

        bool insertJumpAddresses(std::vector<unsigned char> &output);
        void addJumpAddrInsLoc(std::string &jName, unsigned short addr);

        int getRegisterNum(const std::string &regName);
        int getOpcodeNum(const std::string &opName);
        bool hasArgNumError(int numArgsNeeded, Args &args);
        int getNumArgs(Args &args);
        bool isArgLit(const std::string &arg);
        bool isArgJumpLit(const std::string &arg);
        bool hasArgLitError(const bool argsLit[3], Args &args);
        bool doesJumpToLocExist(const std::string jName);


        void printErrorHeader();
        void printLiteralError();
        void printUnknownRegisterError(std::string &_register);
        void printUnknownInstructionError(std::string &instruction);
        void printNumArgsError(int expected, int found);

};

#endif
