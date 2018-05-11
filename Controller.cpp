#include <iostream>
#include "Controller.h"

Conveyor* Controller::manageBag(Luggage* bag, Junction *junction) {
    std::cout << junction->getId() << " id-vel rendelkezo  csomopont kert eligazitast a " << bag->getId() << " id-vel rendelkezo csomaghoz" << std::endl;

    for(int i = 0; i < junction->getNumOuts(); ++i){

        if(junction->getOutput(i)->getNext() == bag->getTarget())
            return junction->getOutput(i)->getNext();
    }

    //utvonal megkeresese es annak a szalagnak a cimenek a visszaadasa, amire tovabb kell kldeni a cuccot
    return NULL;
}
