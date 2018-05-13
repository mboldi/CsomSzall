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

    /**
     * visszatér a saját típusával
     * @return compType típusban a komponens típusa - konstans conv
     */
    virtual compType getType() const { return conv; }

    /**
     * id lekérdező
     * @return az id
     */
    int getId() const;

    /**
     * beállítja az id-jét az objektumnak
     * @param id a kívánt id
     */
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
     * beállítja a következő elemre mutató pointert
     * @param nextConv a kívánt következő elemre mutató pointer
     */
    void setNext(Conveyor* nextConv);

    /**
     * a kovetkezo rendszerelemre mutato pointert kerhetjuk le vele
     * @return a kovetkezo rendszerelemre mutato pointer
     */
    Conveyor* getNext();

    /**
     * kiírja a komponenst
     * @param os az std::ostream, amelyre ki akarjuk írni a komponenst
     */
    virtual void write(std::ostream& os);

    /**
     * destruktor
     */
    virtual ~Conveyor() {};
};

class Input: public Conveyor {
public:
    Input(int id = 0): Conveyor(id) {}

    /**
     * visszatér a saját típusával
     * @return compType típusban a komponens típusa - konstans inp
     */
    compType getType() const { return inp; }

    /**
     * egy táska látrehozására használt függvény
     * @param targetId a táska célpontjának id-je
     */
    void addBagToSys(int targetId);
};


class Output: public Conveyor {
public:
    /**
     * visszatér a saját típusával
     * @return compType típusban a komponens típusa - konstans outp
     */
    compType getType() const { return outp; }

    /**
     * kitörli a csomagot a rendszerből
     */
    void transmit();
};


#endif //CSOMSZALL_CONVEYOR_H
