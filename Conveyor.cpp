#include <ostream>
#include <iostream>
#include "Conveyor.h"

#include "System.h"

void Conveyor::transmit() {
    if(next == NULL)
        throw std::runtime_error("nincs csatlakoztatva kovetkezo rendszerelem");
    next->bag = bag;
    bag = NULL;
    next->transmit();
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
        os << "type: " << this->next->getType() << ", id: " << this->next->getId();
}

void Output::transmit() {
    std::cout << bag->getId() << " idvel rendelkezo csomag elerte celjat." << std::endl;

    System::removeBag(bag->getId());
    bag = NULL;
}

void Input::addBagToSys(int targetId) {
    bag = new Luggage;

    System::addBag(bag, targetId);
}