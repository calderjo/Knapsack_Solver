//
// Created by Jonathan Calderon Chavez on 5/14/21.
//

#include "file_reader.h"


void file_reader::readData(
        const std::string& capacityFileName,
        const std::string& valueFileName,
        const std::string& weightFileName) {

    // takes in 3 file names, and will open those files
    // capacityFileName must contain a single number, and valueFileName and weightFileName must
    // contain the same number of values

    std::fstream dataFile1; // open file 1 which contains the capacity of the knapsack
    dataFile1.open("KnapsackTestData/" + capacityFileName, std::ios_base::in);

    if( ! dataFile1.is_open()) {  // exit if file does not exist
        std::cout << "Unable to open input file ->" << capacityFileName << "<-\n";
        exit(2);
    }
    dataFile1 >> capacity; // reads in the knapsack
    dataFile1.close();

    std::fstream dataFile2; // open file 2 which contains the value of all n items
    dataFile2.open("KnapsackTestData/" + valueFileName, std::ios_base::in );
    if( ! dataFile2.is_open()) {
        std::cout << "Unable to open input file ->" << valueFileName << "<-\n";
        exit(2);
    }

    int value; // parsing file for values
    while( dataFile2 >> value )
        values.push_back(value);
    dataFile2.close();

    std::fstream dataFile3; // open file 3 which contains the value of all n items
    dataFile3.open( "KnapsackTestData/" + weightFileName, std::ios_base::in );
    if( ! dataFile3.is_open()) {
        std::cout << "Unable to open input file ->" << weightFileName << "<-\n";
        exit(2);
    }

    int weight; // parsing file for weights
    while( dataFile3 >> weight )
        weights.push_back(weight);
    dataFile3.close();
}

file_reader::file_reader() {
    capacity =0;
    values.clear();
    weights.clear();
}
