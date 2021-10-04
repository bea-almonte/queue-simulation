#include "eventsimulator.hpp"

EventSimulator::EventSimulator() {
    mu = 3;
    lambda = 2;
    totalEvents = 5000;
    totalServers = 2;
    availableServers = totalServers;
    customerWaitedCnt = 0;
    totalWaitTime = 0;
    serviceTime = 0;
    idleTime = 0;
    timeOfLastDeparture = 0;
    nextArrivalTime = 0;
    totalSimTime = 0;
    currentWaitTime = 0;
    PQ = Heap(lambda, mu, totalEvents);
}

EventSimulator::EventSimulator(int lambda, int mu, int totalServers, int totalEvents) {
    this->mu = mu;
    this->lambda = lambda;
    this->totalEvents = totalEvents;
    this->totalServers = totalServers;
    availableServers = totalServers;
    // stats
    customerWaitedCnt = 0;
    totalWaitTime = 0;
    serviceTime = 0;
    idleTime = 0;
    timeOfLastDeparture = 0;
    nextArrivalTime = 0;
    totalSimTime = 0;
    currentWaitTime = 0; 
    totalCounted = 0;
    PQ = Heap(lambda, mu, totalEvents);
}

void EventSimulator::processEvents() {
    std::cout << "Total Events: " << totalEvents;

    PQ.ConstructHeap(10);
    while (!PQ.IsEmpty()) {
        processNextEvent();
        // add arrivals
        if ((PQ.totalEvents > 0) && PQ.heapSize <= totalServers+1) {
            PQ.InsertCustomers();
        }
    }
   std::cout << "\nTotal time: " << timeOfLastDeparture;
   std::cout << "\nTotal Wait Time: " << totalWaitTime;
   std::cout << "\nCustomer Waited: " << customerWaitedCnt;
   std::cout << "\nIdle Time: " << idleTime;
   std::cout << "\nTotal Service Time: " << totalCounted;
}

void EventSimulator::processStatistics(Customer processCustomer) {
    currentWaitTime = processCustomer.startOfServiceTime - processCustomer.arrivalTime;
    
    if(currentWaitTime > 0.00) {
        customerWaitedCnt++;
        totalWaitTime += currentWaitTime;
    }

    
    serviceTime += (processCustomer.departureTime - processCustomer.startOfServiceTime);
    if(availableServers == totalServers) {

        idleTime += (timeOfLastDeparture - processCustomer.arrivalTime);
    } 
}

void EventSimulator::processNextEvent() {
    Customer currCustomer;
    //std::cout << "test\n";
    currCustomer = PQ.DeleteMin(); // take out of PQ
    if(currCustomer.isDeparture == false) {

        if(availableServers > 0) {
            availableServers--;
            currCustomer.startOfServiceTime = currCustomer.arrivalTime; 
            currCustomer.departureTime = currCustomer.arrivalTime + PQ.GetNextRandomInterval(mu);
            timeOfLastDeparture = currCustomer.departureTime; // noting time departure
            currCustomer.isDeparture = true;
            PQ.PercolateUp(currCustomer);  //place departureEvent in PQ 
        } else {
            // add back to add to fifo
//            currCustomer.isDeparture = true;
            FIFO.Enqueue(PQ.PercolateUp(currCustomer));
        } 
    } else { // processing a departure event
        totalCounted++;
        availableServers++;
        processStatistics(currCustomer); 

        if(!FIFO.IsEmpty()) {
            FIFO.Dequeue();//remove Customer from FIFO 
            currCustomer = PQ.DeleteMin();
            currCustomer.startOfServiceTime = timeOfLastDeparture;
            currCustomer.departureTime = currCustomer.startOfServiceTime + PQ.GetNextRandomInterval(mu);
            timeOfLastDeparture = currCustomer.departureTime; // noting time departure
            currCustomer.isDeparture = true;
            PQ.PercolateUp(currCustomer);
            availableServers--;
        }
    }
}