#ifndef BREAK_H
#define BREAK_H

#include "Connector.h"
#include <iostream>

class Break : public Connector {
public:
	bool execute(bool leftPass) {
		if (rightCmd != NULL) {
			cout << "I'm a break, executing: " << rightCmd->getData() << endl;
			return this->rightCmd->execute();
		}
		else {
			cout << "null" << endl;
			return false;
		}

	}
};

#endif
