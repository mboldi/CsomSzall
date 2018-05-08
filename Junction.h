#ifndef CSOMSZALL_JUNCTION_H
#define CSOMSZALL_JUNCTION_H

#include "Conveyor.h"

class Junction: public Conveyor {
    int id;
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

    Conveyor* getInput(int id);

    /**
     * újy kimeneti futószalag hozzáadása a csomóponthoz
     * @param newOut az újonnan hozzáadandó futószalagra mutató pointer
     */
    void addOutput(Conveyor* newOut);

    Conveyor* getOutput(int id);

    int getNumIns() { return numIns; }
    int getNumOuts() { return numOuts; }

    /**
     * ezen fuggvenyen belul kell elintezni a csomag tovbbkuldeset, itt kellene meghívni a Controller manageBag függvényét
     */
    void bagManage();

    ~Junction() ;
};

std::ostream& operator<<(std::ostream& os, Conveyor& c);


#endif //CSOMSZALL_JUNCTION_H
