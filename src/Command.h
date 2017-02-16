#ifndef COMMAND_H
#define COMMAND_H

#include "Input.h"

class Command : public Input {
public:
	Command(string data) : Input(data) {}
	/*RESET TO VITRUAL WHEN EXECUTABLES & EXITS HAVE BEEN DELINIATED*/
	bool execute() { 
		return true; 
	}
};

#endif
