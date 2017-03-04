#ifndef OR_H
#define OR_H

#include "Connector.h"
#include <iostream>

class Or : public Connector {
public:
	bool execute(bool leftPass) {
		// Check whether the command on the left was executed successfully
		// If not, call execute() on the command on the right and return that bool value
		// If it did, return true
		if (!leftPass) {
			return this->rightCmd->execute();
		}
		else {
			return true;
		}
	}
};

#endif
