#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include "knapsack.h"
#include "max_heap.h"
#include "file_reader.h"

int main(int argc, char *argv[]) {

    if( argc != 2 ) {  // argument checking
        std::cout << "usage: " << argv[0] << " inputFileNameThatContainsCapacity inputFileNameThatContainsValues inputFileNameThatContainsWeights\n";
        exit(1);
    }
    std::string input = argv[1];
    std::string prefix = "p";
    std::string capacityFileName;
    std::string weightFileName;
    std::string valueFileName;

    if( input.length() < 2 ) {  // finding out the name of file using the guidelines
        capacityFileName = prefix + "0" + input + "_c.txt";
        weightFileName = prefix + "0" + input + "_w.txt";
        valueFileName = prefix + "0" + input + "_v.txt";
    }
    else {
        capacityFileName = prefix + input + "_c.txt";
        weightFileName = prefix + input + "_w.txt";
        valueFileName = prefix + input + "_v.txt";
    }

    file_reader fReader;
    fReader.readData(capacityFileName, valueFileName, weightFileName);  // extract data from files

    std::cout << "File containing the capacity, weights, and values are: ";
    std::cout << capacityFileName << " " << weightFileName << " " << valueFileName << std::endl << std::endl;

    std::cout << "Knapsack capacity = " << fReader.getCapacity() << ".";
    std::cout << " Total number of items = " << fReader.getNumItems() << std::endl << std::endl ;

    Knapsack k(fReader.getCapacity(), fReader.getValues(), fReader.getWeights());
    k.traditional_approach();
    k.memory_function_approach();
    k.greedy_approach();

    ////////////////////////////////// Test For 2a/2b ////////////////////////////////
    Max_Heap h(fReader.getValues(), fReader.getWeights(), fReader.getCapacity());
    h.task2b();

    std::cout << std::endl;

    return 0;
}
