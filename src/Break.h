#ifndef BREAK_H
#define BREAK_H

#include "Connector.h"
#include <iostream>

class Break : public Connector {
public:
	bool execute(bool leftPass) {
		// Check whether there is a command on the right
		// If so, execute it and return the bool value from calling the command's execute()
		// If not, return false
		leftPass = false;
		if (rightCmd != NULL) {
			return this->rightCmd->execute();
		}
		else {
			return leftPass;
		}
	}
};

#endif
