wumpus: main.o graph.o node.o
	g++ main.o graph.o node.o -o wumpus
main.o: main.cpp
	g++ -c -g -Wall -pedantic --std=c++11 main.cpp
graph.o: graph.cpp
	g++ -c -g -Wall -pedantic --std=c++11 graph.cpp
node.o: node.cpp
	g++ -c -g -Wall -pedantic --std=c++11 node.cpp
clean:
	rm *.o wumpus
