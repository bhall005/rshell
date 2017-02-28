#ifndef TEST_H
#define TEST_H

#include "Command.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

class Test : public Command {
private:
      bool e;
      bool f;
      bool d;
public:
      //assuming data is the path and flags are set in constructor
      Test(string data) : Command(data), e(true), f(false), d(false) {}
      Test(string data, bool e, bool f, bool d) : Command(data), e(e), f(f), d(d) {}
      
      bool execute(){
            struct stat path;
            stat(data.c_str(), &path);
            
            if (path.st_mode){
                  if (e || (f && S_ISREG(path.st_mode)) || (d && S_ISDIR(path.st_mode))){
                        cout << "(True)" << endl;
                        return true;
                  }
                  else {
                        cout << "error" << endl;
                        return false;
                  }
            }
            else{
                  cout << "(False)" << endl;
                  return false;
            }

            return false;
      }
};

#endif
