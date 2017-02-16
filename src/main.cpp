#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>

#include "Executor.h"
#include "Input.h"

using namespace std;

int main() {
	Executor shell;

	shell.init();
	shell.getInput();

	return 0;
}