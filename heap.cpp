#include "heap.hpp"

Heap::Heap() {
    heapSize = 0;
    currentTime = 0;
    mu = 3;
    lambda = 2;
    totalEvents = 600;
}


float Heap::GetNextRandomInterval(int avg) {
    //Generate a random float f on the interval (0..1]
    float randFloat;
    float intervalTime;
 
    randFloat = float(rand()) / (float(RAND_MAX) + 1.0);
    
    //Compute intervalTime as -1 * (1.0/avg) * ln(f) // natural logarithm of f
    intervalTime = -1 * (1.0/lambda) * log(randFloat);
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

    // increase heapsize and index at end of heap / new node
    int i = ++heapSize;
    // while arrival time is less than the parent
    while (newCustomer.GetEventTime() < events[i/2].GetEventTime()) {
        // create hole
        events[i] = events[i/2];

        i /= 2;
    }

    events[i] = newCustomer;
}

// delete elements
Customer Heap::DeleteMin() {
    // replace top with last elemnt
    events[0] = events[1];
    events[1] = events[heapSize--];
    // set last node
    PercolateDown(1);
    events[heapSize+1] = Customer();
    

    return events[0];
}

void Heap::PercolateDown(int i) {
    int child;
    Customer temp = events[i];

    // while left child < size
    // start at bottom
    while ((i*2) <= heapSize) {
        child = i*2;
        // if child is not at the end and right child is less than left
        if (child != heapSize && (events[child+1].GetEventTime() < events[child].GetEventTime())) {
            if (events[child].arrivalTime != 0){
                child++;
            }
        }
        if (events[child].GetEventTime() < temp.GetEventTime()){
            events[i] = events[child];
        } else {
            break;
        }
        i = child;
    }

    events[i] = temp;
}

void Heap::InsertCustomers() {

    while (heapSize < 20 && totalEvents != 0) {
        totalEvents--;
        //currentTime += GetNextRandomInterval(lambda);
        events[heapSize].arrivalTime = currentTime;
        // increases heapsize
        PercolateUp(events[heapSize]);
    }
}

void Heap::ConstructHeap(int initialSize) {
    // 1- 10
    totalEvents -= 200;
    this->heapSize = initialSize;
    // 1-200
    for (int i = 1; i <= heapSize; i++) {
        currentTime += GetNextRandomInterval(lambda);
        events[i].arrivalTime = currentTime;
    }
}

Customer* Heap::NextCustomer() {
    return &events[1];
}

bool Heap::IsEmpty() {
    if (heapSize == 0) {
        return true;
    } else {
        return false;
    }
}
