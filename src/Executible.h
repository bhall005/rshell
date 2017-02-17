#ifndef __EXECUTIBLE_H__
#define __EXECUTIBLE_H__

#include "Input.h"
#include "Command.h"

class Executible : public Command {
public:
	Executible(string data) : Command(data) {}
	bool execute() {
		//INSERT VANESSA CODE HERE
		return true;
	}
};

#endif