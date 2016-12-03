#All testing done by hand

cd src
cd src/testfolder
cd src/testfolder/testfolder2
cd src/testfolder/testfolder2 ; ls
cd testfolder2 (after cd src/testfolder)
cd
cd -
cd workspace/Cs100/rshell (after cd -)
cd - (after cd src)
cd (after cd)
touch test (after cd src/testfolder/testfolder2)
cd (after cd-)
cd src ; cd testfolder ; cd testfolder2
cd path/that/doesnt/exist
cd testfolder ; cd path/that/doesnt/exist