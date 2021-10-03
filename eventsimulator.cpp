#include "eventsimulator.hpp"

EventSimulator::EventSimulator() {
    mu = 2;
    lambda = 3;
    totalEvents = 100;
    totalServers = 4;
    availableServers = 4;
    customerWaitedCnt = 0;
    totalWaitTime = 0;
    serviceTime = 0;
    idleTime = 0;
    timeOfLastDeparture = 0;
    nextArrivalTime = 0;
    totalSimTime = 0;
}

EventSimulator::EventSimulator(int mu, int lambda, int totalEvents, int totalServers) {
    this->mu = 2;
    this->lambda = 3;
    this->totalEvents = 100;
    this->totalServers = 4;
    availableServers = 4;
    customerWaitedCnt = 0;
    totalWaitTime = 0;
    serviceTime = 0;
    idleTime = 0;
    timeOfLastDeparture = 0;
    nextArrivalTime = 0;
    totalSimTime = 0;
}

void EventSimulator::processEvents() {
    PQ.ConstructHeap(14);
    while (!PQ.IsEmpty()) {
        processNextEvent();
        // add arrivals
/*         if ((totalEvents > 0) && PQ.heapSize <= availableServers+1) {
            PQ.InsertCustomers();
        } */
    }
   std::cout << "Total time: " << timeOfLastDeparture;
}

void EventSimulator::processStatistics(Customer processCustomer) {
    //std::cout << "results here.\n";
    /*  if(currentWaitTime > 0) 
      increment customerWaitedCnt 
   totalWaitTime = totalWaitTime + currentWaitTime 
   accumulate serviceTime 
   if(serverAvailableCnt == M) 
      accumulate idleTime  */
}

void EventSimulator::processNextEvent() {
    Customer currCustomer;
    //std::cout << "test\n";
    currCustomer = PQ.DeleteMin(); // take out of PQ
    if(currCustomer.isDeparture == false) {
        //currCustomer = PQ.DeleteMin();
        if(availableServers > 0) {
            availableServers--;
            currCustomer.startOfServiceTime = currCustomer.arrivalTime; 
            currCustomer.departureTime = currCustomer.arrivalTime + PQ.GetNextRandomInterval(mu);
            timeOfLastDeparture = currCustomer.departureTime; // noting time departure
            currCustomer.isDeparture = true;
            PQ.PercolateUp(currCustomer);  //place departureEvent in PQ 
        } else {
            PQ.PercolateUp(currCustomer); // add back to add to fifo
            //FIFO.Enqueue(currCustomer);// not working, PQ next customer only enqueues the head, must enqueue currcustomer
        } 
    } else { // processing a departure event 
      availableServers++;
     // currCustomer = PQ.DeleteMin();
      processStatistics(currCustomer); 
      if(!FIFO.IsEmpty()) {
        FIFO.Dequeue();//remove Customer from FIFO 
       // currCustomer = PQ.DeleteMin();
        currCustomer.startOfServiceTime = timeOfLastDeparture;
        currCustomer.departureTime = currCustomer.startOfServiceTime + PQ.GetNextRandomInterval(mu);
        timeOfLastDeparture = currCustomer.departureTime; // noting time departure
        currCustomer.isDeparture = true;
        PQ.PercolateUp(currCustomer);
        availableServers--;
        }
    }
}