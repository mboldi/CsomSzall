#ifndef CSOMSZALL_JUNCTION_H
#define CSOMSZALL_JUNCTION_H

#include "Conveyor.h"

class Junction: public Conveyor {
    Conveyor** outputs;      ///a csomópontból kiinduló futószalagok
    int numOuts;

public:
    /**
     * konstruktor
     */
    Junction(): outputs(NULL), numOuts(0) {}

    /**
     * másoló konstruktor
     * @param j a junction, amit akarunk másolni
     */
    Junction(Junction& j): numOuts(j.getNumOuts()) {
        outputs = new Conveyor*[numOuts];
        for(int i = 0; i < numOuts; i++) {
            outputs[i] = j.getOutput(i);
        }
    }

    /**
     * visszatér a saját típusával
     * @return compType típusban a komponens típusa - konstans junct
     */
    compType getType() const { return junct; }

    /**
     * újy kimeneti futószalag hozzáadása a csomóponthoz
     * @param newOut az újonnan hozzáadandó futószalagra mutató pointer
     */
    void addOutput(Conveyor* newOut);

    /**
     * visszatér a megadott id-nek megfelelő kimeneti conveyorra mutató pointerrel
     * @param id a kívánt kimeneti conveyor id-je
     * @return a megfelelő kimeneti conevyorra mutató pointer
     */
    Conveyor* getOutput(int id);

    /**
     * visszatér a kimenetek számával
     * @return a kimenetek száma
     */
    int getNumOuts() { return numOuts; }

    /**
     * kiírja a junction-t
     * @param os a használni kívánt std::ostream
     */
    void write(std::ostream& os);

    /**
     * miután megkereste a megfelelő kimenetet tovabbkuldi a csomagot
     */
    void transmit();

    /**
     * destruktor
     */
    ~Junction() ;
};

#endif //CSOMSZALL_JUNCTION_H
