#ifndef BREAK_H
#define BREAK_H

class Break : public Connector {
public:
	bool execute(bool leftPass) {
		//execute right command after left command
		return true; //FIXME
	}
};

#endif
