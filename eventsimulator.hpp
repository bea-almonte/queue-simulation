#include "heap.hpp"
#include "queue.hpp"
#include "customer.hpp"
#include <iostream>

#ifndef EVENTSIMULATOR_HPP
#define EVENTSIMULATOR_HPP

class EventSimulator {
    public:
        Heap PQ; // priority queue
        Queue FIFO; // Fifo for waiting customers
        int mu;
        int lambda;
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
        // functions
        EventSimulator();
        EventSimulator(int lambda, int mu, int totalServers, int totalEvents);
        void processEvents();
        void processStatistics(Customer processCustomer);
        void processNextEvent();
};

#endif