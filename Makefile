all: dijkstra

clean:
        -rm dijkstra.o dijkstra

dijkstra: dijkstra.o
        g++ -g -std=c++11 -o dijkstra dijkstra.o

dijkstra.o: dijkstra.cpp
        g++ -c -std=c++11 -g dijkstra.cpp

