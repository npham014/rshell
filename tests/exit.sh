#!../bin/rshell
#We tested our program manually, so below is a list of test cases we used.
exit
echo byebye && exit
echo byebye && exit ; echo "you'll never see this message"
echo ending || exit

#exit