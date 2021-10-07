#include "eventsimulator.hpp"

EventSimulator::EventSimulator() {
    lambda = 2;
    mu = 3;
    totalServers = 2;
    totalEvents = 5000;
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
    
    PQ = Heap(lambda, mu, totalEvents);
}

EventSimulator::EventSimulator(float lambda, float mu, int totalServers, int totalEvents) {
    this->lambda = lambda;
    this->mu = mu;
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
    simulationStatistics();
    std::cout << std::endl;
}

void EventSimulator::processStatistics(Customer processCustomer) {
    currentWaitTime = processCustomer.startOfServiceTime - processCustomer.arrivalTime;

    if(currentWaitTime > 0.0) {
        customerWaitedCnt++;
        totalWaitTime += currentWaitTime;
    }

    serviceTime += (processCustomer.departureTime - processCustomer.startOfServiceTime);

    if(availableServers == totalServers) {
        if (PQ.NextCustomer()->arrivalTime != 0) { 
            idleTime += PQ.NextCustomer()->arrivalTime - processCustomer.departureTime;
        }
        
    } 
}

void EventSimulator::processNextEvent() {
    Customer currCustomer;

    currCustomer = PQ.DeleteMin(); // take out of PQ
    if(currCustomer.isDeparture == false) {
        // process arrivalss
        if(availableServers > 0) {
            availableServers--;
            currCustomer.startOfServiceTime = currCustomer.arrivalTime; 
            currCustomer.departureTime = currCustomer.arrivalTime + PQ.GetNextRandomInterval(mu);
            currCustomer.isDeparture = true;
            PQ.PercolateUp(currCustomer);  //place departureEvent in PQ 
        } else {
            FIFO.Enqueue(currCustomer); // add customer to fifo
        } 
    } else { // processing a departure event
        availableServers++;
        timeOfLastDeparture = currCustomer.departureTime; 
        processStatistics(currCustomer); 
        if(!FIFO.IsEmpty()) {
            //remove Customer from FIFO 
            currCustomer = FIFO.Dequeue();
            currCustomer.startOfServiceTime = timeOfLastDeparture;
            currCustomer.departureTime = currCustomer.startOfServiceTime + PQ.GetNextRandomInterval(mu);
            currCustomer.isDeparture = true;
            PQ.PercolateUp(currCustomer);
            availableServers--;
        }
    }
}

void EventSimulator::analyticalModel() {
    float Po = 0; // percent idle time = idletime/totaltime *
    float L = 0; // avg num of people in system (numberinline +numberbeing served)
    float W = 0; // avg time a customer spends in the system, spent in line plus getting service *
    float Lq = 0; // avg number of customers in the queue;
    float Wq = 0; // avg time a customer spends waiting in the queue; *
    float rho = 0; // utilization factor for system *

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
    rho = avgRatio / M;

    std::cout << std::endl;

    // output labels
    std::cout << std::setw(5) << " " << std::left
    << std::setw(12) << "Analytical" 
    << std::setw(12) << "Simulated" 
    << std::setw(12) << "% Error" 
    << std::endl;
    // output each compared values
    printFormattedStats(Po, simPo, "Po");
    printFormattedStats(L,"L");
    printFormattedStats(W, simW, "W");
    printFormattedStats(Lq,"Lq");
    printFormattedStats(Wq, simWq, "Wq");
    printFormattedStats(rho, simRho, "Rho");

    std::cout << std::endl;
}

void EventSimulator::simulationStatistics() {
    simPo = idleTime / timeOfLastDeparture; // percent idle time
    simW = (totalWaitTime + serviceTime)/ totalEvents; // avg time a customer is in the system
    simWq = totalWaitTime / static_cast<float>(totalEvents); // avg time waiting in queue
    simRho = (serviceTime) / (totalServers * timeOfLastDeparture); // utilization factor
    std::cout << "\nWaited for service: " <<(customerWaitedCnt / static_cast<float>(totalEvents));
}

// print row of stats and percent error
void EventSimulator::printFormattedStats(float theoretical, float experimental, std::string label) {
    std::cout << std::endl;
    std::cout << std::fixed << std::setw(5) << std::left << label << std::setprecision(5)
    << std::setw(12) << theoretical 
    << std::setw(12) << experimental 
    << std::setw(12) << calcPercentError(theoretical, experimental) << std::endl;
}

// print only analytical model
void EventSimulator::printFormattedStats(float theoretical, std::string label) {
    std::string empty = "-------";
    std::cout << std::endl;
    std::cout << std::fixed << std::setw(5) << std::left << label << std::setprecision(5)
    << std::setw(12) << theoretical
    << std::setw(12) << empty
    << std::setw(12) << empty << std::endl;
}

// return percent error of values
float EventSimulator::calcPercentError(float theoretical, float experimental) {
    float percentError;
    float PERCENT = 100.0;
    
    percentError = ((experimental - theoretical) / theoretical) * PERCENT;

    return percentError;
}

// get factorial of a number
float EventSimulator::factorial(float n) {
    return (n==1 || n == 0) ? 1 : factorial(n-1) * n;
}