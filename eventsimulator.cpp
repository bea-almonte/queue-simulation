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

EventSimulator::EventSimulator(float lambda, float mu, int totalServers, int totalEvents) {
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

    PQ.ConstructHeap(200);
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
   std::cout << "\nIdle Time: " << idleTime/timeOfLastDeparture;
   std::cout << "\nTotal Service Time: " << totalCounted;
}

void EventSimulator::processStatistics(Customer processCustomer) {
    currentWaitTime = processCustomer.startOfServiceTime - processCustomer.arrivalTime;
    
    if(currentWaitTime > 0.00) {
        customerWaitedCnt++;
        totalWaitTime += currentWaitTime;

    }

    totalSimTime += (processCustomer.departureTime - processCustomer.arrivalTime);
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
        totalCounted++;
        if(availableServers > 0) {
            availableServers--;
            currCustomer.startOfServiceTime = currCustomer.arrivalTime; 
            currCustomer.departureTime = currCustomer.arrivalTime + PQ.GetNextRandomInterval(mu);
            timeOfLastDeparture = currCustomer.departureTime; // noting time departure
            currCustomer.isDeparture = true;
            PQ.PercolateUp(currCustomer);  //place departureEvent in PQ 
        } else {
            FIFO.Enqueue(currCustomer); // remove customer from pq
        } 
    } else { // processing a departure event
        availableServers++;
        processStatistics(currCustomer); 

        if(!FIFO.IsEmpty()) {
            //remove Customer from FIFO 
            currCustomer = FIFO.Dequeue();
            currCustomer.startOfServiceTime = timeOfLastDeparture;
            currCustomer.departureTime = currCustomer.startOfServiceTime + PQ.GetNextRandomInterval(mu);
            timeOfLastDeparture = currCustomer.departureTime; // noting time departure
            currCustomer.isDeparture = true;
            PQ.PercolateUp(currCustomer);
            availableServers--;
        }
    }
}

void EventSimulator::analyticalModel() {
    float Po = 0; // percent idle time = idletime/totaltime
    float L = 0; // avg num of people in system (numberinline +numberbeing served)
    float W = 0; // avg time a customer spends in the system, spent in line plus getting service
    float Lq = 0; // avg number of customers in the queue;
    float Wq = 0; // avg time a customer spends waiting in the queue;
    float rho = 0; // utilization factor for system, proportion of system's resources ??

    float M = totalServers;
    float avgRatio = 0; // ratio of lambda/mu
    float denom1 = 0;
    float denom2 = 0;
    float num1 = 0; // numerator

    avgRatio = lambda / mu;

    // CALCULATING Po PERCENTAGE IDLE TIME
    for (int i = 0; i < M; i++) {
        denom1 += (1.0/factorial(i)) * pow(avgRatio,static_cast<float>(i));
    }
    
    denom2 = (1.0/factorial(M)) * pow(avgRatio,M) * ((M*mu)/((M*mu)-lambda));
    Po = (1.0/(denom1 + denom2));

    // CALCULATING L = AVG NUMBER OF PEOPLE IN SYSTEM
    num1 = (lambda * mu) * pow(avgRatio,M);
    denom1 = factorial(M - 1);
    denom2 = pow((M * mu) - lambda,2);

    L = ((num1) / (denom1 * denom2)) * Po + avgRatio;
    
    // CALCULATING AVG TIME IN SYSTEM
    W = L / lambda;

    // CALCULATE AVG NUMBER OF CUSTOMERS IN QUEUE
    Lq = L - avgRatio;

    // CALCULATING AVG TIME SPENT IN QUEUE
    Wq = Lq / lambda;

    // CALCULATING UTILIZATION FACTOR
    rho = avgRatio * M;

    // OUTPUT MODEL
    std::cout << "\nPo = " << Po;
    std::cout << "\nL = " << L;
    std::cout << "\nW = " << W;
    std::cout << "\nLq = " << Lq;
    std::cout << "\nWq = " << Wq;
}

float EventSimulator::factorial(float n) {
    return (n==1 || n == 0) ? 1 : factorial(n-1) * n;
}