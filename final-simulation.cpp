#include <iostream>
#include "customer.hpp"
#include "queue.hpp"

int main() {
    Customer heap[5];
    Queue line;

    for (int i = 0; i < 5; i++) {
        heap[i].arrivalTime = i;
        line.Enqueue(&heap[i]);
    }

    for (int i = 0; i < 5; i++) {
        std::cout << line.Dequeue()->arrivalTime << std::endl;
    }

    return 0;
}