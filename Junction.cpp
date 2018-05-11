#include "Junction.h"
#include "System.h"

void Junction::transmit() {
    next = System::contr.manageBag(bag, this); //beallitja a kovetkezo pointert arra, amerre a csomagnak menni kell

    Conveyor::transmit();
}

void Junction::addOutput(Conveyor *newOut) {
    Conveyor** tmpOuts = new Conveyor*[numOuts + 1];

    for(int i = 0; i < numOuts; ++i){
        tmpOuts[i] = outputs[i];
    }

    tmpOuts[numOuts] = newOut;
    delete[] outputs;

    ++numOuts;
    outputs = tmpOuts;
}


Conveyor* Junction::getOutput(int id) {
    return outputs[id];
}

Junction::~Junction() {
    delete[] outputs;
}

void Junction::write(std::ostream &os) {
    os << "Junction, id: " << this->getId() <<  "\n\toutputs: " << std::endl;

    int numOuts = this->numOuts;
    for (int k = 0; k < numOuts; ++k) {
        os << "\t\t" << this->outputs[k]->getType() << " id: " << this->outputs[k]->getId() << std::endl;
    }
}
