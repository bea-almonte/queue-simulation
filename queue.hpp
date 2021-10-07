// queue.hpp -- maintains a fifo queue of customers
#include "customer.hpp"

#ifndef QUEUE_HPP
#define QUEUE_HPP

class Queue {
    private:
        Customer* front; // front of line
        Customer* end; // end of line
    public:
        Queue(); // set front and end to null
        void Enqueue(Customer waitingCustomer); // insert customer at end
        Customer Dequeue(); // returns customer at front
        bool IsEmpty();
};

#endif