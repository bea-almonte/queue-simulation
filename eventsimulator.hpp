#include "heap.hpp"
#include "queue.hpp"
#include "customer.hpp"
#include <iostream>
#include <math.h>

#ifndef EVENTSIMULATOR_HPP
#define EVENTSIMULATOR_HPP

class EventSimulator {
    private: 
        Heap PQ; // priority queue
        Queue FIFO; // Fifo for waiting customers
        float mu;
        float lambda;
        int totalEvents;
        int totalServers;
        int availableServers;
        // stats
        int customerWaitedCnt;
        int totalCounted;
        float totalWaitTime;
        float serviceTime;
        float idleTime; //timeoflastdeparture + nextarrivaltime
        float timeOfLastDeparture;
        float nextArrivalTime;
        float totalSimTime;
        float currentWaitTime;

        float factorial(float n);
    public:

        // functions
        EventSimulator();
        EventSimulator(float lambda, float mu, int totalServers, int totalEvents);
        void processEvents();
        void processStatistics(Customer processCustomer);
        void processNextEvent();
        void analyticalModel();
};

#endif