#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Input.h"
#include "Command.h"

class Connector : public Input {
protected:
	Command* rightCmd;
public:
	Connector() : Input("") {}
	Connector(Command* right) : Input(""), rightCmd(right) {}
	virtual bool execute(bool leftPass) = 0;
	void setCmd(Command* right) { this->rightCmd = right; }
	string getCmd() { return this->rightCmd->getData(); }

};

#endif
