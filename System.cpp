#include "System.h"

//statikus adattagok inicializalasa
Controller System::contr;
Junction** System::junctions;
int System::numJuncts;
Luggage** System::bags;
int System::numBags;
Output** System::outputs;
int System::numOuts;

void System::removeBag(int bagId) {
    delete bags[bagId];

    Luggage** tmpBags = new Luggage*[numBags-1];

    for(int i = 0; i < bagId; ++i) {
        tmpBags[i] = bags[i];
    }

    for(int i = bagId; i+1 < numBags; ++i) {
        bags[i] = bags[i+1];
        bags[i]->setId(i);
    }

    delete[] bags;
    bags = tmpBags;
    --numBags;
}

void System::addJunction(Junction* junct) {
    Junction** tmpJunctions = new Junction*[numJuncts + 1];

    for(int i = 0; i < numJuncts; ++i) {
        tmpJunctions[i] = junctions[i];
    }

    tmpJunctions[numJuncts] = junct;
    ++numJuncts;
    delete[] junctions;
    junctions = tmpJunctions;
}

void System::addBag(Luggage *bag, int targetId) {
    Luggage** tmpBags = new Luggage*[numBags + 1];

    for(int i = 0; i < numBags; ++i) {
        tmpBags[i] = bags[i];
    }

    bag->setId(numBags);
    bag->setTarget(outputs[targetId]);

    tmpBags[numJuncts] = bag;
    ++numBags;
    delete[] bags;
    bags = tmpBags;
}

System::~System() {
    for(int i = 0; i < numJuncts; ++i)
        delete junctions[i];

    delete[] junctions;

    for (int i = 0; i < numBags; ++i)
        delete bags[i];

    delete[] bags;

    for(int i = 0; i < numOuts; ++i)
        delete outputs[i];

    delete[] outputs;
}
