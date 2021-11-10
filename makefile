project4.x: main.o knapsack.o max_heap.o file_reader.o
	g++ -ggdb -o project4.x main.o knapsack.o max_heap.o file_reader.o

file_reader.o: file_reader.cpp
	g++ -std=c++17 -ggdb file_reader.cpp -o file_reader.o -c

main.o: main.cpp knapsack.h max_heap.h file_reader.h
	g++ -std=c++17 -ggdb main.cpp -o main.o -c

knapsack.o: knapsack.cpp
	g++ -std=c++17 -ggdb knapsack.cpp -o knapsack.o -c

max_heap.o: max_heap.cpp
	g++ -std=c++17 -ggdb max_heap.cpp -o max_heap.o -c

clean:
	/bin/rm -f project4.x *.o *~
