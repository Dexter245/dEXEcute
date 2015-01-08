/*
 * tests.h
 * This file is part of the dEXEcute project
 *
 * Author: Lajos Ambrus
 * Published under the MIT License. See LICENSE file for more info.
 * Copyright (c) 2014-2015 Lajos Ambrus
 */

#ifndef TESTS_H_
#define TESTS_H_

int runTests(bool lineTests, bool fileTests,
		int logLevel);
void runLineTests(int logLevel);
void runFileTests(int logLevel);
int cmpOutFiles(char *filenameExpected,
		char *filenameWritten, int testNum, int logLevel);

#endif /* TESTS_H_ */
