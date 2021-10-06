#include "queue.hpp"
// create allocate customers

Queue::Queue() {
    front = nullptr;
    end = nullptr;
} // set front and end to null

Queue::~Queue() {

}

//
void Queue::Enqueue(Customer waitingCustomer) {
    // add customer to front if there aren't
    // others,otherwise add to end
    Customer *n = new Customer(waitingCustomer.arrivalTime);

    if (end == nullptr) {
        front = n;
        end = n;
    } else {
        // update pointer for current end
        end->nextCust = n;
        // end is now waitcustomer
        end = n;
    }
}

// service customer
// return pointer to serviced customer
Customer Queue::Dequeue() {
    // temp object to return
    Customer serviceCust;
    Customer *toBeDeleted;
    // set front to be serviced
    serviceCust = *front;
    toBeDeleted = front;

    // set front to next customer in line
    front = front->nextCust;

    // sets end to empty if queue is empty
    if (front == nullptr) {
        end = nullptr;
    }
    
    delete toBeDeleted;
    return serviceCust;
} // returns customer at front

bool Queue::IsEmpty() {
    if (end == nullptr) {
        return true;
    } else {
        return false;
    }
}