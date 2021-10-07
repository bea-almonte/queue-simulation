/* Heap is the priority queue.
Contains events (customers) that will be sorted by their arrival/departure time
*/
#include <math.h> // pow()
#include <random> // rand()
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
        void PercolateDown(int i); // hole
        Customer* PercolateUp(Customer newCustomer);
        Customer DeleteMin(); // returns top and removes customer from PQ
        Customer* NextCustomer(); // returns top
        float GetNextRandomInterval(int avg); // returns random interval (0,1]
        bool IsEmpty();

        int heapSize;
        int totalEvents = 5000;
};


#endif