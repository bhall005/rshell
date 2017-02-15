#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

#include "Input.h"

using namespace std;

class Executor {
private:
	vector<Input*> cmdVec;
	vector<Input*> cnctVec;
	char lgn[256];
	char hostName[256];


public:
	void init() {
		getlogin_r(lgn, 256);

		cout << lgn << "$ ";
	}

	string getInput() {

	}

	void parseInput(string userInput) {

	}
};











#endif