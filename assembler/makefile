CC=g++
NPD=--no-print-directory
CFLAGS_DEBUG=-std=c++11 -c -g3 -Wall -Werror -pedantic -pedantic-errors
CFLAGS_RELEASE=-std=c++11 -c -O3 -Wall -Werror -pedantic -pedantic-errors
#CFLAGS_TEST=-std=c++11 -g3 -Wall -Werror -pedantic -pedantic-errors

LDFLAGS=
LDFLAGS_TEST=

SOURCES=src/main.cpp src/assembler.cpp src/dconst.cpp
SOURCES_TEST=src/test/main_test.cpp src/test/assemblerTester.cpp src/assembler.cpp src/dconst.cpp

EXE_DEBUG=assemblerdebug
EXE_RELEASE=assembler
EXE_TEST=assemblertest

#all: debug release test test
all: debug test release

debug: $(EXE_DEBUG)

test: $(EXE_TEST)

release: $(EXE_RELEASE)

clean: FORCE
	rm -rf obj/debug/*.o obj/release/*.o $(EXE_DEBUG) $(EXE_TEST) $(EXE_RELEASE)


$(EXE_DEBUG): obj/debug/main.o obj/debug/assembler.o obj/debug/dconst.o
	$(CC) $(LDFLAGS) $^ -o $(EXE_DEBUG)

obj/debug/main.o: src/main.cpp src/main.h
	$(CC) $(CFLAGS_DEBUG) src/main.cpp -o $@

obj/debug/assembler.o: src/assembler.cpp src/assembler.h
	$(CC) $(CFLAGS_DEBUG) src/assembler.cpp -o $@

obj/debug/dconst.o: src/dconst.cpp src/dconst.h
	$(CC) $(CFLAGS_DEBUG) src/dconst.cpp -o $@


$(EXE_TEST): obj/debug/main_test.o obj/debug/assemblerTester.o obj/debug/assembler.o obj/debug/dconst.o
	$(CC) $(LDFLAGS_TEST) $^ -o $(EXE_TEST)

obj/debug/main_test.o: src/test/main_test.cpp src/test/main_test.h
	$(CC) $(CFLAGS_DEBUG) src/test/main_test.cpp -o $@

obj/debug/assemblerTester.o: src/test/assemblerTester.cpp src/test/assemblerTester.h
	$(CC) $(CFLAGS_DEBUG) src/test/assemblerTester.cpp -o $@


$(EXE_RELEASE): obj/release/main.o obj/release/assembler.o obj/release/dconst.o
	$(CC) $(LDFLAGS) $^ -o $(EXE_RELEASE)

obj/release/main.o: src/main.cpp src/main.h
	$(CC) $(CFLAGS_RELEASE) src/main.cpp -o $@

obj/release/assembler.o: src/assembler.cpp src/assembler.h
	$(CC) $(CFLAGS_RELEASE) src/assembler.cpp -o $@

obj/release/dconst.o: src/dconst.cpp src/dconst.h
	$(CC) $(CFLAGS_RELEASE) src/dconst.cpp -o $@

FORCE:

run_debug: $(EXE_DEBUG)
	./$(EXE_DEBUG) fileTests/in1.dasm b 

run_debug2: $(EXE_DEBUG)
	ddd $(EXE_DEBUG) fileTests/in1.dasm 

run_release: $(EXE_RELEASE)
	./$(EXE_RELEASE) fileTests/in1.dasm b 

run_test: $(EXE_TEST)
	./$(EXE_TEST) -lt 0 -ft 1 -l 2

run_test2: $(EXE_TEST)
	ddd $(EXE_TEST) 
