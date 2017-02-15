#ifndef COMMAND_H
#define COMMAND_H

#include "Input.h"

class Command {
public:
	Command() {}
	bool failed;
private:
	virtual void execute() = 0;
	void setFail(bool failure) {
		failed = failure;
	}
}

#endif
