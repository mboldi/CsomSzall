#include <ostream>
#include "Conveyor.h"

#include "System.h"

void Conveyor::transmit() {
    next->bag = bag;
    bag = NULL;
}

void Conveyor::setBag(Luggage *bag) {
    this->bag = bag;
}

Conveyor *Conveyor::getNext() {
    return next;
}

int Conveyor::getId() const {
    return id;
}

void Conveyor::setId(int id) {
    this->id = id;
}

void Conveyor::setNext(Conveyor *nextConv) {
    this->next = nextConv;
}

void Conveyor::write(std::ostream &os) {
    os << this->getType() << ", id: " << this->id << " next " ;
    if(this->next == NULL)
        os << "nincs";
    else
        os << "id: " << this->next->getId();
}

void Output::transmit() {
    System::removeBag(bag->getId());
    bag = NULL;
}

void Input::addBagToSys(int targetId) {
    bag = new Luggage;

    System::addBag(bag, targetId);
}