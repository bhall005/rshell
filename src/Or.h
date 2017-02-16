#ifndef OR_H
#define OR_H

class Or : public Connector {
public:
	bool execute(bool leftPass) {
		//execute right command is left command fails
		return true; //FIXME
	}

};

#endif
