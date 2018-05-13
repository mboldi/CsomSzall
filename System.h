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
     * @return a hozzáadott komponens id-je
     */
    static int addJunction(Junction* junct);

    /**
     * visszatér a megadott id-nek megfelelő id-jű junctionre mutató pointerrel
     * @param id a lekérni kívánt junction id-je
     * @return a megfelelő junctionre mutató pointer
     */
    Junction* getJunction(int id);

    /**
     * hozzaad egy csomagot a csomagokat tároló tömbhöz
     * @param bag a csomagra mutató pointer
     * @param targetId a csomag céljának id-je
     * @return a hozzáadott komponens id-je
     */
    static int addBag(Luggage* bag, int targetId);

    /**
     * visszatér a megadott id-nek megfelelő id-jű bag-re mutató pointerrel
     * @param id a lekérni kívánt bag id-je
     * @return a megfelelő bag-re mutató pointer
     */
    Luggage* getBag(int id);

    /**
     * hozzaad egy szalagot a szalagokat tároló tömbhöz
     * @param conveyorra mutató pointer
     * @return a hozzáadott komponens id-je
     */
    static int addConveyor(Conveyor* conv);

    /**
     * visszatér a megadott id-nek megfelelő id-jű conveyor-ra mutató pointerrel
     * @param id a lekérni kívánt conveyor id-je
     * @return a megfelelő conveyor-ra mutató pointer
     */
    Conveyor* getConveyor(int id);

    /**
     * hozzáad a rendszerhez egy input egységet
     * @param inp az egységre mutató pointer
     * @return a hozzáadott komponens id-je
     */
    static int addInput(Input* inp);

    /**
     * visszatér a megadott id-nek megfelelő id-jű input-ra mutató pointerrel
     * @param id a lekérni kívánt input id-je
     * @return a megfelelő input-ra mutató pointer
     */
    Input* getInput(int id);

    /**
     * hozzáad a rendszerhez egy output egységet
     * @param inp az egységre mutató pointer
     * @return a hozzáadott komponens id-je
     */
    static int addOutput(Output* outp);

    /**
     * visszatér a megadott id-nek megfelelő id-jű output-ra mutató pointerrel
     * @param id a lekérni kívánt output id-je
     * @return a megfelelő output-ra mutató pointer
     */
    Output* getOutput(int id);

    /**
     * mikor kikerül egy csomag a rendszerből, ezzel a függvénnyel lehet törölni a tömbből és újra is rendezi a tömböt, valamint korrigálja ehhez a csomagok id-jét
     * @param bagId a kitörölni kívánt csomag id-je
     */
    static void removeBag(int bagId);

    /**
     * kiírja a rendszert
     * @param os a használni kívánt std::ostream
     */
    void list(std::ostream& os);

    /**
     * visszatér a rendszerben megtalálható bemeneti egységek számával
     * @return az egységek száma
     */
    int getNumIns() { return numIns; }

    /**
     * visszatér a rendszerben megtalálható kimeneti egységek számával
     * @return az egységek száma
     */
    int getNumOuts() { return numOuts; }

    /**
     * visszatér a rendszerben megtalálható elágazások egységek számával
     * @return az egységek száma
     */
    int getNumJuncts() { return numJuncts; }

    /**
     * destruktor
     */
    ~System();
};

#endif //CSOMSZALL_SYSTEM_H
