#ifndef CSOMSZALL_CONTROLLER_H
#define CSOMSZALL_CONTROLLER_H

#include <cstdio>
#include "Junction.h"
#include "Luggage.h"
#include "Conveyor.h"

class Controller {

public:

    /**
     * egy csomópont ezt a függvényt hívja meg, ha továbbítania kell egy csomagot, ez dönti el melyik kimenetére kell tegye
     * @param bagId annak a csomagnak az id-je, amit tovabitani kellene
     * @param junction a függvényt meghívó csomópontra mutató pointer
     */
    Conveyor* manageBag(Luggage* bag, Junction *junctio);
};


#endif //CSOMSZALL_CONTROLLER_H
