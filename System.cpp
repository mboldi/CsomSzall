#include <ostream>
#include "System.h"
#include "Conveyor.h"
#include "Junction.h"

//statikus adattagok inicializalasa
Controller System::contr;
Junction** System::junctions;
int System::numJuncts = 0;
Luggage** System::bags;
int System::numBags = 0;
Output** System::outputs;
int System::numOuts = 0;
Input** System::inputs;
int System::numIns = 0;
Conveyor** System::conveyors;
int System::numConvs = 0;

int System::addBag(Luggage *bag, int targetId) {
    Luggage** tmpBags = new Luggage*[numBags + 1];

    for(int i = 0; i < numBags; ++i) {
        tmpBags[i] = bags[i];
    }

    bag->setId(numBags);
    bag->setTarget(outputs[targetId]);

    tmpBags[numBags] = bag;
    bag->setId(numBags);

    ++numBags;
    delete[] bags;
    bags = tmpBags;
    return numBags - 1;
}

Luggage *System::getBag(int id) {
    return bags[id];
}

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

int System::addJunction(Junction* junct) {
    Junction** tmpJunctions = new Junction*[numJuncts + 1];

    for(int i = 0; i < numJuncts; ++i) {
        tmpJunctions[i] = junctions[i];
    }

    tmpJunctions[numJuncts] = junct;
    junct->setId(numJuncts);

    ++numJuncts;
    delete[] junctions;
    junctions = tmpJunctions;

    return numJuncts - 1;
}

Junction *System::getJunction(int id) {
    return junctions[id];
}

int System::addConveyor(Conveyor* conv) {
    Conveyor** tmpConveyors = new Conveyor*[numConvs + 1];

    for(int i = 0; i < numBags; ++i) {
        tmpConveyors[i] = conveyors[i];
    }

    tmpConveyors[numConvs] = conv;
    conv->setId(numConvs);

    ++numConvs;
    delete[] conveyors;
    conveyors = tmpConveyors;
    return numConvs - 1;
}

Conveyor *System::getConveyor(int id) {
    return conveyors[id];
}

int System::addInput(Input *inp) {
    Input** tmpInputs = new Input*[numIns + 1];

    for(int i = 0; i < numIns; ++i) {
        tmpInputs[i] = inputs[i];
    }

    tmpInputs[numIns] = inp;
    inp->setId(numIns);

    ++numIns;
    delete[] inputs;
    inputs = tmpInputs;

    return numIns - 1;
}

Input *System::getInput(int id) {
    return inputs[id];
}

int System::addOutput(Output *outp) {
    Output** tmpOutputs = new Output*[numOuts + 1];

    for(int i = 0; i < numOuts; ++i) {
        tmpOutputs[i] = outputs[i];
    }

    tmpOutputs[numOuts] = outp;
    outp->setId(numOuts);

    ++numOuts;
    delete[] outputs;
    outputs = tmpOutputs;

    return numOuts - 1;
}

Output *System::getOutput(int id) {
    return outputs[id];
}

void System::list(std::ostream& os) {
    os << "rendszer: " << std::endl;

    int insNum = numIns;
    for(int i = 0; i < insNum; ++i) {
        inputs[i]->write(os);
        os << std::endl;
    }

    int outsNum = numOuts;
    for(int i = 0; i < outsNum; ++i) {
        outputs[i]->write(os);
        os << std::endl;
    }

    int junctsNum = numJuncts;
    for(int i = 0; i < junctsNum; ++i) {
        junctions[i]->write(os);
        os << std::endl;
    }

    int convsNum = numConvs;
    for(int i = 0; i < convsNum; ++i) {
        Conveyor actConv = *this->conveyors[i];
        actConv.write(os);
        os << std::endl;
    }

    for(int i = 0; i < numBags; ++i)
        os << bags[i]->getId() << std::endl;
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

    for(int i = 0; i < numIns; ++i)
        delete inputs[i];

    delete[] inputs;

    for(int i = 0; i < numConvs; ++i)
        delete conveyors[i];

    delete[] conveyors;
}