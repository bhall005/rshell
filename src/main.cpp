#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>

#include "Executor.h"
#include "Input.h"

using namespace std;

int main() {
	// Create an Executor object called shell
	Executor shell;

	// Call the functions to initialize the shell, process the input, and execute the commands
	shell.init();
	shell.getInput();
	shell.execute();

	return 0;
}
