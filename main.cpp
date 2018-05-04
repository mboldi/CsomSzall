#include <iostream>
#include <cstring>
#include <fstream>

#include "Controller.h"
#include "Conveyor.h"
#include "Junction.h"
#include "Luggage.h"
#include "System.h"

enum compType {junct, conv, bag, inp, outp, endconf};

/**
 * eltolja a sor tomb elemeit balra a megadott szammal
 * @param line a sorra mutato pointer
 * @param amount ennyivel fogja eltolni balra a sort
 */
void pushLine(char* line, int amount){
    for(int i = 0; i <= strlen(line); i++){
        line[i] = line[i + amount];
    }
}

/**
 * visszater a tipussal amilyen a belvasott sor, es ki is torli az elejerol a tipusmegjelolest, ha nem talal tpiust, akkor std::invalid_parameter exceptiont dob
 * @param line a sorra mutato pointer
 * @return a sor tipusa
 */
compType whatType(char* line) {
    if(strstr(line, "input") == 0){
        pushLine(line, 6);
        return inp;
    }
    else if(strstr(line, "output") == 0) {
        pushLine(line, 7);
        return outp;
    }
    else if(strstr(line, "luggage") == 0) {
        pushLine(line, 8);
        return bag;
    }
    else if(strstr(line, "conveyor") == 0) {
        pushLine(line, 9);
        return conv;
    }
    else if(strstr(line, "junction") == 0) {
        pushLine(line, 9);
        return junct;
    }
    else if(strstr(line, "endconfig") == 0) {
        return endconf;
    }
    else{
        throw std::invalid_argument("nincs ilyen tipus");
    }
}

/**
 * beolvassa a rendszert a megadott forrasbol
 * @param is a rendszert leiro szoveg forrasa
 */
bool sysRead(std::istream& is){
    char* actLine = new char[200];
    compType actType;

    is.getline(actLine, 200);
    actType = whatType(actLine);
    while(actType != endconf){
        switch (actType){
            case inp:
                Input* tmpInp = new Input;
                std::cout << System::addInput(tmpInp) << std::endl;
                break;
            case outp:
                Output* tmpOutp = new Output;
                std::cout << System::addOutput(tmpOutp) << std::endl;
                break;
            default:
                std::cout << "Kredenc" << std::endl;
        }

        is.getline(actLine, 200);
        actType = whatType(actLine);
    }

    whatType(actLine);

    delete[] actLine;
}

int main() {
    /*std::fstream fileS;
    fileS.open("asd.txt");*/

    /*char* alma =  new char[100];

    std::cin.getline(alma, 100);
    std::cout << alma << std::endl;

    delete[] alma;*/

    sysRead(std::cin);
    return 0;
}