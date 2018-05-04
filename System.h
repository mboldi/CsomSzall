#ifndef CSOMSZALL_SYSTEM_H
#define CSOMSZALL_SYSTEM_H

#include "Controller.h"

class System {
    static Junction** junctions;
    static int numJuncts;
    static Luggage** bags;
    static int numBags;
    static Output** outputs;
    static int numOuts;
    static Input** inputs;
    static int numIns;
    static Conveyor** conveyors;
    static int numConvs;

public:
    static Controller contr;

    /**
     * hozzaad egy elosztót a rendszerhez
     * @param junct az elosztóra mutató pointer
     */
    static int addJunction(Junction* junct);

    /**
     * hozzaad egy csomagot a csomagokat tároló tömbhöz
     * @param bag
     */
    static int addBag(Luggage* bag, int targetId);

    /**
     * hozzaad egy szalagot a szalagokat tároló tömbhöz
     * @param conveyorra mutató pointer
     */
    static int addConveyor(Conveyor* conv);

    static int addInput(Input* inp);

    static int addOutput(Output* outp);

    /**
     * mikor kikerül egy csomag a rendszerből, ezzel a függvénnyel lehet törölni a tömbből és újra is rendezi a tömböt, valamint korrigálja ehhez a csomagok id-jét
     * @param bagId a kitörölni kívánt csomag id-je
     */
    static void removeBag(int bagId);

    ~System();
};


#endif //CSOMSZALL_SYSTEM_H
