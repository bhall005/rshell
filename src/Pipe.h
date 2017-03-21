#ifndef __PIPE_H__
#define __PIPE_H__

#include "Command.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Pipe : public Command {
private:
	string rightCmd; //stores the command/file on the right side of the redirection symbol
	string leftCmd;//stores the file/input on the left side of the redirection symbol
	bool passBool; //stores the ultimate return value to be passed into the next function
public:
	Pipe(string str, string leftC) : Command(str), leftCmd(leftC) {}
	bool isParen() { return false; }
	void setRight(string rgt) { this->rightCmd = rgt; } //used to make parsing easier
	void testCmds() { cout << leftCmd << ' ' << data << ' ' << rightCmd << endl; }
	//used to test if parsing works correctly
	bool execute() {
		if (data == "|")
			passBool = this->pipeCmd();
		else if (data == ">")
			passBool = this->owRedirect();
		else if (data == ">>")
			passBool = this->catRedirect();
		else if (data == "<")
			passBool = this->inputRedirect();
		return passBool;
	}

	bool pipeCmd() { 
		//FIXME
		return false;
	}

	bool owRedirect() {
		//FIXME
		return false;
	}

	bool catRedirect() {
		//FIXME
		return false;
	}

	bool inputRedirect() {
		//FIXME
		return false;
	}
};

#endif