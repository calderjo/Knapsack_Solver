//
// Created by Hugh on 4/30/21.
//

#ifndef PROJECT_4_KNAPSACK_H
#define PROJECT_4_KNAPSACK_H
#include <utility>
#include <vector>
#include <iostream>
#include <tuple>

class Knapsack {
public:
    Knapsack(int capacityFileName, std::vector<int> valueFileName, std::vector<int> weightFileName){
        this -> capacity = capacityFileName;
        this -> values  = std::move(valueFileName);
        this -> weights = std::move(weightFileName);
    }

    void traditional_approach();
    void memory_function_approach();
    void greedy_approach();


    std::vector<int> get_indices() { return indices; };

    int getCapacity() { return capacity; }
    std::vector<int> getValues() { return values; }
    std::vector<int> getWeights() { return weights; }

private:
    void findOptimalValue_t();
    void print_traditional_approach_details();

    void create_mF_table();
    void optimalValue_MF();
    int findOptimalValue_MF( int i, int j );
    void print_memoryFunction_details();


    void findOptimalSubset(int i, int j);

    void mergeSort( int left, int right );
    void merge( int left, int mid, int right );
    void computeRatio();
    void sortRatio();
    void getOptimal_value_and_set();
    void print2a();


    void allClear();

    int capacity;
    std::vector<int> values;
    std::vector<int> weights;

    std::vector<std::vector<int>> recordingMatrix;
    std::vector<int> optPath;
    int optValue;
    int basicOps;

    std::vector<std::tuple<int, double>> value_to_weight_ratios;
    std::vector<int> optPathGreedy;
    // An inverted list for the values and weights vectors
    std::vector<int> indices;
    int optValueGreedy = 0;
    int basicOpsGreedy = 0;
};


#endif //PROJECT_4_KNAPSACK_H
