#include "heap.hpp"
#include "queue.hpp"
#include "customer.hpp"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>

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
        // stat finals
        float simPo;
        float simW;
        float simWq;
        float simRho;
        float factorial(float n);
        void simulationStatistics();
        float calcPercentError(float theoretical, float experimental);
        void printFormattedStats(float theoretical, float experimental, std::string label);
        void printFormattedStats(float theoretical, std::string label);
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