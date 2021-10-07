// heap.cpp -- function definitions of heap class

#include "heap.hpp"

Heap::Heap() {
    heapSize = 0;
    currentTime = 0;

    lambda = 2;
    mu = 3;
    totalEvents = 5000;
}

Heap::Heap(float lambda, float mu, int totalEvents) {
    heapSize = 0;
    currentTime = 0;
    
    this-> lambda = lambda;
    this->mu = mu;
    this->totalEvents = totalEvents;
}

// This function generates a random interval depending on the avg (lambda/mu)
float Heap::GetNextRandomInterval(int avg) {
    
    float randFloat;
    float intervalTime;
 
    // Generate a random float f on the interval (0..1]
    randFloat = float(rand()) / (float(RAND_MAX) + 1.0);
    
    //Compute intervalTime as -1 * (1.0/avg) * ln(f) // natural logarithm of f
    intervalTime = -1.0 * (1.0/avg) * log(randFloat);
    return intervalTime;
}

/*
left child = i *2
right child = i * 2 + 1
parent = i / 2
*/
Customer* Heap::PercolateUp(Customer newCustomer) {
    // place item at top of heap
    // move items down until place to insert is found
    events[0] = newCustomer;

    // increase heapsize and index at end of heap / new node
    int i = ++heapSize;
    // while arrival time is less than the parent
    // since equal, reassigns same to heapsize +1
    while (newCustomer.GetEventTime() < events[i/2].GetEventTime()) {
        // create hole
        events[i] = events[i/2];
        i /= 2;
    }

    events[i] = newCustomer;

    return &events[i];
}

// delete elements
Customer Heap::DeleteMin() {
    // return top element
    events[0] = events[1];
    // replace top with last elemnt
    events[1] = events[heapSize--];
    // set last node
    PercolateDown(1);

    // reinitialize element outside of heap
    events[heapSize+1] = Customer();
    

    return events[0];
}

void Heap::PercolateDown(int i) {
    int child;
    Customer temp = events[i]; // hole is now at top

    // while left child < size
    // start at bottom
    while ((i*2) <= heapSize) {
        child = i*2;
        // if child is not at the end and right child is less than left
        if (child != heapSize && (events[child+1].GetEventTime() < events[child].GetEventTime())) {
            // choose right child if > 0
            if (events[child].arrivalTime != 0) {
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

    events[i] = temp; // set hole to temp
}

// inserts customers up to heap size and total events
void Heap::InsertCustomers() {

    // while events aren't finish and heap isn't full...
    while (totalEvents != 0 && heapSize < 200) {
        totalEvents--;
        currentTime += GetNextRandomInterval(lambda);
        // for departures left in PQ
        while (events[heapSize].isDeparture) {
            totalEvents--;
            heapSize++;
        }
        // assign last node to new arrival
        events[heapSize].arrivalTime = currentTime;

        // increases heapsize
        PercolateUp(events[heapSize]);
    }
}

// construct initial heap size (no percolating needed)
void Heap::ConstructHeap(int initialSize) {
    totalEvents -= initialSize;

    this->heapSize = initialSize;

    for (int i = 1; i <= heapSize; i++) {
        currentTime += GetNextRandomInterval(lambda);
        events[i].arrivalTime = currentTime;
    }
}

// returns the top of heap
Customer* Heap::NextCustomer() {
    return &events[1];
}

// checks if there are customers in priority queue
bool Heap::IsEmpty() {
    if (heapSize == 0) {
        return true;
    } else {
        return false;
    }
}
