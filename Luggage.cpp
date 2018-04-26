#include "Luggage.h"

Output* Luggage::getTarget() {
    return targetPoint;
}

int Luggage::getId() {
    return id;
}

void Luggage::setId(int id) {
    this->id = id;
}

void Luggage::setTarget(Output *out) {
    targetPoint = out;
}
