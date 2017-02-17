#ifndef OR_H
#define OR_H

#include "Connector.h"
#include <iostream>

class Or : public Connector {
public:
	bool execute(bool leftPass) {
		cout << "I'm an or, ";
		if (!leftPass) {
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
