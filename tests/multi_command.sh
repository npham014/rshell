#!../bin/rshell
#We tested our program manually, so below is a list of test cases we used.

echo hello && echo world
echo hello || echo world
echo hello ; echo world

echo hello && echo world || echo tool
echo hello || echo world && echo tool 
echo hello || echo world ; echo school
ls -l ; echo hi ; echo frivelous ; ls
echo hello ; echo world && hi
echo hello && echo world ; echo tool
echo hello ; echo world || echo cheese
echo hell0 ;echo hell0 ;echo hell0 ;echo hell0 ;echo hell0 ;echo hell0 
echo hell0 || echo hell0 || echo hell0 || echo hell0 || echo hell0 || echo hell0 
echo hell0 && echo hell0 && echo hell0 && echo hell0 && echo hell0 &&echo hell0 

&& echo hello
&& || ;