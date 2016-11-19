# rshell


 by Nathan Pham and Ryan Wilson

This program takes input from the user as individual commands that are executed through user/bin.
It does this by parsing through the commands and seperating the connectors from the commands and arguments.
Once seperated, it executes the commands based off the runability and connectors used.


##Bugs
-Program crashes when a list of multiple semi-colons joined together between commands
-Program crashes when a list of multiple semi-colons are together without any commands
###Bugs Involving Test:

-Strange punctuation e.g. ' causes crash

-Unable to go up directories. Not sure how to implement this