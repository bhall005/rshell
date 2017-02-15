#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Input.h"

class Connector {
public:
	Connector(bool leftFail, bool rightFail) : leftFail(leftFail), rightFail(rightFail) {}
	bool leftFail;
	bool rightFail;
private:
	virtual void execute() = 0;

}

#endif
