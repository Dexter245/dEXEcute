CC=g++
NPD=--no-print-directory
CFLAGS_DEBUG=-std=c++11 -g3 -Wall -Werror -pedantic -pedantic-errors
CFLAGS_RELEASE=-std=c++11 -O3 -Wall -Werror -pedantic -pedantic-errors
CFLAGS_TEST=-std=c++11 -g3 -Wall -Werror -pedantic -pedantic-errors

LDFLAGS=
LDFLAGS_TEST=

SOURCES=src/main.cpp src/assembler.cpp src/dconst.cpp
SOURCES_TEST=src/test/main_test.cpp src/test/assemblerTester.cpp src/assembler.cpp src/dconst.cpp

EXE_DEBUG=assemblerdebug
EXE_RELEASE=assembler
EXE_TEST=assemblertest

#all: debug release test test
all: debug 
	
debug: $(SOURCES)
	$(CC) $(CFLAGS_DEBUG) $(LDFLAGS) $(SOURCES) -o $(EXE_DEBUG)

release: $(SOURCES)
	$(CC) $(CFLAGS_RELEASE) $(LDFLAGS) $(SOURCES) -o $(EXE_RELEASE)

test: $(SOURCES_TEST)
	$(CC) $(CFLAGS_TEST) $(LDFLAGS_TEST) $(SOURCES_TEST) -o $(EXE_TEST)

run_debug: $(EXE_DEBUG)
	./$(EXE_DEBUG) fileTests/in1.dasm b -l 3

run_debug2: $(EXE_DEBUG)
	ddd $(EXE_DEBUG) fileTests/in1.dasm 

run_release: $(EXE_RELEASE)
	./$(EXE_RELEASE) fileTests/in1.dasm b -l 3

run_test: $(EXE_TEST)
	./$(EXE_TEST) -lt 0 -ft 1 -l 3

run_test2: $(EXE_TEST)
	ddd $(EXE_TEST) 

clean:
	rm -rf $(EXE_DEBUG) $(EXE_RELEASE) $(EXE_TEST)

