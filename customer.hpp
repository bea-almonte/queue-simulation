// customer.hpp

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

class Customer {
    public:
        Customer();
        Customer(float arrivalTime);
        Customer& operator=(const Customer& newCustomer);
        Customer* nextCust; 
        float arrivalTime;
        float departureTime;
        float startOfServiceTime; // not equal to 
        //arrival time when clerks are taken
        float GetEventTime();
        bool isDeparture;
};

#endif