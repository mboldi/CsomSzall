#ifndef CSOMSZALL_CONVEYOR_H
#define CSOMSZALL_CONVEYOR_H

class Luggage;

#include <cstdio>
#include "Luggage.h"
#include "types.h"

class Conveyor {
    /// a szállítószalag id-je
    int id;
protected:
    /// a következő rendszerelemre mutató pointer
    Conveyor* next;
    /// az éppen a szalagon lévő csomagra mutató pointer
    Luggage* bag;
public:
    Conveyor(int id = 0): id(id), next(NULL), bag(NULL) {}
    //Conveyor(int id, Conveyor* nextConv): id(id), next(nextConv) {}
    Conveyor(Conveyor& c): id(c.getId()), next(c.getNext()) {}

    virtual compType getType() const { return conv; }

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

    void setNext(Conveyor* nextConv);

    /**
     * a kovetkezo rendszerelemre mutato pointert kerhetjuk le vele
     * @return a kovetkezo rendszerelemre mutato pointer
     */
    Conveyor* getNext();

    virtual void write(std::ostream& os);

    /**
     * ezt a függvényt meg kell hívni, ha átadunk a futószalagnak egy csomagot
     */
    //virtual void bagManage();

    virtual ~Conveyor() {};
};

class Input: public Conveyor {
public:
    Input(int id = 0): Conveyor(id) {}

    compType getType() const { return inp; }

    /**
     * egy táska látrehozására használt függvény
     * @param targetId a táska célpontjának id-je
     */
    void addBagToSys(int targetId);
};


class Output: public Conveyor {
public:
    compType getType() const { return outp; }

    void transmit();
};


#endif //CSOMSZALL_CONVEYOR_H
