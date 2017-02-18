#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Input.h"
#include "Command.h"

class Connector : public Input {
protected:
	Command* rightCmd;
public:
	// Default Constructor: stores an empty string as data
	Connector() : Input("") {}
	// Constructor that leaves data emtpy and stores a pointer to the command on the right of the connector
	Connector(Command* right) : Input(""), rightCmd(right) {}
	
	// Virtual execute() function: Parameter represents whether the command on the left was executed successfully
	// Will be implemented in And, Or, and Break classes
	virtual bool execute(bool leftPass) = 0;
	
	// Functions to change and access rightCmd
	void setCmd(Command* right) { this->rightCmd = right; }
	string getCmd() { return this->rightCmd->getData(); }
};

#endif
