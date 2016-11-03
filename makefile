all:
	mkdir bin
	g++ src/main.cpp src/RShell.cpp src/command.cpp src/andConnector.cpp src/orConnector.cpp src/semiConnector.cpp -Wall -Werror -ansi -pedantic -o rshell
	
	mv rshell bin