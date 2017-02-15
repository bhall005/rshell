#ifndef __INPUT_H__
#define __INPUT_H__

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

using namespace std;

class Input {
public:
	string data;
private:
	Input(string data) : data(data) {}
	virtual void execute() = 0;

};

#endif
