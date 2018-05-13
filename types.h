#ifndef CSOMSZALL_TYPES_HPP
#define CSOMSZALL_TYPES_HPP

#include <cstring>

///komponenst típus lehetőségek
enum compType {junct, conn, bag, inp, outp, conv, endconf};

/**
 * eltol balra a megadott mennyiséggel egy char tömböt
 * @param line a char tömbre mutató pointer
 * @param amount ennyivel fogja eltolni a char tömböt
 */
void pushLine(char* line, int amount);

/**
 * megmondja, hogy a megadott char tömbben melyik komponens típus található meg
 * @param line a char tömbre mutató pointer
 * @return a fellelhető komponens típus
 */
compType whatType(char* line);

/**
 * inserter operator overload, hogy ki lehessen írni compType típusú változót
 * @param os a használni kívánt std::ostream
 * @param c a kiírni kívánt változó
 * @return a használt std::ostream
 */
std::ostream& operator<<(std::ostream& os, compType c);

#endif //CSOMSZALL_TYPES_HPP
