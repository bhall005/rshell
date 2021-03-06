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
#include "Test.h"
#include "Paren.h"

using namespace std;

class Executor {
private:
	vector<Command*> cmdVec; //Stores current set of Commands
	vector<Connector*> cnctVec; //Stores current set of Connectors
	vector<Paren*> prpVec; //Stores list of known parentheticals
	//Pipe* tmpPipe = NULL; //buffer for a new Pipe command that needs a right
	char lgn[256]; //Stores userlogin
	char hostName[256]; //Stores the host name

	void parseInput(string input) {
		stringstream lineStream(input);
		char curChar;
		bool testFlag = false;
		bool keepPipe = false;
		int parenIndex = -1;
		int cctLength = 0;
		string newCommand;
		string charBuffer;

		while (lineStream >> noskipws >> curChar) {
			if (curChar != ' ' && curChar != ';' && curChar != '&'
				&& curChar != '|' && curChar != '#' && curChar != '['
				&& curChar != '(' && curChar != ')'
				&& curChar != '>' && curChar != '<') {
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
				|| curChar == '|' || curChar == '#' 
				|| curChar == '[' || curChar == '('
				|| curChar == '<' || curChar == '>') {
				charBuffer.clear();
				if (!newCommand.empty() || testFlag) {
					if (curChar == '|') {
	 				lineStream >> noskipws >> curChar;
	 				if (curChar == '|') {
	 					Connector* tmp = new Or();
	 					cnctVec.push_back(tmp);
	 					keepPipe = false;
	 				}
	 				else {
	 					newCommand += " | ";
	 					keepPipe = true;
	 				}

	 				if (parenIndex > -1)
	 					cctLength++;
	 			}
	 			else if (curChar == '>') {
	 				// lineStream >> noskipws >> curChar;
	 				newCommand += " >";
	 				keepPipe = true;
	 				// if (curChar == '>') {
	 				// 	tmpPipe = new Pipe(">>", newCommand);
	 				// }
	 				// else {
	 				// 	tmpPipe = new Pipe(">", newCommand);
	 				// }
	 				// newCommand.clear();
	 				// charBuffer.clear();
	 			}
	 			else if (curChar == '<') {
	 			      newCommand += " < ";
	 				// tmpPipe = new Pipe("<", newCommand);
	 				// newCommand.clear();
	 				// charBuffer.clear();
	 				keepPipe = true;
	 			}
	 			else if (curChar == '&') {
	 				Connector* tmp = new And();
	 				cnctVec.push_back(tmp);
	 				keepPipe = false;

	 				if (parenIndex > -1)
	 					cctLength++;
	 			}
	 			else if (curChar == ';') {
	 				keepPipe = false;
	 				Connector* tmp = new Break();
	 				cnctVec.push_back(tmp);

	 				if (parenIndex > -1)
	 					cctLength++;
	 			}
	 			else if (curChar == '#') {
	 				newCommand.clear();
	 				return;
	 			}

	 			if (!newCommand.empty() && !keepPipe) {

				  //  if (tmpPipe != NULL) {
				  //  	tmpPipe->setRight(newCommand);
				  //  	newCommand.clear();
				  //  	cmdVec.push_back(tmpPipe);
				  //  	tmpPipe = NULL;
				  //  }  
				//	else 
					if (newCommand == "exit") {
						Command* tmp = new Exit();
						cmdVec.push_back(tmp);
					}
					else if (strncmp(newCommand.c_str(), "test", 4) == 0) {
					      char testCommand[] = "";
					      unsigned i = 0;
					      unsigned j = 5;
					      char flag = 'e';
					      while (newCommand[i + j] != '\0') {
					            if (newCommand[i + j] == '-') {
					                  flag = newCommand[i + j + 1];
					                  j += 3;
					            }
					            else {
      					            testCommand[i] = newCommand[i + j];
      					            i++;
					            }
					      }
					      
					      Command *tmp = new Test(testCommand, flag);
					      cmdVec.push_back(tmp);
					}
					else {
						Command* tmp = new Executable(newCommand);
						cmdVec.push_back(tmp);
					}

	 			newCommand.clear();
	 			charBuffer.clear();
	 			testFlag = false;
	 			}
	 			else if (curChar == '[') {
	 				string testCommand;
	 				char flag = 'e';
	 				while (lineStream >> noskipws >> curChar) {
						if (curChar == '-') {
							lineStream >> noskipws >> curChar;
					    	flag = curChar;
						}
						else if (curChar != ' ' && curChar != ']')
      						testCommand.push_back(curChar);
      					else if (curChar == ']') {
      						testFlag = true;
      						break;
      					}
	 				}
	 				Command *tmp = new Test(testCommand, flag);
					cmdVec.push_back(tmp);

					newCommand.clear();
	 				charBuffer.clear();
	 			}
	 			else if(curChar == '(') {
					parenIndex = cmdVec.size() - 1;
	 			}
	 			else
	 				if (curChar == '#')
	 					return;
			}
		}
			if (curChar == ')' && parenIndex > -1) {
				Paren* parenTmp = new Paren();
				parenTmp->setLength(cctLength);
				Command* tmp = parenTmp;
				cmdVec.insert(cmdVec.begin() + parenIndex, tmp);
				prpVec.push_back(parenTmp);
				parenTmp->clearData();

				cctLength = 0;
				parenIndex = -1;
			}
		}
		if (!newCommand.empty()) {
			if (newCommand == "exit") {
				Command* tmp = new Exit();
				cmdVec.push_back(tmp);
			}
			else if (strncmp(newCommand.c_str(), "test", 4) == 0) {
				char testCommand[] = "";
			    unsigned i = 0;
		        unsigned j = 5;
				char flag = 'e';
				while (newCommand[i + j] != '\0') {
					if (newCommand[i + j] == '-') {
					    flag = newCommand[i + j + 1];
					    j += 3;
					}
					else {
      					testCommand[i] = newCommand[i + j];
      					i++;
					}
				}
					      
				Command *tmp = new Test(testCommand, flag);
				cmdVec.push_back(tmp);
			}
// 			else if (tmpPipe != NULL) {
// 		    	tmpPipe->setRight(newCommand);
// 		    	newCommand.clear();
// 		    	cmdVec.push_back(tmpPipe);
// 		    	tmpPipe = NULL;
// 			}  
			else {
				Command* tmp = new Executable(newCommand);
				cmdVec.push_back(tmp);
			}
	 	}

	 	if (parenIndex > -1) {
	 		Paren* parenTmp = new Paren();
	 		parenTmp->setLength(cctLength);
			Command* tmp = parenTmp;
			cmdVec.insert(cmdVec.begin() + parenIndex, tmp);
			prpVec.push_back(parenTmp);
			parenTmp->clearData();
				
			cctLength = 0;
			parenIndex = -1;
		}
	}

	void fillConnectors() {
		if (cmdVec.empty())
			return;
		unsigned vecBound = 0;
		if (cmdVec.size() > cnctVec.size())
			vecBound = cnctVec.size();
		else 
			vecBound = cnctVec.size() - 1;
		for (unsigned i = 0; i < vecBound; ++i) {
			cnctVec.at(i)->setCmd(cmdVec.at(i + 1));
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
		string str; //Cstring to store userinput
		//Console message
		while(str.empty()) {
			cout << lgn << "@" << hostName << "$ "; 	
			getline(cin, str);
		}
	
		this->parseInput(str);
		this->fillConnectors();
	}

	void execute() {
		bool lastPass = false;
		if (cmdVec.size() > 0)
			lastPass = cmdVec.at(0)->execute();

		if (cnctVec.size() > 0) {
			for(unsigned i = 0; i < cnctVec.size(); i++) {
				lastPass = cnctVec.at(i)->execute(lastPass);
			}
		}
		
		cnctVec.clear();
		cmdVec.clear();
		prpVec.clear();
	}
};

#endif
