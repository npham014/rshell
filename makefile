all:
	mkdir bin
	g++ src/main.cpp src/RShell.cpp src/command.cpp src/andConnector.cpp src/orConnector.cpp src/semiConnector.cpp src/test.cpp -Wall -Werror -ansi -pedantic -o rshell -g
	
	mv rshell bin