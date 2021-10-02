#include <iostream>
#include <time.h>
#include <random>
#include "customer.hpp"
#include "queue.hpp"
#include "heap.hpp"

int main() {
    Customer test;
    Heap customers;
    srand(time(NULL));

    customers.ConstructHeap(199);
    test.arrivalTime = 1.5;
    for (int i = 1; i < 20; i++) {
        std::cout << customers.events[i].arrivalTime << " ";
    }
    customers.PercolateUp(test);
    std::cout << "\n" << customers.heapSize;
    std::cout << std::endl;
/*     for (int i = 1; i < customers.heapSize-1; i++) {
        std::cout << i << "=" << customers.events[i].arrivalTime << " ";
    }
 */
    std::cout << std::endl;
    customers.DeleteMin();
    customers.DeleteMin();
    customers.DeleteMin();
    for (int i = 1; i < 20; i++) {
        std::cout << i << "=" << customers.events[i].arrivalTime << " ";
    }
    std::cout << "\n" << customers.heapSize;
    return 0;
}