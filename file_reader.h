//
// Created by Jonathan Calderon Chavez on 5/14/21.
//

#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <fstream>

#ifndef PROJECT_4_FILE_READER_H
#define PROJECT_4_FILE_READER_H

class file_reader {
public:
    file_reader();
    void readData(const std::string& capacityFileName, const std::string& valueFileName, const std::string& weightFileName);
    int getCapacity() const {return capacity;};
    int getNumItems(){return values.size();};
    std::vector<int> getValues(){return values;};
    std::vector<int> getWeights(){return weights;};

private:
    int capacity;
    std::vector<int> values;
    std::vector<int> weights;
};


#endif //PROJECT_4_FILE_READER_H
