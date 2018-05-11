#ifndef CSOMSZALL_JUNCTION_H
#define CSOMSZALL_JUNCTION_H

#include "Conveyor.h"

class Junction: public Conveyor {
    Conveyor** outputs;      ///a csomópontból kiinduló futószalagok
    int numOuts;

public:
    Junction(): outputs(NULL), numOuts(0) {}
    Junction(Junction& j): numOuts(j.getNumOuts()) {
        outputs = new Conveyor*[numOuts];
        for(int i = 0; i < numOuts; i++) {
            outputs[i] = j.getOutput(i);
        }
    }

    compType getType() const { return junct; }

    /**
     * újy kimeneti futószalag hozzáadása a csomóponthoz
     * @param newOut az újonnan hozzáadandó futószalagra mutató pointer
     */
    void addOutput(Conveyor* newOut);

    Conveyor* getOutput(int id);

    int getNumOuts() { return numOuts; }

    void write(std::ostream& os);

    void transmit();

    ~Junction() ;
};

#endif //CSOMSZALL_JUNCTION_H
