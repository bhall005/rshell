#ifndef __PAREN_H
#define __PAREN_H

#include "Connector.h"
#include "Command.h"
#include <iostream>
#include <vector>

class Paren : public Command {
private:
	Command* firstCmd; //holds the first command in the parenthetical
	vector<Connector*> parenVec; //contains the rest of the connectors
	int cnctLength; //stores the number of connectors in the expression
public:
	Paren() : Command("het"), cnctLength(0) {}
	void setLength(int len) { this->cnctLength = len; }
	int getLength() { return this->cnctLength; }

	void setFirst(Command* first) { this->firstCmd = first; }
	void push_back(Connector* tmp) { this->parenVec.push_back(tmp); }
	void clearData() {
		this->cnctLength = 0;
		parenVec.clear();
	}

	bool isParen() { return true; }

	bool execute() {
		bool lastPass = this->firstCmd->execute();

		if (parenVec.size() > 0) {
			for(unsigned i = 0; i < parenVec.size(); i++) {
				lastPass = parenVec.at(i)->execute(lastPass);
			}
		}
		return lastPass;
	}
};

#endif