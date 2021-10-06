#include <iostream>
#include <time.h>
#include <random>
#include "customer.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "eventsimulator.hpp"
int main() {
    EventSimulator event1(2,3,2,5000);
    srand(time(NULL));
    event1.processEvents();
    event1.analyticalModel();
    return 0;
}