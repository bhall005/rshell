#ifndef __EXIT_H__
#define __EXIT_H__

#include "Input.h"
#include "Command.h"
#include <stdlib.h>

class Exit : public Command {
public:
	Exit() : Command("exit") {}
	bool execute() {
		// Exit the shell
		exit(0);
		// Return false if exit() failed
		perror("There was an error trying to exit the program");
		return false;
	}
};

#endif
