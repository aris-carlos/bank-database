project_debug: llist.o user_interface.o
	g++ -o project_debug llist.o user_interface.o
llist.o: llist.cpp
	g++ -ansi -pedantic-errors -Wall -c -DDEBUG llist.cpp
user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -c -DDEBUG user_interface.cpp
