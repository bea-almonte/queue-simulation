/// Bea Almonte - DSA2 Project 2
/// This program takes file inputs containing values for
/// lambda, mu, total servers, and total events to use in a simulation queue.
/// The results of the simulation are compared to an analytical model.

#include <iostream> // std::cout
#include <time.h>   // seed for rand()
#include <random>   // rand()
#include <fstream>
#include "customer.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "eventsimulator.hpp"

int main() {
    std::ifstream inData;
    float lambda = 0;
    float mu = 0;
    float M = 0;
    float events;

    // TEST 1
    inData.open("test1.txt");
    inData >> lambda >> mu >> M >> events;
    EventSimulator event1(lambda,mu,M,events);
    srand(time(NULL)); // set rand()

    event1.processEvents();
    event1.analyticalModel(); // output analytical model and sim results

    std::cout << "\n========================================\n";
    
    // TEST 2
    inData.close();
    inData.open("test2.txt");
    inData >> lambda >> mu >> M >> events;

    EventSimulator event2(lambda,mu,M,events);
    event2.processEvents();
    event2.analyticalModel(); // output analytical model and sim results
    inData.close();
    return 0;
}