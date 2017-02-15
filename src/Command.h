#ifndef COMMAND_H
#define COMMAND_H

#include "Input.h"

class Command : public Input {
public:
	Command(string data) : Input(data) {}
	virtual bool execute() = 0;
}

#endif
