#include <iostream>
#include "Controller.h"

Conveyor* Controller::manageBag(int bagId, Conveyor *junction) {
    std::cout << junction->getId() << " id-vel rendelkezo  csomopont kert eligazitast a " << bagId << " id-vel rendelkezo csomaghoz" << std::endl;

    //utvonal megkeresese es annak a szalagnak a cimenek a visszaadasa, amire tovabb kell kldeni a cuccot
    return NULL;
}
