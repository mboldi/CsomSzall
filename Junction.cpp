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
