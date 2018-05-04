#ifndef CSOMSZALL_CONVEYOR_H
#define CSOMSZALL_CONVEYOR_H

class Luggage;

#include <cstdio>
#include "Luggage.h"

class Conveyor {
    /// a szállítószalag id-je
    int id;
protected:
    /// a következő rendszerelemre mutató pointer
    Conveyor* next;
    /// az éppen a szalagon lévő csomagra mutató pointer
    Luggage* bag;
public:
    Conveyor(int id = 0): id(id), next(NULL) {}
    Conveyor(int id, Conveyor* nextConv): id(id), next(nextConv) {}

    int getId() const;

    void setId(int id);
    /**
     * tovabbkuldi a csomagot
     */
    virtual void transmit();

    /**
     * beallitja a szalagon levo csomagot
     * @param bag a csomagra mutato pointer
     */
    void setBag(Luggage* bag);

    /**
     * a kovetkezo rendszerelemre mutato pointert kerhetjuk le vele
     * @return a kovetkezo rendszerelemre mutato pointer
     */
    Conveyor* getNext();


    /**
     * ezt a függvényt meg kell hívni, ha átadunk a futószalagnak egy csomagot
     */
    //virtual void bagManage();

    virtual ~Conveyor() {};
};

class Input: public Conveyor {
public:
    Input(int id = 0): Conveyor(id) {}

    /**
     * egy táska látrehozására használt függvény
     * @param targetId a táska célpontjának id-je
     */
    void addBagToSys(int targetId);
};


class Output: public Conveyor {
public:
    void transmit();
};


#endif //CSOMSZALL_CONVEYOR_H
