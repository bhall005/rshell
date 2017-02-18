#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include "Command.h"
#include <sys/types.h>
#include <sys/wait.h>

class Executable : public Command {
public:
      Executable(string data) : Command(data) {}
      
      bool execute(){
            // Use the syscall fork() to create a child process to execute the command.
            pid_t pid = fork();
            
            // Checking whether fork() was sucessful.
            if(pid < 0) {
                  perror("The forking process failed");
                  return false;
            }
            
            // If in the child process, we will execute the command.
            if (pid == 0) {
                  // Convert the string data to a char[]
                  char str[data.length()];
                  int words = 1;
                  for(unsigned i = 0; i < data.length(); i++) {
                        str[i] = data.at(i);
                        if(data.at(i) == ' '){
                              words++;
                        }
                  }
            
                  // Convert the char[] to a char** for use in execvp()
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
                  
                  // Call execvp() to execute the command and return true if successful
                  if(execvp(arr[0], arr)){
                        return true;
                  }
                  
                  // If execvp() is not successful, return false
                  perror("An error occured while executing an argument");
                  return false;
            }
            
            // If in the parent process, call waitpid()
            if(pid > 0) {
                  int status;
                  pid_t endPID = waitpid(pid, &status, 0);
                  
                  // Check whether waitpid() was unsuccessful
                  if(endPID == -1){
                        perror("There was an error calling waitpid on a parent process");
                        return false;
                  }
                  
                  // Continue to wait until the child process is completed
                  while (endPID != pid){
                        // Continue to check whether waitpid() was unsuccessful
                        if(endPID == -1) {
                              perror("There was an error calling waitpid on a parent process");
                              return false;
                        }
                        
                        // Continue to call waitpid() while waiting
                        endPID = waitpid(pid, &status, 0);
                  }
                  
                  // Check whether the child process exited normally and return the correct bool value
                  if (WIFEXITED(status)){
                        return true;
                  }
                  
                  perror("The child process for an executable did not exit normally");
                  return false;
            }
      }
};

#endif
