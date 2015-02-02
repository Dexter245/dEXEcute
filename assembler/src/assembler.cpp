/*
 * assembler.cpp
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#include "assembler.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "dconst.h"

Assembler::Assembler(int logLevel){

    this->logLevel = logLevel;
    lineNum = 0;
    bytesWritten = 0;

}

bool Assembler::assembleLine(std::string line,
        std::vector<unsigned char> &output){

    bool errorFound = false;
    args_.arg0 = "";
    args_.arg1 = "";
    args_.arg2 = "";

    //remove comments
    line = line.substr(0, line.find("/"));

    //everything to lowercase
    std::transform(line.begin(), line.end(), line.begin(), tolower);

    char delimiters[] = " \n";
    char *line_c = (char*) calloc(256, sizeof(char));
    strcpy(line_c, line.c_str());

    std::string word;

    //break down line to its parts
    //char *tmp = (char*) calloc(256, sizeof(char));
    char *tmp = 0;
    tmp = strtok(line_c, delimiters);
    if(tmp != 0)
        word = std::string(tmp);
    tmp = strtok(0, delimiters);
    if(tmp != 0)
        args_.arg0 = std::string(tmp);
    tmp = strtok(0, delimiters);
    if(tmp != 0)
        args_.arg1 = std::string(tmp);
    tmp = strtok(0, delimiters);
    if(tmp != 0)
        args_.arg2 = std::string(tmp);

    free(line_c);

    if(logLevel >= 3){
        std::cout << "line: " << lineNum << ", word: " << word << ", arg0: " <<
            args_.arg0 << ", arg1: " << args_.arg1 << ", arg2: " << args_.arg2 <<
            std::endl;
    }

    //check for errors in line
    int opcodeNum = getOpcodeNum(word);
    if(opcodeNum == -1){
        errorFound = true;
        if(logLevel >= 1)
            printUnknownInstructionError(word);
    }

    int numArgsNeeded = dconst::opcode_numArgs[opcodeNum];
	if(hasArgNumError(numArgsNeeded, args_ )){
        errorFound = true;
        if(logLevel >= 1)
            printNumArgsError(numArgsNeeded, getNumArgs(args_));
	}

    if(hasArgLitError(dconst::opcode_argsLit[opcodeNum], args_)){
        errorFound = true;
        if(logLevel >= 1)
            printLiteralError();
	}

	//write opcode
	unsigned char opcode = static_cast<unsigned char>(opcodeNum);
	opcode <<= 2;
	bool isArg0Lit = isArgLit(args_.arg0);
	bool isArg1Lit = isArgLit(args_.arg1);
	if(isArg0Lit)
		opcode |= 2;
	if(isArg1Lit)
		opcode |= 1;

	if(logLevel >= 3)
        std::cout << "opcodeNum: " << opcodeNum <<
            ", opcode: " << (int) opcode << std::endl;

    output.push_back(opcode);
    bytesWritten++;


	//write arg0
	if(numArgsNeeded > 0){
		//jump arg0 jumpLit
		if(opcode == 62 && isArgJumpLit(args_.arg0)){//62 = 15*4+2, jmp :bla

            unsigned short addr = bytesWritten;
			if(logLevel >= 2){
                std::cout << "argJumpLit: " << args_.arg0 << std::endl;
                std::cout << "address: " << addr << std::endl;
			}
            addJumpAddrInsLoc(args_.arg0, addr);
            output.push_back(0);
            output.push_back(0);
            bytesWritten += 2;
		}
		else if(isArg0Lit){
			unsigned short arg0short = static_cast<unsigned short>(
                    atoi(args_.arg0.c_str()));
            unsigned char byte0 = static_cast<unsigned char>(arg0short>>8);
            unsigned char byte1 = static_cast<unsigned char>(arg0short&0x00FF);
            if(logLevel >= 3){
                std::cout << "arg0Lit: " << arg0short << ", " << byte0 << " " <<
                    byte1 << std::endl;
            }
            output.push_back(byte0);
            output.push_back(byte1);
            bytesWritten += 2;

        }else{

			int rNum = getRegisterNum(args_.arg0);
			if(rNum == -1){
                errorFound = true;
				if(logLevel >= 1)
					printUnknownRegisterError(args_.arg0);
			}
            output.push_back(static_cast<unsigned char>(rNum & 0x000000FF));
            bytesWritten++;
            if(logLevel >= 3){
                std::cout << "arg0(not lit): " << rNum << ", written: " <<
                    static_cast<unsigned int>(output.back()) << std::endl;
            }
		}
	}


	//write arg1
	if(numArgsNeeded > 1){
        if(isArg1Lit){
			unsigned short arg1short = static_cast<unsigned short>(
                    atoi(args_.arg1.c_str()));
            unsigned char byte0 = static_cast<unsigned char>(arg1short>>8);
            unsigned char byte1 = static_cast<unsigned char>(arg1short&0x00FF);
            if(logLevel >= 3){
                std::cout << "arg1Lit: " << arg1short << ", " << byte0 << " " <<
                    byte1 << std::endl;
            }
            output.push_back(byte0);
            output.push_back(byte1);
            bytesWritten += 2;
		}else{
			int rNum = getRegisterNum(args_.arg1);
			if(rNum == -1){
                errorFound = true;
				if(logLevel >= 1)
					printUnknownRegisterError(args_.arg1);
			}

            output.push_back(static_cast<unsigned char>(rNum & 0x000000FF));
            bytesWritten++;
            if(logLevel >= 3){
                std::cout << "arg1(not lit): " << rNum << ", written: " <<
                    static_cast<unsigned int>(output.back()) << std::endl;
            }
		}
	}


	//write arg2
	if(numArgsNeeded > 2){
			int rNum = getRegisterNum(args_.arg2);
			if(rNum == -1){
                errorFound = true;
				if(logLevel >= 1)
					printUnknownRegisterError(args_.arg2);
			}
            output.push_back(static_cast<unsigned char>(rNum & 0x000000FF));
            bytesWritten++;
            if(logLevel >= 3){
                std::cout << "arg2(not lit): " << rNum << ", written: " <<
                    static_cast<unsigned int>(output.back()) << std::endl;
            }
	}

    return errorFound;

}

bool Assembler::assembleFile(const std::string &inFilename,
        const std::string &outFilename){

    bool errorFound = false;
    std::ifstream ifs(inFilename);
    std::ofstream ofs(outFilename, std::ios::out | std::ios::binary);

    std::vector<unsigned char> outBuf;
    char inBuf[256] = "\0";
    std::string line;
    bytesWritten = dconst::DEXE_HEADER_SIZE;
    lineNum = 0;

    while(ifs.good()){

        lineNum++;

        ifs.getline(inBuf, 256);

        if(logLevel >= 2){
            std::cout << std::endl;
        }

        //empty line
        if(inBuf[0] == '\n' || inBuf[0] == '\0'){
            if(logLevel >= 2){
                std::cout << "Empty line detected, skipping." << std::endl;
            }
            continue;
        }

        //line starting with comment
        if(inBuf[0] == '/'){
            if(logLevel >= 2){
                std::cout << "Line starting with comment detected, skipping." <<
                    std::endl;
            }
            continue;
        }

        line.assign(inBuf);

        //"remove" comments
        line = line.substr(0, line.find("/"));

        //jump position
        if(line[0] == ':'){
        //if(line.find(":") != std::string::npos){
            //remove '\n'
            line = line.substr(0, line.find('\n'));
            //check if jumpToName already exists
            if(doesJumpToLocExist(line)){
                if(logLevel >= 1){
                    std::cout << "Warning: Multiple defintions of jumpLocation: "
                        << line << " found in line: " << lineNum << std::endl;
                }
                continue;
            }
            //save jump location
            if(logLevel >= 2){
                std::cout << "Saved jump position: name: " << line <<
                    ", pos: " << bytesWritten << std::endl;
            }
            jumpToLocs.emplace(line, static_cast<unsigned char>(bytesWritten));
            //jumpToLocs.emplace(line, 65534);
            continue;
        }

        //asm line
        bool ret = assembleLine(line, outBuf);
        if(ret)
            errorFound = true;


    }

    if(errorFound){
        std::cout << "There were errors while assembling the file." << std::endl;
        return errorFound;
    }


    //insert jump addresses
    bool err = insertJumpAddresses(outBuf);
    if(err){
        std::cout << "Inserting Jump Addresses was NOT successful." << std::endl;
        return err;
    }

    //write to file
    //dexe header first
    for(auto it = dconst::DEXE_HEADER.begin(); it != dconst::DEXE_HEADER.end();
            ++it){
        ofs << *it;
    }
    int counter = 0;
    for(auto it = outBuf.begin(); it != outBuf.end(); ++it){
        ofs << *it;
        if(logLevel >= 3 && counter <= 30){
            std::cout << "pos " << counter << ": " <<
                static_cast<unsigned int>(*it) << std::endl;
            counter++;
        }
    }

    for(int i = bytesWritten; i < 65536; i++){
        ofs << (unsigned char) 0;
    }


    std::cout << "Successfully assembled file with " << lineNum << " lines and " <<
        "effectively wrote " << bytesWritten << " Bytes." << std::endl;

    //reset variables
    args_.arg0 = "";
    args_.arg1 = "";
    args_.arg2 = "";
    bytesWritten = 0;
    lineNum = 0;
    jumpToLocs.clear();
    jumpAddrInsLocs.clear();

    return 0;

}

bool Assembler::insertJumpAddresses(std::vector<unsigned char> &output){

    bool found = false;
    auto it = jumpAddrInsLocs.begin();
    for(; it != jumpAddrInsLocs.end(); ++it){//insert entries for each jName
        auto it2 = jumpToLocs.begin();
        for(; it2 != jumpToLocs.end(); ++it2){//all jumpTo positions
            if(it2->first.compare(it->first) == 0){//found needed jumpTo position
                found = true;
                auto it3 = it->second.begin();
                for(; it3 != it->second.end(); ++it3){//each codePos where jumpTo
                                                    //pos needs to be inserted
                    unsigned char byte0 =
                        static_cast<unsigned char>(it2->second >> 8);
                    unsigned char byte1 =
                        static_cast<unsigned char>(it2->second & 0x00FF);
                    int offset = dconst::DEXE_HEADER_SIZE;
                    output.at((*it3)-offset) = byte0;
                    output.at((*it3)-offset+1) = byte1;
                    if(logLevel >= 2){
                        std::cout << "jName: " << it->first << " , addr: " <<
                            it2->second << ", byte0: " << (unsigned short) byte0 <<
                            ", byte1: " << (unsigned short) byte1 << std::endl;
                        std::cout << "insAddr: " << *it3 << std::endl;
                    }
                }
            }
        }

        if(!found){
            std::cout << "ERROR: jump position '" << it->first <<
                " doesn't exist!" << std::endl;
            return true;
        }
        found = false;
    }

    return false;

}

void Assembler::addJumpAddrInsLoc(std::string &jName, unsigned short addr){
    auto it = jumpAddrInsLocs.find(jName);
    if(it != jumpAddrInsLocs.end()){//entry with jName exists
        it->second.push_back(addr);
    }
    else{
        std::vector<unsigned short> newVec;
        newVec.push_back(addr);
        jumpAddrInsLocs.emplace(jName, newVec);
    }
}

int Assembler::getRegisterNum(const std::string &regName){

    int counter = 0;
    for(auto it = dconst::registers.begin(); it != dconst::registers.end(); ++it){
        if(regName.compare(*it) == 0)
            return counter;
        counter++;
    }

    return -1;
}

int Assembler::getOpcodeNum(const std::string &opName){

    int counter = 0;
    for(auto it = dconst::opcodes.begin(); it != dconst::opcodes.end(); ++it){
        if(opName.compare(*it) == 0)
            return counter;
        counter++;
    }

    return -1;
}

bool Assembler::hasArgNumError(int numArgsNeeded, Args &args){

    int numArgsHaving = getNumArgs(args);
    if(numArgsHaving >= numArgsNeeded)
        return false;
    else
        return true;
}

int Assembler::getNumArgs(Args &args){

    int counter = 0;
    if(!args.arg0.empty())
        counter++;
    if(!args.arg1.empty())
        counter++;
    if(!args.arg2.empty())
        counter++;

    return counter;
}

bool Assembler::isArgLit(const std::string &arg){

    if(arg.empty())
        return false;
    if(arg[0] == ':')
        return true;

    for(auto it = dconst::registers.begin(); it != dconst::registers.end(); ++it){
        if(arg.compare(*it) == 0)
            return false;
    }

    for(auto it = dconst::opcodes.begin(); it != dconst::opcodes.end(); ++it){
        if(arg.compare(*it) == 0)
            return false;
    }

    return true;
}

bool Assembler::isArgJumpLit(const std::string &arg){

    if(arg.empty())
        return false;
    else if(arg[0] == ':')
        return true;
    else
        return false;
}

bool Assembler::hasArgLitError(const bool argsLit[3], Args &args){

    if(!argsLit[0] && isArgLit(args.arg0))
        return true;
    if(!argsLit[1] && isArgLit(args.arg1))
        return true;
    if(!argsLit[2] && isArgLit(args.arg2))
        return true;

    return false;
}

bool Assembler::doesJumpToLocExist(const std::string jName){

    auto it = jumpToLocs.begin();
    for(; it != jumpToLocs.end(); ++it){
        if(jName.compare(it->first) == 0)
            return true;
    }

    return false;//TODO
}

void Assembler::printErrorHeader(){
    std::cout << std::endl << "ERROR in line " << lineNum << ":" << std::endl;
}

void Assembler::printLiteralError(){
    printErrorHeader();
    std::cout << "Error regarding literals." << std::endl;
}

void Assembler::printUnknownRegisterError(std::string &_register){
    printErrorHeader();
    std::cout << "Unknown Register: " << _register << std::endl;
}

void Assembler::printUnknownInstructionError(std::string &instruction){
    printErrorHeader();
    std::cout << "Unknown Instruction: " << instruction << std::endl;
}

void Assembler::printNumArgsError(int expected, int found){
    printErrorHeader();
    std::cout << "Wrong number of arguments, expected: " << expected <<
        ", found: " << found << std::endl;
}










