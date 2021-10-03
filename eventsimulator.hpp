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
        float totalWaitTime;
        float serviceTime;
        float idleTime; //timeoflastdeparture + nextarrivaltime
        float timeOfLastDeparture;
        float nextArrivalTime;
        int totalSimTime; // change later
        // functions
        EventSimulator();
        EventSimulator(int mu, int lambda, int totalEvents, int totalServers);
        void processEvents();
        void processStatistics(Customer processCustomer);
        void processNextEvent();
};

#endif