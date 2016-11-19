#include "RShell.h"

RShell::RShell() {
    connectorStrings.push_back("&&");
    connectorStrings.push_back("||");
    connectorStrings.push_back(";");
}

void RShell::Run() {
    string input = "";
    
    do {
        cout << "$";                                //continuously asks for user commands until exit is called
        getline(cin, input);                    
        if (input == "exit") {                      //if the user enters exit, the shell closes.
            break;
        }
        Parse(input);                               //sorts through the information
        createCommands();                           //then it creates the commands to run later
        
        int checkExit = runAllCommands();           //if a command returned -5, it was an exit. 
        if(checkExit == -5) {                       //This kills the program.
            break;
        }
        
        clearCommands();                            //deletes all allocated memory
    } while (input != "exit");
    
}



void RShell::Parse(string commandLine) {                    //This function breaks the command line into sections, based on connectors.
    if(commandLine == "") {                                 //Make sure something was entered
        return;
    }
    
   
    string tempToken;
    int ampPos = 999;                                       //Set positions to some high numbers so that they can be sorted through below (in case of multiple connectors)
    int linePos = 999;
    int semiPos = 999;
    int minPos = 9999999;
    if(commandLine.find("#") != string::npos) {             //Delete any comments, they won't be necessary.
        commandLine.erase(commandLine.find("#"), (commandLine.size() - commandLine.find("#")));
    }
    
    
   
    
    while(commandLine.find("&&") != string::npos || commandLine.find("||") != string::npos || commandLine.find(";") != string::npos) {//Search for connectors
                
        if(isspace(commandLine.at(0))) {                //Delete spaces that are next to connectors to make things easier to parse.
            commandLine.erase(0, 1);
        }
        
        if(commandLine.find("&&") != string::npos) {    //Find the positions of any &&'s, ||'s, or ;'s
            ampPos = commandLine.find("&&");
        }
        if(commandLine.find("||") != string::npos) {
            linePos = commandLine.find("||");
        }
        if(commandLine.find(";") != string::npos) {
            semiPos = commandLine.find(";");
        }
        
        minPos = min(min(ampPos, linePos), semiPos);    //Find the one closest to the left to keep commands in order.
        
        string soloConnector = commandLine.substr(0, minPos + 2);
        soloConnector.erase( std::remove_if( soloConnector.begin(), soloConnector.end(), ::isspace ), soloConnector.end() );
        if(soloConnector == "&&" || soloConnector == "||" || soloConnector == ";") {
            return;
        }
        
    
        tempToken = commandLine.substr(0, minPos);      //push the string into the vector of unbroken-up command lines.
        tokens.push_back(tempToken);
        commandLine.erase(0, minPos);

        if(commandLine != "") {                         //This part pushes the connectors themselves into a vector.
            if(commandLine.at(0) != ';') {
                string conToken = commandLine.substr(0, 2);
                connectorTokens.push_back(conToken);
                commandLine.erase(0, 2);
            }
            else {
                string conToken = commandLine.substr(0, 1);
                connectorTokens.push_back(conToken);
                commandLine.erase(0, 1);
            }
        }
        if(isspace(commandLine.at(0))) {                //cleaning up more spaces
            commandLine.erase(0, 1);
        }
        ampPos = 999;                                   //Reset the positions so they can be compared again
        linePos = 999;
        semiPos = 999;
    }
    tokens.push_back(commandLine);                      //If there are no connectors, or there are no more connectors, push whatevers left.
}

void RShell::createCommands() {
    
    if(tokens.size() == 0) { //If there was no input, don't run this
        return;
    }
    int pos = 0;
    string temp = "";

    for(unsigned int i = 0; i < tokens.size(); ++i) {// This for loop breaks each object in the token vector into it's individual parts.
        vector<string> brokenChunks;                
        do {// This is the part that actually breaks it into parts. the outer loop iterates through the tokens.
            pos = tokens.at(i).find(" ");
            temp = tokens.at(i).substr(0, pos);
            tokens.at(i).erase(0, pos + 1);
            brokenChunks.push_back(temp);
        } while(tokens.at(i).find(" ") != string::npos);
        if(tokens.at(i) != "" && tokens.at(i) != brokenChunks.at(0)) {//Used to fix an issue with final pieces of tokens.
            brokenChunks.push_back(tokens.at(i));
        }
        commandChunks.push_back(brokenChunks);
    }
    
    for(unsigned c = 0; c < commandChunks.size(); ++c) {//This loop will go through the command chunks (vector of command lines broken up by token. e.g.: commandChunks.at(1) = [ls, -l]
        if(commandChunks.at(c).at(0) == "test") {//Looping through big vector to check if there are any tests in it. If there is, create a new Test object.
        
            if(commandChunks.at(c).size() == 3){
                if(commandChunks.at(c).at(1) == "-f") {//if statements for different flags
                    Test* temp = new Test(commandChunks.at(c).at(2),"-f");//Make a new test object (inherited from command)
                    commandList.push_back(temp);//Push the test command into the list
                    commandChunks.erase(commandChunks.begin());//If a test command was made, get rid of it now. (So that it won't get pushed twice)
                    break;
                }
                else if(commandChunks.at(c).at(1) == "-d") {
                    Test* temp = new Test(commandChunks.at(c).at(2),"-d");
                    commandList.push_back(temp);
                    commandChunks.erase(commandChunks.begin());
                    break;
                }
                else if(commandChunks.at(c).at(1) == "-e") {//Flag set to -e
                    Test* temp = new Test(commandChunks.at(c).at(2),"-e");
                    commandList.push_back(temp);
                    commandChunks.erase(commandChunks.begin());
                    break;
                }//End inner else
                else {
                    cout << "Error invalid flag input" << endl;
                }
            }//End "test" token size check
            
            if(commandChunks.at(c).size() == 2) {//There was no flag. Defaults to -e
                Test* temp = new Test(commandChunks.at(c).at(1), "-e");
                commandList.push_back(temp);
                commandChunks.erase(commandChunks.begin());
                break;
            }
            
        }//end "test" token if
        
        if(commandChunks.at(c).at(0).at(0) == '[') {//In the case that brackets were used instead of test
            commandChunks.at(c).at(0).erase(commandChunks.at(c).at(0).begin());  //Delete the bracket
            string LastCommand = commandChunks.at(c).at(commandChunks.at(c).size() - 1);
            if(LastCommand.at(LastCommand.size() - 1) == ']') {
                 //commandChunks.at(c).at(commandChunks.at(c).size() - 1).erase(commandChunks.at(c).at(commandChunks.at(c).size() - 1).end());//Delete the other bracket
                if(commandChunks.at(c).size() == 2) {//all numbers in this if have been scaled down 1 from the above if, because there is no "test" token
                    if(commandChunks.at(c).at(0) == "-f") {//if statements for different flags
                        Test* temp = new Test(commandChunks.at(c).at(1).substr(0, commandChunks.at(c).at(1).size() - 1),"-f");//Make a new test object (inherited from command)
                        commandList.push_back(temp);//Push the test command into the list
                        commandChunks.erase(commandChunks.begin());
                        break;
                    }
                    else if(commandChunks.at(c).at(0) == "-d") {
                        Test* temp = new Test(commandChunks.at(c).at(1).substr(0, commandChunks.at(c).at(1).size() - 1),"-d");
                        commandList.push_back(temp);
                        commandChunks.erase(commandChunks.begin());
                        break;
                    }
                    else {//Flag set to -e or none was input. Either way defaults to -e
                        Test* temp = new Test(commandChunks.at(c).at(1).substr(0, commandChunks.at(c).at(1).size() - 1),"-e");
                        commandList.push_back(temp);
                        commandChunks.erase(commandChunks.begin());
                        break;
                    }// End inner else
                }// End [] size check                
            }// End ] check

        }// End main [ if
    }//End "test" command loop
    
    
    for(unsigned int z = 0; z < commandChunks.size(); ++z) {    //Push a bunch of commands into a vector of commands.
        command* curr = new command(commandChunks.at(z));
        commandList.push_back(curr);
    }
    
    
    for(unsigned int b = 0; b < connectorTokens.size(); ++b) { //push all the connector tokens from earlier into a vector of connectors.
        if(connectorTokens.at(b) == "&&") {
            connector* temp = new andConnector();
            connectorList.push_back(temp);
        }
        else if(connectorTokens.at(b) == "||") {
            connector* temp = new orConnector();
            connectorList.push_back(temp);
        }
        else if(connectorTokens.at(b) == ";") {
            connector* temp = new semiConnector();
            connectorList.push_back(temp);
        }
    }
}

int RShell::runAllCommands() { //Iterate through the vector of commands and run them, based on whether they were part of a connector bunch or not.
    if(commandList.size() == 0) {
        return 0;
    }
    
    if (commandList.size() == 1) {
        commandList.at(0)->runCommand();
        return 0;
    }
    
    for(unsigned int i = 0; i < connectorList.size(); ++i) {                        //Pass two commands into connectors.
        
        connectorList.at(i)->run(commandList.at(i), commandList.at(i + 1));         //The connector then runs them/determines if they should be run
        if(commandList.at(i)->status == -5 || commandList.at(i + 1)->status == -5) { //This is to check if an exit was thrown into the mix
            return -5;
        }
    }
    return 0;
}

void RShell::clearCommands() { //Get rid of any left over stuff to get ready for the next line of commands.
    commandChunks.clear();
    tokens.clear();
    connectorList.clear();
    commandList.clear();
    connectorTokens.clear();
}
