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
protected:
	string data;
public:
	Input(string d) : data(d) {}
	string getData() {return data;}

};

#endif
