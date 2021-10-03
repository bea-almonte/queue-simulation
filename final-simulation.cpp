#include <iostream>
#include <time.h>
#include <random>
#include "customer.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "eventsimulator.hpp"
int main() {
    EventSimulator event1;
    srand(time(NULL));
    float testnum = 1.5;
    event1.processEvents();
    
    return 0;
}