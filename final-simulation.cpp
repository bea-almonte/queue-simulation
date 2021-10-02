#include <iostream>
#include <time.h>
#include "customer.hpp"
#include "queue.hpp"
#include "heap.hpp"

int main() {
    Customer test;
    Heap customers;
    Queue line;
    srand(time(NULL));

    customers.BuildHeap();
    test.arrivalTime = 1.5;
    for (int i = 1; i < 11; i++) {
        std::cout << customers.events[i].arrivalTime << " ";
    }
    customers.PercolateUp(test);
    std::cout << std::endl;
    for (int i = 1; i < 12; i++) {
        std::cout << customers.events[i].arrivalTime << " ";
    }

    std::cout << std::endl;
    customers.DeleteMin();
    customers.DeleteMin();
    customers.DeleteMin();
    for (int i = 1; i < 9; i++) {
        std::cout << customers.events[i].arrivalTime << " ";
    }
    return 0;
}