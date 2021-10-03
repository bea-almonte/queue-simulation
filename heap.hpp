#include <math.h>
#include <random>
#include <iostream>
#include "queue.hpp"
#include "customer.hpp"
#ifndef HEAP_HPP
#define HEAP_HPP

class Heap {
    private:
        float currentTime; // keep track of ticks
        int mu = 3;
        int lambda = 2;
        
    public:
        Heap();
        bool IsEmpty();
        int eventsCreated = 0;
        Customer* NextCustomer(); // done
        void InsertCustomers(); // done
        void ConstructHeap(int initialSize); // first arrivals
        void PercolateDown(int i); // done
        Customer* PercolateUp(Customer newCustomer); // done
        Customer events[201];
        float GetNextRandomInterval(int avg); // done
        Customer DeleteMin(); // working
        int heapSize;
        int totalEvents = 5000;
};


#endif