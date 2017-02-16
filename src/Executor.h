#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

#include "Input.h"
#include "Command.h"
#include "Connector.h"
#include "And.h"
#include "Break.h"
#include "Or.h"

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
		
		this->parseInput(str);

		for (unsigned i = 0; i < cmdVec.size(); i++)
			cout << cmdVec.at(i)->getData() << endl;
	}

	void parseInput(string input) {
		stringstream lineStream(input);
		char curChar;
		string newCommand;
		string charBuffer;

		while(lineStream >> noskipws >> curChar) {
			if (curChar != ' ' && curChar != ';' && curChar != '&'
				&& curChar != '|' && curChar != '#') {
				if (!charBuffer.empty() && newCommand.empty()) {
					newCommand.push_back(curChar);
					charBuffer.clear();
				}
				else if (!charBuffer.empty() && !newCommand.empty()) {
					charBuffer.push_back(curChar);
					newCommand += charBuffer;
					charBuffer.clear();
				}
				else
					newCommand.push_back(curChar);
			}
			else if (curChar == ' ') {
				charBuffer.push_back(curChar);
			}
			else if (curChar == ';' || curChar == '&'
				|| curChar == '|' || curChar == '#') {
				charBuffer.clear();
				if (!newCommand.empty()) {
				Command* tmp = new Command(newCommand);
	 			cmdVec.push_back(tmp);
	 			/*FIX TO ACCOUNT FOR EXECUTIBLES AND EXITS*/
	 			if (curChar == '|')
	 				cout << "||" << endl;
	 				//CREATE NEW OR THAT POINTS AT THE RIGHT COMMAND
	 			else if (curChar == '&')
	 				cout << "&&" << endl;
	 			else if (curChar == ';')
	 				cout << ";" << endl;
	 			else if (curChar == '#')
	 				break;

	 			newCommand.clear();
	 			charBuffer.clear();
	 			}
			}
		}
	}

	// void parseCommands(char* str) {
	// 	char* point;
	// 	point = strtok(str, ";|&");

	// 	while(point != NULL) {
	// 		if(strrchr(point, '#') != NULL) {
	// 			Command* tmp = new Command(strtok(point, "#"));
	// 			cmdVec.push_back(tmp);
	// 			/*FIX TO ACCOUNT FOR EXECUTIBLES AND EXITS*/
	// 			break;
	// 		}

	// 		Command* tmp = new Command(point);
	// 		cmdVec.push_back(tmp);
	// 		/*FIX TO ACCOUNT FOR EXECUTIBLES AND EXITS*/
	// 		point = strtok(NULL, ";|&");
	// 	}
	// }

	// void parseConnectors(char* str) {
	// 	int safariVal = 0;
	// 	for (unsigned i = 0; i < cmdVec.size(); i++) {
	// 		safariVal += cmdVec.at(i)->getData().size();
	// 		char checkChar = *(str + safariVal);
	// 		cout << checkChar << endl;
	// 	}
	// }
};











#endif