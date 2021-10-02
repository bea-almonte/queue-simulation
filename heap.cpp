#include "heap.hpp"

float Heap::GetNextRandomInterval() {
    //Generate a random float f on the interval (0..1]
    float randFloat;
    float intervalTime;

    randFloat = float(rand()) / (float(RAND_MAX) + 1.0);
    
    //Compute intervalTime as -1 * (1.0/avg) * ln(f) // natural logarithm of f
    intervalTime = -1 * (1.0/2) * log(randFloat);
    return intervalTime;
}
/*
left child = i *2
right child = i * 2 + 1
parent = i / 2
*/
void Heap::PercolateUp(Customer newCustomer) {
    // place item at top of heap
    // move items down until place to insert is found
    events[0] = newCustomer;
    int i = 11;
    // while arrival time is less than the parent
    while (newCustomer.arrivalTime < events[i/2].arrivalTime) {
        // switch
        events[i] = events[i/2];

        i /= 2;
    }

    events[i] = newCustomer;
}

void Heap::PercolateDown(Customer newCustomer) {
    //int child;
    int i;
    //float temp = events[i].arrivalTime;

    // while left child < size
    while ((i*2) <= 12) {
        i = i*2;
    }
}

void Heap::BuildHeap() {
    for (int i = 1; i < 11; i++) {
        events[i].arrivalTime = i;
    }
}