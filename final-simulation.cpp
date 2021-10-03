#include <iostream>
#include <time.h>
#include <random>
#include "customer.hpp"
#include "queue.hpp"
#include "heap.hpp"

int main() {
    Customer test;
    Heap customers;
    srand(6);
    float testnum = 1.5;
    customers.ConstructHeap(25);
    test.arrivalTime = testnum;

    

//    customers.InsertCustomers();
for (int i = 1; i <= 15; i++) {
        test.arrivalTime = testnum + static_cast<float>(i);
        customers.PercolateUp(test);
    }
    //std::cout << "\n" << customers.heapSize;
    int total = 0;
        for (int i = 1; i <= 20; i++) {
        customers.DeleteMin();
    }
   
    
    std::cout << "\ntotal " << total << std::endl;
    for (int i = 1; i < 20; i++) {
        std::cout << customers.events[i].arrivalTime << " ";
    }
    std::cout << "\ntotal " << total << std::endl;
    return 0;
}