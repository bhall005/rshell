# rshell
---
This program prints a command prompt and reads in a line of commands. The command prompt is printed in the format username@hostname$, and the user can type in a single command or a chain of commands by using the connectors ||, &&, or ;. The connectors will determine whether to run the command on the right based on the success of the command on the left.

* || will run the next command if the previous command fails.
* && will run the next command if the previous command succeeds.
* ;  will run the next command regardless of the success of the previous command.


# Known Bugs
---

* Currently, the program only accepts command lines with proper syntax. Inputting a command line with typing errors or a command line that does not follow the expected format of surrounding every connector by arguments cannot be run correctly.
