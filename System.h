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

public:
    static Controller contr;

    System(){}

    /**
     * hozzaad egy elosztót a rendszerhez
     * @param junct az elosztóra muttó pointer
     */
    static void addJunction(Junction* junct);

    /**
     * hozzaad egy csomagot a csomagokat tároló tömbhöz
     * @param bag
     */
    static void addBag(Luggage* bag, int targetId);

    /**
     * mikor kikerül egy csomag a rendszerből, ezzel a függvénnyel lehet törölni a tömbből és újra is rendezi a tömböt, valamir korrigálja ehhez a csomagok id-jét
     * @param bagId a kitörölni kívánt csomag id-je
     */
    static void removeBag(int bagId);

    ~System();
};


#endif //CSOMSZALL_SYSTEM_H
