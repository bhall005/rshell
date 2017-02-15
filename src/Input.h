#ifndef __INPUT_H__
#define __INPUT_H__

class Input {
public:
	string data;
private:
	Input(string data) : data(data) {}
	virtual void execute() = 0;

};

#endif
