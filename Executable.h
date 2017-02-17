#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include "Command.h"
#include <sys/types.h>
#include <sys/wait.h>

class Executable : public Command {
public:
      Executable(string data) : Command(data) {}
      
      bool execute(){
            fork();
            pid_t pid = getpid();
            pid_t endPID;
            
            if (pid == 0) {
                  
                  //execvp requires name of file to be executed and char** (similar to main) 
                  //if(execvp(filename, data)){
                  //      return true;
                  //}
                  return false;
            }
            else if(pid == -1){
                  perror("The forking proccess for an executable has failed.");
                  return false;
            }
            else {
                  int status;
                  endPID = waitpid(pid, &status, 0);
                  
                  while (endPID != pid){
                        if(endPID == -1)
                        {
                              perror("There was an error calling waitpid on a parent process.");\
                              return false;
                        }
                        
                        endPID = waitpid(pid, &status, 0);
                  }
                  
                  if (WIFEXITED(status)){
                        return true;
                  }
                  else {
                        perror("The child process for an executable did not exit normally.");
                        return false;
                  }
            }
      }
};

#endif