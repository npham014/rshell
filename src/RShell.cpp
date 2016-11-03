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
        Parse(input);                               
        createCommands();
        runAllCommands();
        
        clearCommands();
    }while (input != "exit");
    
}



void RShell::Parse(string commandLine) {                    //This function breaks the command line into sections, based on connectors.
    if(commandLine == "") {//Make sure something was entered
        return;
    }
   
    string tempToken;
    int ampPos = 999; //Set positions to some high numbers so that they can be sorted through below (in case of multiple connectors)
    int linePos = 999;
    int semiPos = 999;
    int minPos = 9999999;
    if(commandLine.find("#") != string::npos) { //Delete any comments, they won't be necessary.
        commandLine.erase(commandLine.find("#"), (commandLine.size() - commandLine.find("#")));
    }
   
    
    while(commandLine.find("&&") != string::npos || commandLine.find("||") != string::npos || commandLine.find(";") != string::npos) {//Search for connectors
                
        if(isspace(commandLine.at(0))) {//Delete spaces that are next to connectors to make things easier to parse.
            commandLine.erase(0, 1);
        }
        
        if(commandLine.find("&&") != string::npos) {//Find the positions of any &&'s, ||'s, or ;'s
            ampPos = commandLine.find("&&");
        }
        if(commandLine.find("||") != string::npos) {
            linePos = commandLine.find("||");
        }
        if(commandLine.find(";") != string::npos) {
            semiPos = commandLine.find(";");
        }
        
        minPos = min(min(ampPos, linePos), semiPos); //Find the one closest to the left to keep commands in order.
        
    
        tempToken = commandLine.substr(0, minPos);//push the string into the vector of unbroken-up command lines.
        tokens.push_back(tempToken);
        commandLine.erase(0, minPos);

        if(commandLine != "") { //This part pushes the connectors themselves into a vector.
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
        
        if(isspace(commandLine.at(0))) {//cleaning up more spaces
            commandLine.erase(0, 1);
        }
        ampPos = 999; //Reset the positions so they can be compared again
        linePos = 999;
        semiPos = 999;
    }
    
    tokens.push_back(commandLine); //If there are no connectors, or there are no more connectors, push whatevers left.
    
    // for(int i = 0; i < tokens.size(); ++i) {
    //     cout << tokens.at(i) << endl;
    // }
    
}

void RShell::createCommands() {
    if(tokens.size() == 0) { //If there was no input, don't run this
        return;
    }
    int pos = 0;
    string temp = "";

    for(int i = 0; i < tokens.size(); ++i) {// This for loop breaks each object in the token vector into it's individual parts.
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
    
    for(int z = 0; z < commandChunks.size(); ++z) {    //Push a bunch of commands into a vector of commands.
        command* curr = new command(commandChunks.at(z));
        commandList.push_back(curr);
    }
    
    
    
    for(int b = 0; b < connectorTokens.size(); ++b) { //push all the connector tokens from earlier into a vector of connectors.
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

void RShell::runAllCommands() { //Iterate through the vector of commands and run them, based on whether they were part of a connector bunch or not.
    for(int i = 0; i < connectorList.size(); ++i) {
        if(commandList.size() > 1) {
            connectorList.at(0)->run(commandList.at(0), commandList.at(1));
            connectorList.erase(connectorList.begin());
            commandList.erase(commandList.begin());
            commandList.erase(commandList.begin());
        }
    }
    if(!(commandList.empty())) {
        commandList.at(0)->runCommand();
    }

    // while(commandList.size() > 0) {
    //     if(commandList.size() > 1) {
    //         connectorList.at(0)->left = commandList.at(0);
    //         connectorList.at(0)->right = commandList.at(1);
    //         connectorList.at(0)->run();
            
    //         connectorList.erase(connectorList.begin());
    //         commandList.erase(commandList.begin());
    //         commandList.erase(commandList.begin());
    //     }
    //     else if(commandList.size() == 1) {
    //         commandList.at(0)->runCommand();
    //         commandList.erase(commandList.begin());
    //     }
    // }
    // for(int i = 0; i < commandList.size(); ++i) {
        
    //     commandList.at(i)->runCommand(commandChunks.at(i));
        
    // }
    
}

void RShell::clearCommands() { //Get rid of any left over stuff to get ready for the next line of commands.
    commandChunks.clear();
    tokens.clear();
    connectorList.clear();
    commandList.clear();
    connectorTokens.clear();
}
    
    // char* tempToken;
    // tempToken = strtok(commandLine, " ");
    
    // vector<string> tokens;
    // while(commandLine != NULL) {
    //     cout << tempToken << endl;
    //     tokens.push_back(tempToken);
    //     tempToken = strtok(NULL, " ");
    // }
    
