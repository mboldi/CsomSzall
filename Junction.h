#ifndef CSOMSZALL_JUNCTION_H
#define CSOMSZALL_JUNCTION_H

#include "Conveyor.h"

class Junction: public Conveyor {
    Conveyor** inputs;      ///a csomópontba beérkező futószalagok
    int numIns;
    Conveyor** outputs;      ///a csomópontból kiinduló futószalagok
    int numOuts;

public:
    Junction(): inputs(NULL), outputs(NULL) {}

    /**
     * új bemeneti futószalag hosszáadása a csomóponthoz
     * @param newIn az újonnan hozzáadandó futószalagra mutató pointer
     */
    void addInput(Conveyor* newIn);

    /**
     * újy kimeneti futószalag hozzáadása a csomóponthoz
     * @param newOut az újonnan hozzáadandó futószalagra mutató pointer
     */
    void addOutput(Conveyor* newOut);

    /**
     * ezen fuggvenyen belul kell elintezni a csomag tovbbkuldeset, itt kellene meghívni a Controller manageBag függvényét
     */
    void bagManage();

    ~Junction() ;
};


#endif //CSOMSZALL_JUNCTION_H
