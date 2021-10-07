/// Bea Almonte - DSA2 Project 2
/// This program takes file inputs containing values for
/// lambda, mu, total servers, and total events to use in a simulation queue.
/// The results of the simulation are compared to an analytical model.

#include <iostream> // std::cout
#include <time.h>   // seed for rand()
#include <random>   // rand()
#include <fstream>  // reading files
#include <iomanip> // setw()
#include "customer.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "eventsimulator.hpp"

void TakeFileInput(float& lambda, float& mu, float& M, float& totalEvents, std::string filename);

int main() {
    std::ifstream inData;
    float lambda = 0;
    float mu = 0;
    float M = 0;
    float events;

    srand(time(NULL)); // set rand()

    // TEST 1
    std::cout << "Case 1\n\n";

    TakeFileInput(lambda, mu, M, events, "test1.txt");
    EventSimulator event1(lambda,mu,M,events);
    
    event1.processEvents();
    event1.analyticalModel(); // output analytical model and sim results

    std::cout << "\n======================================\n";
    
    // TEST 2
    std::cout << "Case 2\n\n";

    TakeFileInput(lambda, mu, M, events, "test2.txt");
    EventSimulator event2(lambda,mu,M,events);

    event2.processEvents();
    event2.analyticalModel(); // output analytical model and sim results
    return 0;
}

void TakeFileInput(float& lambda, float& mu, float& M, float& totalEvents, std::string filename) {
    std::ifstream inData;
    // open file
    inData.open(filename);
    // input data
    inData >> lambda >> mu >> M >> totalEvents;

    // output header

    std::cout << "\u03BB   \u03BC   M   Events" << std::endl;
    std::cout << std::left << std::fixed << std::setprecision(0)
    << std::setw(4) << lambda
    << std::setw(4) << mu
    << std::setw(4) << M
    << totalEvents << std::endl;

    inData.close();
}