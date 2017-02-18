#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include "Command.h"
#include <sys/types.h>
#include <sys/wait.h>

class Executable : public Command {
public:
      Executable(string data) : Command(data) {}
      
      bool execute(){
           // fork();
           // pid_t pid = getpid();
	pid_t pid = fork();
            
	if(pid < 0) {
		perror("The forking process failed");
		return false;
	}

	if (pid == 0) {
		char str[data.length()];
		int words = 1;
		for(unsigned i = 0; i < data.length(); i++) {
			str[i] = data.at(i);
			if(data.at(i) == ' '){
				words++;
			}
		}
		char * argument;
		argument = strtok (str, " ");
		char** arr = new char*[words];
		unsigned j = 0;

		while (argument != NULL) {
			arr[j] = new char[strlen(argument)];
			strcpy(arr[j], argument);
			j++;
			argument = strtok(NULL, " ");
		} 
                 
                  if(execvp(arr[0], arr)){
                        return true;
                  }

		perror("An error occured while executing an argument");
                  return false;
            }
            

	if(pid > 0) {
                  int status;
                  pid_t endPID = waitpid(pid, &status, 0);
		if(endPID == -1){
			perror("There was an error calling waitpid on a parent process");
			return false;
		}
                  
                  while (endPID != pid){
                        if(endPID == -1) {
                              perror("There was an error calling waitpid on a parent process");
                              return false;
                        }
                        
                        endPID = waitpid(pid, &status, 0);
                  }
                  
                  if (WIFEXITED(status)){
                        return true;
                  }
                  
                  perror("The child process for an executable did not exit normally");
                  return false;
            }
      }
};

#endif
