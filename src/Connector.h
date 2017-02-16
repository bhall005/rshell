#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Input.h"
#include "Command.h"

class Connector : public Input {
protected:
	Command* rightCmd;
public:
	Connector(Command* right) : Input(""), rightCmd(right) {}
	virtual bool execute(bool leftPass) = 0;

};

#endif
