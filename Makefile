wumpus: main.o graph.o node.o
	g++ main.o graph.o node.o -o wumpus
main.o: main.cpp
	g++ -c -g main.cpp
graph.o: graph.cpp
	g++ -c -g graph.cpp
node.o: node.cpp
	g++ -c -g node.cpp
clean:
	rm *.o wumpus