#ifndef CSOMSZALL_LUGGAGE_H
#define CSOMSZALL_LUGGAGE_H

class Conveyor;
class Output;
class Input;

#include <ostream>
#include "Conveyor.h"

class Luggage {
    /// a csomag id-je
    int id;
    /// a csomag célpontjára mutató pointer
    Output* targetPoint;
public:
    /**
     * konstruktor
     * @param out a célpontjára mutató pointer
     * @param id a csomag id-je
     */
    Luggage(int id = 0): id(id), targetPoint(NULL) {}

    /**
     * ezzel a fuggvénnyel le lehet kérni a csomag célpontját
     * @return a csomag célpontjára mutató pointer
     */
    Output* getTarget();

    void setTarget(Output* out);

    void setId(int id);

    /**
     * ezzel a fuggvénnyel le lehet kérni a csomag id.jét
     * @return a csomag id-je, int
     */
    int getId();
};

std::ostream& operator<<(std::ostream& os, Luggage& l);


#endif //CSOMSZALL_LUGGAGE_H
