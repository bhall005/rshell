#ifndef COMMAND_H
#define COMMAND_H

#include "Input.h"

class Command : public Input {
public:
	// Store the command as a string data in the constructor
	Command(string data) : Input(data) {}
	
	// Virtual function execute() that will be implemented in Executable.h and Exit.h
	virtual bool execute() = 0;
};

#endif
