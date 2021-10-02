// customer.hpp

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

class Customer {
    private:
        float arrivalTime;
        float departureTime;
        float startOfServiceTime; // not equal to arrival time when clerks are taken
        Customer* nextCust; // for fifo
    public:
        Customer();
        Customer(float arrivalTime);
        Customer *GetNext(); // for fifo
        void SetNext(Customer* newNext);
};

#endif