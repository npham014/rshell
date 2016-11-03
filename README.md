# rshell


by Nathan Pham and Ryan Wilson

	In this assignment we created a basic Shell progam called RShell. The program operates by taking input from the user in order to generate a list of commands for the script to execute. It does this by parsing through these commands and seperating the connectors (&&, ;, ||) from the actual commands. Then, it takes these commands and executes them based on the connectors given and whether the commands are successful.

	Known Bugs:
		Multiple semicolons in a row with no whitespace or commands crashes program.
		