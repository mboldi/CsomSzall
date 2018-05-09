#ifndef CSOMSZALL_TYPES_HPP
#define CSOMSZALL_TYPES_HPP

#include <cstring>

///komponenst típus lehetőségek
enum compType {junct, conn, bag, inp, outp, conv, endconf};

/**
 * eltolja a sor tomb elemeit balra a megadott szammal
 * @param line a sorra mutato pointer
 * @param amount ennyivel fogja eltolni balra a sort
 */
void pushLine(char* line, int amount);

/**
 * visszater a tipussal amilyen a belvasott sor, es ki is torli az elejerol a tipusmegjelolest, ha nem talal tpiust, akkor std::invalid_parameter exceptiont dob
 * @param line a sorra mutato pointer
 * @return a sor tipusa
 */
compType whatType(char* line);

std::ostream& operator<<(std::ostream& os, compType c);

#endif //CSOMSZALL_TYPES_HPP
