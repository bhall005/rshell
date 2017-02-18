#ifndef AND_H
#define AND_H

#include "Connector.h"
#include <iostream>

class And : public Connector {
public:
	bool execute(bool leftPass) {
		// Check whether the executable on the left succeeeded
		// If yes, execute the command on the right
		// If not, do not execute the right command and return false
		if (leftPass) {
			return this->rightCmd->execute();
		}
		else {
			return false;
		}
	}
};

#endif
