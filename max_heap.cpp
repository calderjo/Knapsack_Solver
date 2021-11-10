//
// Created by Hugh on 5/14/21.
//

#include "max_heap.h"
#include "knapsack.h"
#include <tuple>
#include <algorithm>

void Max_Heap::task2b() {
    numBasicOpt2 = 0;
    bottomUp();
    removeMax();
    numBasicOpt2 += numBasicOpt;
    print2b();
}

Max_Heap::Max_Heap(std::vector<int> v, std::vector<int> w, int capacity) {
    numBasicOpt = 0;
    std::vector<double> r;
    r.clear();
    heap.emplace_back(std::make_tuple(0, 0, 0, 0));
    for( int i = 0; i < v.size(); i++) {
        numBasicOpt++;
        double a = v[i];
        double b = w[i];
        double ratio = a/b;
        auto tuple = std::make_tuple(ratio, v[i], w[i], i+1);
        heap.emplace_back(tuple);
    }
    n = w.size();
    size = w.size();
    this->capacity = capacity;
}

void Max_Heap::bottomUp() {  // from textbook
    for(int i = (n / 2)  ; i != 0; i--) {
        int k = i;
        auto tuple = heap[k];
        bool h = false;
        while(!h && (2 * k <= n)){
            numBasicOpt2++;
            int j = 2 * k;
            if (j < n) {
                if (std::get<0>(heap[j]) < std::get<0>(heap[j + 1])) {
                    j++;
                }
            }
            if(std::get<0>(tuple) >= std::get<0>(heap[j])) {
                h = true;
            }
            else {
                heap[k] = heap[j];
                k = j;
            }
        }
        heap[k] = tuple;
    }
}

void Max_Heap::siftDown(int pos) {  // from open dsa
    if( ( pos < 1 ) || (pos >= n + 1) )
        return;
    while(!isLeaf(pos)) {
        numBasicOpt2++;
        int j = leftChild(pos);
        if(( j < ( n - 1 ) ) && std::get<0>( heap[j] ) < std::get<0>(heap[j+1] ))
            j++;
        if( std::get<0>(heap[pos]) >= std::get<0>(heap[j] ) )
            return;
        std::swap( heap[pos], heap[j] );
        pos = j;
    }
}

void Max_Heap::removeMax() {
    int curWeight = 0;
    int size = heap.size();
    while(size >= 0) {
        auto temp = removeMaxHelper(curWeight);
        if(temp == 0)
            return;
        curWeight += temp;
        size--;
    }
    print2b();
}

int Max_Heap::removeMaxHelper(int curWeight) {
    if(n == 0)
        return 0;
    auto max = heap[1];
    std::swap(heap[1], heap[heap.size() - 1]);
    heap.pop_back();
    size--;
    n--;
    siftDown(1);
    if(curWeight + std::get<2>(max) <= capacity) {
        optPathGreedyHeap.push_back(std::get<3>(max));
        optValueGreedyHeap += std::get<1>(max);
        return std::get<2>(max);
    }
    return 0;
}

void Max_Heap::print2b() {
    std::cout << "(2b) Heap-based Greedy Approach Optimal value: " << optValueGreedyHeap << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Optimal subset: {";
    sort( optPathGreedyHeap.begin(), optPathGreedyHeap.end() );
    for( int i = 0; i < optPathGreedyHeap.size()-1; ++i)
        std::cout << optPathGreedyHeap.at(i) << " ";
    std::cout << optPathGreedyHeap.at(optPathGreedyHeap.size()-1) << "}" << std::endl;
    std::cout << "(2b) Heap-based Greedy Approach Total Basic Ops: " << numBasicOpt2;
}

bool Max_Heap::isLeaf(int pos) {
    return (pos > n / 2) && (pos < n + 1);
}

int Max_Heap::leftChild(int pos) {
    if( pos > n / 2 )
        return -1;
    return 2 * pos;
}

int Max_Heap::rightChild(int pos) {
    if(pos > n / 2)
        return -1;
    return 2 * pos + 1;
}

int Max_Heap::parent(int pos) {
    if( pos <= 1 )
        return -1;
    return (pos) / 2;
}

