#include "customer.hpp"

Customer::Customer() {
    arrivalTime = 0;
    departureTime = -1;
    startOfServiceTime = 0;
    nextCust = nullptr;
}

Customer::Customer(float arrivalTime) {
    this->arrivalTime = arrivalTime;
    departureTime = -1;
    startOfServiceTime = 0;
    nextCust = nullptr;
}