#include "queue.hpp"

Queue::Queue() {
    front = nullptr;
    end = nullptr;
} // set front and end to null

Queue::~Queue() {

}

//
void Queue::Enqueue(Customer* waitingCustomer) {
    // add customer to front if there aren't
    // others,otherwise add to end
    if (end == nullptr) {
        front = waitingCustomer;
        end = waitingCustomer;
    } else {
        // update pointer for current end
        end->nextCust = waitingCustomer;
        // end is now waitcustomer
        end = waitingCustomer;
    }
}

// service customer
// return pointer to serviced customer
Customer* Queue::Dequeue() {
    // temp pointer to return
    Customer *serviceCust;

    // set front to be serviced
    serviceCust = front;
    // 
    front = front->nextCust;

    // sets end to empty if queue is empty
    if (front == nullptr) {
        end = nullptr;
    }

    return serviceCust;
} // returns customer at front

bool Queue::IsEmpty() {
    if (end == nullptr) {
        return true;
    } else {
        return false;
    }
}