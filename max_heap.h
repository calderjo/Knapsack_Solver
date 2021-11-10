//
// Created by Hugh on 5/14/21.
//
//

#ifndef PROJECT_4_MAX_HEAP1_H
#define PROJECT_4_MAX_HEAP1_H
#include <vector>
#include <tuple>

class Max_Heap{
public:
    Max_Heap(std::vector<int> v, std::vector<int> w, int capacity);

    void task2b();

    bool isLeaf( int pos );
    int leftChild( int pos );
    int rightChild( int pos );
    int parent( int pos );
    void insert( int key );
    void buildHeap();
    void siftDown( int pos );
    void removeMax();
    int removeMaxHelper(int curWeight);
    void print2b();
    void bottomUp();
private:
    std::vector<std::tuple<double, int, int, int>> heap;
    std::vector<int> optPathGreedyHeap;

    int numBasicOpt2 = 0;
    int numBasicOpt = 0;
    int optValueGreedyHeap = 0;
    int size = 0;
    int n = 0;
    int capacity = 0;
};


#endif //PROJECT_4_MAX_HEAP1_H
