#include <iostream>
#include <time.h>
#include "customer.hpp"
#include "queue.hpp"
#include "heap.hpp"

int main() {
    Customer heap[5];
    Heap customers;
    Queue line;
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        heap[i].arrivalTime = i;
        line.Enqueue(&heap[i]);
    }

    for (int i = 0; i < 5; i++) {
        std::cout << line.Dequeue()->arrivalTime << std::endl;
    }

    for (int i = 0; i < 20; i++) {
        std::cout << customers.GetNextRandomInterval() << " ";
        
    }
    return 0;
}