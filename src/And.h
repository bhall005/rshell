#ifndef AND_H
#define AND_H

class And : public Connector {
public:
	bool execute(bool leftPass) {
		//execute right command is left command succeeds
		return true; //FIXME
	}
};

#endif
