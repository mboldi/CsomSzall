#include "Junction.h"

#include "System.h"

void Junction::bagManage() {
    next = System::contr.manageBag(bag->getId(), this);
}

void Junction::addInput(Conveyor *newIn) {
    Conveyor** tmpIns = new Conveyor*[numIns + 1];

    for(int i = 0; i < numIns; ++i){
        tmpIns[i] = inputs[i];
    }

    tmpIns[numIns] = newIn;
    delete[] inputs;
    ++numIns;
    inputs = tmpIns;
}

void Junction::addOutput(Conveyor *newOut) {
    Conveyor** tmpOuts = new Conveyor*[numOuts + 1];

    for(int i = 0; i < numIns; ++i){
        tmpOuts[i] = outputs[i];
    }

    tmpOuts[numOuts] = newOut;
    delete[] outputs;
    ++numIns;
    inputs = tmpOuts;
}

Junction::~Junction() {
    delete[] inputs;
    delete[] outputs;
}

Conveyor *Junction::getInput(int id) {
    return inputs[id];
}

Conveyor* Junction::getOutput(int id) {
    return outputs[id];
}

std::ostream& operator<<(std::ostream& os, Junction & j) {
    os << "Junction, id: " << j.getId() << " inputs ";

    for (int i = 0; i < j.getNumIns(); ++i) {
        os << "\t" << *j.getInput(i) << std::endl;
    }

    os << "outputs: ";

    for (int k = 0; k < j.getNumOuts(); ++k) {
        os << "\t" << *j.getOutput(k) << std::endl;
    }
}
