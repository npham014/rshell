#All tests in this file were done by hand

test test.txt
test -e test.txt
test -f test.txt
test -d test.txt
test filethatdoesntexist
test -e filethatdoesntexist
test -f filethatdoesntexist
test -d filethatdoesntexist
test src/test.o
test -e src/test.o
test -f src/test.o
test -d src/test.o
test src/filethatdoesntexist
test -e src/filethatdoesntexist
test -f src/filethatdoesntexist
test -d src/filethatdoesntexist
test src
test -e src
test -f src
test -d src
test src/folderthatdoesntexist/filethatdoesntexist
test -e src/folderthatdoesntexist/filethatdoesntexist
test -f src/folderthatdoesntexist/filethatdoesntexist
test -d src/folderthatdoesntexist/filethatdoesntexist