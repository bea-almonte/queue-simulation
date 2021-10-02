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
    test.arrivalTime = 2.5;
    customers.PercolateUp(test);
    for (int i = 1; i < 12; i++) {
        std::cout << customers.events[i].arrivalTime << " ";
    }
    return 0;
}