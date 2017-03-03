#ifndef TEST_H
#define TEST_H

#include "Command.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

class Test : public Command {
private:
      char flag;
public:
      //assuming data is the path and flags are set in constructor
      Test(string data) : Command(data), flag('e') {}
      Test(string data, char flag) : Command(data), flag(flag) {}
      
      bool execute(){
            struct stat path;
            
            if (flag != 'e' && flag != 'f' && flag != 'd') {
                  perror("The flag specified is not valid");
                  return false;
            }
            
            if (stat(data.c_str(), &path) == -1){
                  cout << "(False)" << endl;
                  return false;
            }
            
            if ((flag == 'e' && path.st_mode) || (flag == 'f' && S_ISREG(path.st_mode)) || (flag == 'd' && S_ISDIR(path.st_mode))){
                  cout << "(True)" << endl;
                  return true;
            }
            else {
                  cout << "(False)" << endl;
                  return false;
            }
      }
};

#endif
