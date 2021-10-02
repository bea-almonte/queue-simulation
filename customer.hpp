// customer.hpp

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

class Customer {
    public:
        Customer();
        Customer(float arrivalTime);
        Customer* nextCust; 
        float arrivalTime;
        float departureTime;
        float startOfServiceTime; // not equal to 
        //arrival time when clerks are taken
};

#endif