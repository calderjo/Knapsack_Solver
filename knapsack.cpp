//
// Created by Hugh on 4/30/21.
//

#include "knapsack.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>


////////////////////////////////// Task 1a //////////////////////////////////
void Knapsack::traditional_approach(){
    allClear();
    findOptimalValue_t();
    findOptimalSubset(recordingMatrix.size() - 1, recordingMatrix[0].size() - 1 );
    print_traditional_approach_details();
}

void Knapsack::findOptimalValue_t() {
    recordingMatrix.resize( values.size() + 1 );

    for( auto & each : recordingMatrix )
        each.resize( capacity + 1, 0 );

    for( int i = 0; i < recordingMatrix.size(); i++ ) {
        for (int j = 0; j < recordingMatrix[0].size(); j++) {
            if( i == 0 || j == 0) {
                recordingMatrix[i][j] = 0;
            }
        }
    }
    for(int i = 1; i < recordingMatrix.size(); i++) { // we will count the filling of inner non base case boxes in table
        for( int j = 1; j < recordingMatrix[0].size(); j++ ) {
            basicOps += 1;
            if( i == 0 || j == 0) {
                recordingMatrix[i][j] = 0;
            }
            else {
                if( j - weights[i - 1] >= 0 ) {
                    recordingMatrix[i][j] =
                            std::max(recordingMatrix[i-1][j], values[i-1] + recordingMatrix[i- 1][j-weights[i-1]]);
                }
                else
                    recordingMatrix[i][j] = recordingMatrix[i-1][j];
            }
        }
    }
    optValue = recordingMatrix[recordingMatrix.size() - 1] [recordingMatrix[0].size() - 1];
}

void Knapsack::findOptimalSubset( int i, int j ) {
    basicOps += 1;
    if( i == 0 )
        return;
    if( recordingMatrix[i][j] > recordingMatrix[ i - 1 ][j] ) {
        optPath.push_back(i);
        int remWeight = j - weights[i - 1];
        findOptimalSubset( i - 1, remWeight );
    }
    else
        findOptimalSubset( i - 1, j );
}


void Knapsack::print_traditional_approach_details() {
    std::cout << "(1a) Traditional Dynamic Programming Optimal value: " << optValue << std::endl;
    std::cout << "(1a) Traditional Dynamic Programming Optimal subset: {";

    sort( optPath.begin(), optPath.end() );
    for( int i = 0; i < optPath.size()-1; ++i)
        std::cout << optPath.at(i) << " ";
    std::cout << optPath.at(optPath.size()-1) << "}" << std::endl;

    std::cout << "(1a) Traditional Dynamic Programming Total Basic Ops: " << basicOps << std::endl;
    std::cout << std::endl;
}


////////////////////////////////// Task 1b //////////////////////////////////
void Knapsack::memory_function_approach() {
    allClear();
    create_mF_table();
    optimalValue_MF();
    findOptimalSubset(recordingMatrix.size() - 1, recordingMatrix[0].size() - 1);
    print_memoryFunction_details();
}


void Knapsack::create_mF_table() {
    recordingMatrix.resize(weights.size() + 1);
    for( int i = 0; i < weights.size() + 1; i++ ) {
        recordingMatrix[i].push_back(0);
    }
    for( int j = 1; j < capacity + 1; j++ ) {
        recordingMatrix[0].push_back(0);
    }
    for( int i = 1; i < weights.size() + 1; i++ ) {
        for( int j = 1; j < capacity + 1; j++ ) {
            recordingMatrix[i].push_back(-1);
        }
    }
}

void Knapsack::optimalValue_MF() {
    int i = recordingMatrix.size() - 1;
    int j = recordingMatrix[0].size() - 1;
    findOptimalValue_MF( i, j );
    optValue = recordingMatrix[i][j];
}

int Knapsack::findOptimalValue_MF( int i, int j ) {
    basicOps++;
    if(recordingMatrix[i][j] < 0) {
        int value;
        if( j < weights[i - 1] )
            value = findOptimalValue_MF( i - 1,j);
        else {
            value = std::max(findOptimalValue_MF(i-1,j),
                         values[i - 1] + findOptimalValue_MF( i - 1, j - weights[i - 1] ) );
        }
        recordingMatrix[i][j] = value;
    }
    return recordingMatrix[i][j];
}


void Knapsack::print_memoryFunction_details() {
    std::cout << "(1b) Memory-function Dynamic Programming Optimal value: " << optValue << std::endl;
    std::cout << "(1b) Memory-function Dynamic Programming Optimal subset: {";

    sort( optPath.begin(), optPath.end() );
    for( int i = 0; i < optPath.size()-1; ++i)
        std::cout << optPath.at(i) << " ";
    std::cout << optPath.at(optPath.size()-1) << "}" << std::endl;

    std::cout << "(1b) Memory-function Dynamic Programming Total Basic Ops: " << basicOps << std::endl;
    std::cout << std::endl;
}

////////////////////////////////// Task 2a //////////////////////////////////
void Knapsack::greedy_approach() {
    basicOpsGreedy = 0;
    computeRatio();
    sortRatio();
    getOptimal_value_and_set();
    print2a();
}

void Knapsack::computeRatio() {
    value_to_weight_ratios.clear();
    for( int i = 0; i < values.size(); i++ ) {
        basicOpsGreedy++;
        double a = values[i];
        double b = weights[i];
        double ratio =  a / b;
        value_to_weight_ratios.emplace_back(i+1, ratio);
        indices.push_back(i);
    }
}

void Knapsack::sortRatio() {
    mergeSort(0, int(value_to_weight_ratios.size()) - 1 );
}

void Knapsack::mergeSort(int left, int right) {
    if( right - left <= 0 ) {
        return;
    }
    int mid = left + ( right - left ) / 2;
    mergeSort( left, mid );
    mergeSort( mid + 1, right );
    merge( left, mid, right );
}

void Knapsack::merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create two vectors
    std::vector<std::tuple<int, double>> L, R;
    // For the indices vector
    std::vector<int> L2, R2;

    for( int i = 0; i < n1; i++ ) {
        L.push_back(value_to_weight_ratios[left + i]);
        L2.push_back(indices[ left + i ]);
    }
    for( int j = 0; j < n2; j++ ) {
        R.push_back(value_to_weight_ratios[mid +1+j]);
        R2.push_back(indices[mid+1+j]);
    }

    // Merge
    int i = 0;
    int j = 0;
    int k = left;
    while( i < n1 && j < n2 ) {
        basicOpsGreedy++;
        if(std::get<1>(L[i]) >= std::get<1>(R[j])) {
            value_to_weight_ratios[k] = L[i];
            indices[k] = L2[i];
            i++;
        }
        else {
            value_to_weight_ratios[k] = R[j];
            indices[k] = R2[j];
            j++;
        }
        k++;
    }
    // Basic operation is the condition check for each iteration of the two while loops.
    while ( i < n1 ) {
        value_to_weight_ratios[k] = L[i];
        indices[k] = L2[i];
        i++;
        k++;
    }
    while( j < n2 ) {
        value_to_weight_ratios[k] = R[j];
        indices[k] = R2[j];
        j++;
        k++;
    }
}

void Knapsack::getOptimal_value_and_set() {
    int current_capacity = capacity;
    optValueGreedy = 0;
    for (auto & value_to_weight_ratio : value_to_weight_ratios){
        basicOpsGreedy++;
        int currentW = weights.at(std::get<0>(value_to_weight_ratio)-1);
        if (current_capacity - currentW < 0){
            break;
        }
        else{
            current_capacity -= currentW;
            optValueGreedy += values.at(std::get<0>(value_to_weight_ratio) - 1);
            optPathGreedy.push_back(std::get<0>(value_to_weight_ratio));
        }
    }
}

void Knapsack::print2a() {
    std::cout << "(2a) Greedy Approach Optimal value: " << optValueGreedy << std::endl;
    std::cout << "(2a) Greedy Approach Optimal subset: {";

    std::sort( optPathGreedy.begin(), optPathGreedy.end() );
    for( int i = 0; i < optPathGreedy.size()-1; ++i)
        std::cout << optPathGreedy.at(i) << " ";
    std::cout << optPathGreedy.at(optPathGreedy.size()-1) << "}" << std::endl;

    std::cout << "(2a) Greedy Approach Total Basic Ops: " << basicOpsGreedy << std::endl;
    std::cout << std::endl;
}

void Knapsack::allClear() {
    recordingMatrix.clear();
    basicOps = 0;
    optPath.clear();
}

