#include <math.h>
#include <random>
#include <iostream>
#include "queue.hpp"
#include "customer.hpp"
#ifndef HEAP_HPP
#define HEAP_HPP

class Heap {
    private:
        Customer events[201];
        float currentTime; // keep track of ticks
        float mu;
        float lambda;
    public:
        Heap();
        Heap(float lambda, float mu, int totalEvents);
        // heap functions
        void ConstructHeap(int initialSize); // first arrivals -- sets heap size
        void InsertCustomers(); // inserts customers until heap is full
        void PercolateDown(int i);
        Customer* PercolateUp(Customer newCustomer);
        Customer DeleteMin(); // working
        Customer* NextCustomer(); // done
        float GetNextRandomInterval(int avg);
        bool IsEmpty();

        int heapSize;
        int totalEvents = 5000;
};


#endif