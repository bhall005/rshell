#ifndef __EXIT_H__
#define __EXIT_H__

#include "Input.h"
#include "Command.h"

class Exit : public Command {
public:
	Exit() : Command("exit") {}
	bool execute() {
		//WRITE CODE FOR EXITING
		return false;
	}
};

#endif