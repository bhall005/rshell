#ifndef AND_H
#define AND_H

#include "Connector.h"
#include <iostream>

class And : public Connector {
public:
	bool execute(bool leftPass) {
		cout << "I'm an and, ";
		if (leftPass) {
			cout << "executing: " << rightCmd->getData() << endl;
			return this->rightCmd->execute();
		}
		else {
			cout << "not executing: " << rightCmd->getData() << endl;
			return false;
		}
	}
};

#endif
