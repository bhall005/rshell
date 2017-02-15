#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

#include "Input.h"

using namespace std;

class Executor {
private:
	vector<Command*> cmdVec; //Stores current set of Commands
	vector<Connector*> cnctVec; //Stores current set of Connectors
	char lgn[256]; //Stores userlogin
	char hostName[256]; //Stores the host name


public:
	void init() { //Initializes the shell
		cout << "Welcome to rshell - By Brennan Hall & Vanessa Le" << endl;
		getlogin_r(lgn, 256); //Retreives userlogin from the system
		if (lgn[0] == '\0') //Error checks a null stream
			perror("Login detection failed");
		gethostname(hostName, 256); //Retrieves hostname from system
		if (hostName[0] == '\0') //Error checks a null stream
			perror("hostname detection failed");
	}

	void getInput() {
		char str[256]; //Cstring to store userinput
		cout << lgn << "@" << hostName << "$ "; //Console message
		cin.getline(str, 256);
		
		char* point;
		point = strtok(str, ";|&");

		while(point != NULL) {
			//FIXME
		}

	}
};











#endif