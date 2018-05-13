#include <stdexcept>
#include <cstring>
#include <iostream>
#include "types.h"

void pushLine(char* line, int amount){
    int len = strlen(line);

    char tmpLine[len + 1];
    strcpy(tmpLine, line);
    tmpLine[strlen(line)] = '\0';

    for(unsigned int i = 0; i <= strlen(line); i++){

        line[i] = tmpLine[i + amount];
    }
}

compType whatType(char* line) {
    if(strstr(line, "input") != 0){
        //pushLine(line, 5);
        return inp;
    }
    else if(strstr(line, "output") != 0) {
        //pushLine(line, 6);
        return outp;
    }
    else if(strstr(line, "luggage") != 0) {
        //pushLine(line, 7);
        return bag;
    }
    else if(strstr(line, "connect") != 0) {
        pushLine(line, 7);
        return conn;
    }
    else if(strstr(line, "junction") != 0) {
        //pushLine(line, 8);
        return junct;
    }
    else if(strstr(line, "endconfig") != 0) {
        return endconf;
    }
    else{
        throw std::invalid_argument("nincs ilyen tipus");
    }
}

std::ostream& operator<<(std::ostream& os, compType c) {
    switch (c) {
        case inp:
            os << "input";
            break;
        case outp:
            os << "output";
            break;
        case bag:
            os << "bag";
            break;
        case conn:
            os << "connect";
            break;
        case junct:
            os << "junction";
            break;
        case conv:
            os << "conveyor";
            break;
        case endconf:
            os << "endconfig";
            break;
        default:
            os << "";
            break;
    }

    return os;
}