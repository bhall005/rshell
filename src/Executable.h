#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include "Command.h"
#include "Exit.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

class IONode {
      public:
            IONode() {};
            IONode * left;
            IONode * right;
            virtual bool execute() = 0;
};

class Pipe : public IONode {
      public:
            Pipe() {left = 0; right = 0;};
            bool execute();
};

class Leaf : public IONode {
      public:
            Leaf(string &s) {data = s; left = 0; right = 0;};
            bool execute();
            string data;
};

char * RandString(const int len) {
    char * string = (char *)malloc(len * sizeof(char));
    char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; i++) {
        string[i] = alphabet[rand() % (62)];
    }
    string[len] = 0;
    return string;
}

bool Pipe::execute() {
      int backfd, newfd;
      fflush(stdout);
      backfd = dup(1);
      char * str = RandString(40);
      str[0] = '/';
      str[1] = 't';
      str[2] = 'm';
      str[3] = 'p';
      str[4] = '/';
      FILE * file = fopen(str, "wb");
      newfd = fileno(file);

      dup2(newfd, 1);
      close(newfd);
      
      left->execute();
      
      fflush(stdout);
      dup2(backfd, 1);
      close(backfd);
      
      Leaf * cmd = (Leaf *)right;
      
      int i;
      for (i = 0; i != (int)cmd->data.size() && cmd->data[i] != ' '; i++) {
            
      }
      string basecmd = cmd->data.substr(0, i);
      

      if(basecmd == "grep" || basecmd == "cat") {
            cmd->data += (" " + string(str));
      }
      
      bool status = right->execute();
      remove(str);
      return status;
}

class Executable : public Command {
public:
      Executable(string data) : Command(data) {}
      bool isParen() { return false; }
      
      bool execute(){

            IONode * root = 0;
            IONode * parent = 0;
            string datacpy = data;
            int pos;
            while ((pos = (int)datacpy.find_last_of("|")) != (int)string::npos) {
                  string right = datacpy.substr(pos + 2);
                  datacpy = datacpy.substr(0, pos-1);
                  Leaf * l = new Leaf(right);
                  Pipe * p = new Pipe();
                  if (!root) {
                        parent = root = p;
                        root->right = l;
                  }
                  else {
                        parent->left = p;
                        parent = p;
                        p->right = l;
                  }
            }
            if (root) {
                  parent->left = new Leaf(datacpy);
                  return root->execute();
            }
            
            if ((pos = data.find(">")) != (int)string::npos){
                  int backfd, newfd;
                  fflush(stdout);
                  backfd = dup(1);
                  FILE * file = 0;
                  int i;
                  for (i = pos; data.at(i) != ' '; i++) {
                        
                  }
                  for (; data.at(i) == ' '; i++) {
                        
                  }
                  int start = i;
                  int end;
                  for (end = start; end != (int)data.size() && data.at(end) != ' '; end++) {
                        
                  }
                  string filename = data.substr(start, end - start);
                  if (data.at(pos+1) == '>') {
                        file = fopen(filename.c_str(), "a+");
                  }
                  else {
                        file = fopen(filename.c_str(), "wb");
                  }
                  newfd = fileno(file);
                  dup2(newfd, 1);
                  close(newfd);
                  
                  string left = data.substr(0, pos - 1);
                  Executable * e = new Executable(left);
                  bool status = e->execute();
                  
                  fflush(stdout);
                  dup2(backfd, 1);
                  close(backfd);
                  return status;
            }
            else if ((pos = data.find("<")) != (int)string::npos) {
                  int i;
                  for (i = 0; i != (int)data.size() && data[i] != ' '; i++) {
                        
                  }
                  string basecmd = data.substr(0, i);
                  
                  if (basecmd == "grep" || basecmd == "cat") {
                        data = data.substr(0, pos - 1) + data.substr(pos + 2);
                  }
                  else {
                        data = data.substr(0, pos - 1);
                  }
            }
            
            // Use the syscall fork() to create a child process to execute the command.
            pid_t pid = fork();
            
            // Checking whether fork() was sucessful.
            if (pid < 0) {
                  perror("The forking process failed");
                  return false;
            }
            
            // If in the child process, we will execute the command.
            if (pid == 0) {
                  // Convert the string data to a char[]
                  char str[256];
                  int words = 1;
                  for(unsigned i = 0; i < data.length(); i++) {
                        str[i] = data.at(i);
                        if(data.at(i) == ' '){
                              words++;
                        }
                  }
                  str[data.length()] = '\0';
                  
            
                  // Convert the char[] to a char** for use in execvp()
                  char * argument;
                  argument = strtok (str, " ");
                  char** arr = new char*[words + 1];
                  unsigned j = 0;
                  
                  while (argument != NULL) {
                        arr[j] = new char[strlen(argument)];
                        strcpy(arr[j], argument);
                        j++;
                        argument = strtok(NULL, " ");
                  } 
                  arr[words] = NULL;
                  
                  // Call execvp() to execute the command
                  int executed = execvp(arr[0], arr);
                  
                  if(executed == -1){
                       // If execvp() is not successful, return false
                        perror("An error occured while executing an argument");
                        exit(0);
                        return false;
                  }
                  
                  return true;
            }
            
            // If in the parent process, call waitpid()
            if (pid > 0) {
                  int status;
                  pid_t endPID = waitpid(pid, &status, 0);
                  
                  // Check whether waitpid() was unsuccessful
                  if (endPID == -1){
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
            
            return false;
      }
};

bool Leaf::execute() {
      Command * cmd = 0;
      if (data.substr(0, 4) == "exit") {
		cmd = new Exit();
	}
	cmd = new Executable(data);
      return cmd->execute();
}

#endif
