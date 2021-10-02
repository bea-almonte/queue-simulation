#include "heap.hpp"

float Heap::GetNextRandomInterval() {
    //Generate a random float f on the interval (0..1]
    float randFloat;
    float intervalTime;

    randFloat = float(rand()) / (float(RAND_MAX) + 1.0);
    
    //Compute intervalTime as -1 * (1.0/avg) * ln(f) // natural logarithm of f
    intervalTime = -1 * (1.0/2) * log(randFloat);
    return intervalTime;
}