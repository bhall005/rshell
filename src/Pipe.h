#ifndef __PIPE_H__
#define __PIPE_H__

#include "Command.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

class Pipe : public Command {
private:
	string rightCmd; //stores the command/file on the right side of the redirection symbol
	string leftCmd;//stores the file/input on the left side of the redirection symbol
	bool passBool;
public:
	Pipe(string str, string rightC) : Command(str), rightCmd(rightC) {}
	bool isParen() { return false; }
	void setLeft(string left) { leftCmd = left; } //used to make parsing easier

	bool execute() {
		if (str == "|")
			passBool = this->pipeCmd();
		else if (str == ">")
			passBool = this->owRedirect();
		else if (str == ">>")
			passBool = this->catRedirect();
		else if (str == "<")
			passBool = this->inputRedirect();
	}

	bool pipeCmd() { 
		//FIXME
	}

	bool owRedirect() {
		//FIXME
	}

	bool catRedirect() {
		//FIXME
	}

	bool inputRedirect() {
		//FIXME
	}
};

#endif