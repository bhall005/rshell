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
#include "Executable.h"
#include "Exit.h"

using namespace std;

class Executor {
private:
	vector<Command*> cmdVec; //Stores current set of Commands
	vector<Connector*> cnctVec; //Stores current set of Connectors
	char lgn[256]; //Stores userlogin
	char hostName[256]; //Stores the host name

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
					if (newCommand == "exit") {
						Command* tmp = new Exit();
						cmdVec.push_back(tmp);
					}
					else {
						Command* tmp = new Executable(newCommand);
						cmdVec.push_back(tmp);
					}
	 			if (curChar == '|') {
	 				//cout << "||" << endl;
	 				Connector* tmp = new Or();
	 				cnctVec.push_back(tmp);
	 				//CREATE NEW OR THAT POINTS AT THE RIGHT COMMAND
	 			}
	 			else if (curChar == '&') {
	 				//cout << "&&" << endl;
	 				Connector* tmp = new And();
	 				cnctVec.push_back(tmp);
	 			}
	 			else if (curChar == ';') {
	 				//cout << ";" << endl;
	 				Connector* tmp = new Break();
	 				cnctVec.push_back(tmp);
	 			}
	 			else if (curChar == '#') {
	 				newCommand.clear();
	 				return;
	 			}

	 			newCommand.clear();
	 			charBuffer.clear();
	 			}
	 			else
	 				if (curChar == '#')
	 					return;
			}
		}
		if (!newCommand.empty()) {
			if (newCommand == "exit") {
				Command* tmp = new Exit();
				cmdVec.push_back(tmp);
			}
			else {
				Command* tmp = new Executable(newCommand);
				cmdVec.push_back(tmp);
			}
	 	}
	}

	void fillConnectors() {
		unsigned vecBound = 0;
		if (cmdVec.size() > cnctVec.size())
			vecBound = cnctVec.size();
		else 
			vecBound = cnctVec.size() - 1;
		for (unsigned i = 0; i < vecBound; ++i) {
			cnctVec.at(i)->setCmd(cmdVec.at(i + 1));
			//cout << i << " points to " << cnctVec.at(i)->getCmd() << endl;
		}
	}

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
		this->fillConnectors();

		// for (unsigned i = 0; i < cmdVec.size(); i++)
		// 	cout << '\"' << cmdVec.at(i)->getData() << '\"' << endl;
	}

	void execute() {
		bool lastPass = cmdVec.at(0)->execute();

		if (cnctVec.size() > 0)
			for(unsigned i = 0; i < cnctVec.size(); i++)
				lastPass = cnctVec.at(i)->execute(lastPass);
	}

	// void parseCommands(char* str) {
	// 	char* point;
	// 	point = strtok(str, ";|&");

	// 	while(point != NULL) {
	// 		if(strrchr(point, '#') != NULL) {
	// 			Command* tmp = new Command(strtok(point, "#"));
	// 			cmdVec.push_back(tmp);
	// 			/*FIX TO ACCOUNT FOR ExecutableS AND EXITS*/
	// 			break;
	// 		}

	// 		Command* tmp = new Command(point);
	// 		cmdVec.push_back(tmp);
	// 		/*FIX TO ACCOUNT FOR ExecutableS AND EXITS*/
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