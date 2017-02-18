# rshell
---
This program prints a command prompt and reads in a line of commands. The command prompt is printed in the format username@hostname$, and the user can type in a single command or a chain of commands by using the connectors ||, &&, or ;. The connectors will determine whether to run the command on the right based on the success of the command on the left.

* || will run the next command if the previous command fails.
* && will run the next command if the previous command succeeds.
* ;  will run the next command regardless of the success of the previous command.


# Known Bugs
---

* Currently, the program only accepts command lines with proper syntax. Inputting a command line with typing errors or a command line that does not follow the expected format of surrounding every connector by arguments will result in errors or the commands not being run correctly.
* In addition, inputting an incorrect command may cause errors in the next command line that is input. For example, inputting a random string of letters will cause the correct errors to be thrown and the program will move on and prompt the user for a new line. However, calling exit in the next line will not exit the program. Exit must be called twice for the program to exit correctly.
