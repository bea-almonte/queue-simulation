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
    int i = ++heapSize;
    // while arrival time is less than the parent
    while (newCustomer.arrivalTime < events[i/2].arrivalTime) {
        // switch
        events[i] = events[i/2];

        i /= 2;
    }

    events[i] = newCustomer;
}

// delete elements
void Heap::DeleteMin() {
    // replace top with last elemnt
    events[1] = events[heapSize--];
    PercolateDown(1);
}

void Heap::PercolateDown(int i) {
    int child;
    Customer temp = events[i];

    // while left child < size
    while ((i*2) <= heapSize) {
        child = i*2;
        // if child is not at the end and right child is less than left
        if (child != heapSize && events[child+1].arrivalTime < events[child].arrivalTime) {
            child++;
        }
        if (events[child].arrivalTime < temp.arrivalTime){
            events[i] = events[child];
        } else {
            break;
        }
        i = child;
    }

    events[i] = temp;
}

void Heap::BuildHeap() {
    // 1- 10
    for (int i = 1; i <= heapSize; i++) {
        events[i].arrivalTime = i; // + GetNextRandomInterval();
    }
}