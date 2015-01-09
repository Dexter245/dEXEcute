Readme of the assembler for the dEXEcute system v0.1.0
======================================================

As the name suggests this command-line application converts dasm source code into machine code that can be executed by the cpu of the dEXEcute system. It is compliant with the ISA v0.1.0, which is the first ISA version of the cpu. Official filename extensions are '.dasm' for source code files and '.dexe' for the executable files, but this is not necessary.

Usage
=====

Compile sourcecode file with the name "inputFile.dasm":

./assembler inputFile.dasm
This will write the binary to disk with the default filename "binary.dexe"

Compile sourcecode file with the name "inputFile.dasm" and save binary as "outputBinary.dexe":

./assembler inputFile.dasm outputBinary.dexe
Pretty straightforward, filename extensions aren't necessary, only thing to watch out for is to write the name of the inputfile first.

Parameters
==========

-l [int]: sets the logLevel, that is how much data is printed to the console abou the assembly process.

Example Usage: ./assembler in out -l 1 

LogLevels:
0: dont show anything, not even errors
1: show error related messages, nothing is everything is fine
2: shows lots of stuff you dont need for normal usage, used for debugging the assembler
3: shows even more stuff for debugging

default logLevel is 1, so you probably never have to use this as it's mainly intended to debug the assembler.
