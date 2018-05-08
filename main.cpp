#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

#include "Controller.h"
#include "Conveyor.h"
#include "Junction.h"
#include "Luggage.h"
#include "System.h"

///komponenst típus lehetőségek
enum compType {junct, conn, bag, inp, outp, endconf};

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
    if(strstr(line, "input") != 0){
        pushLine(line, 6);
        return inp;
    }
    else if(strstr(line, "output") != 0) {
        pushLine(line, 7);
        return outp;
    }
    else if(strstr(line, "luggage") != 0) {
        pushLine(line, 8);
        return bag;
    }
    else if(strstr(line, "connect") != 0) {
        pushLine(line, 8);
        return conn;
    }
    else if(strstr(line, "junction") != 0) {
        pushLine(line, 9);
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
        case endconf:
            os << "endconfig";
            break;
    }

    return os;
}

compType readType(std::istream& is, char*& actLine) {
    actLine = new char[200];
    compType actType;

    bool success = false;

    while(!success){
        try {
            is.getline(actLine, 200);
            actType = whatType(actLine);
            success = true;
        }
        catch (std::exception& e) {
            success = false;
            std::cout << e.what() << std::endl;
            std::cout << "Kerem adja meg ujra, vagy ha nincs tobb, irja be: endconfig" << std::endl;
        }
    }


    return actType;
}

/**
 * beolvassa a rendszert a megadott forrasbol
 * @param is a rendszert leiro szoveg forrasa
 */
System* sysRead(std::istream& is){
    compType actType;

    char* actLine;

    System* sys = new System;

    std::cout << "Adja meg a komponenseket!" << std::endl;

    actType = readType(is, actLine);

    while(actType != endconf){
        std::cerr << "while elejen actType: " << actType << std::endl;

        switch (actType){
            case inp: {
                std::cerr << "inp" << std::endl;

                Input* tmpInp = new Input;
                std::cout << "Eszlelt tipus: " << actType << " id: " << sys->addInput(tmpInp) << std::endl;
            }
            break;
            case outp: {
                Output* tmpOutp = new Output;
                std::cout << "Eszlelt tipus: " << actType  << " id: " << sys->addOutput(tmpOutp) << std::endl;
            }
            break;
            case junct: {
                Junction* tmpJunct = new Junction;
                std::cout << "Eszlelt tipus: " << actType  << " id: " << actType << sys->addJunction(tmpJunct) << std::endl;
            }
            break;
            case conn: {
                switch (actLine[0]) {
                    case 'i': {
                        //input - junction conveyor
                        pushLine(actLine, 2);

                        std::stringstream lineStream;
                        lineStream << actLine;

                        int iId, jId;

                        lineStream >> iId >> jId;

                        std::cerr << "jID: " << jId << " iId :" << iId << std::endl;

                        Conveyor* conveyor = new Conveyor;

                        sys->addConveyor(conveyor);                 //conveyor hozzadasa a rendszerhez
                        sys->getInput(iId)->setNext(conveyor);      //input next-jenek beallitasa
                        conveyor->setNext(sys->getJunction(jId));      //conveyor next-jenek beallitasa
                        sys->getJunction(jId)->addInput(conveyor);  //a conveyor hozzaadasa a junction input-jaihoz
                    }
                    break;
                    case 'j': {
                        if(actLine[1] == 'j') {
                            //junction - junction conveyor
                            pushLine(actLine, 2);

                            std::stringstream lineStream;
                            lineStream << actLine;

                            int j1Id, j2Id;

                            lineStream >> j1Id >> j2Id;

                            std::cerr << "j1ID: " << j1Id << "j2Id :" << j2Id << std::endl;

                            Conveyor* conveyor = new Conveyor;

                            sys->addConveyor(conveyor);
                            sys->getJunction(j1Id)->addOutput(conveyor);
                            conveyor->setNext(sys->getJunction(j2Id));
                            sys->getJunction(j2Id)->addInput(conveyor);
                        }
                        else if(actLine[1] == 'o') {
                            pushLine(actLine, 2);

                            std::stringstream lineStream;
                            lineStream << actLine;

                            int jId, oId;

                            lineStream >> jId >> oId;

                            std::cerr << "jId: " << jId << "oId :" << oId << std::endl;

                            Conveyor* conveyor = new Conveyor;
                            sys->addConveyor(conveyor);
                            conveyor->setNext(sys->getOutput(oId));
                            sys->getJunction(jId)->addOutput(conveyor);
                        }

                    }
                    break;
                }
            }
            default:
                std::cerr << "Kredenc" << std::endl;
        }

        actType = readType(is, actLine);
    }

    return sys;
}

System* miniMenu() {
    std::cout << "Honnan akarja megnyitni a konfiguraciot: fajlbol, vagy a console ablakbol? (f/c) ";

    char response;
    std::cin >> response;

    response = tolower(response);

    switch (response){
        case 'c':
            return sysRead(std::cin);
        case 'f': {
            std::cout << "Adja meg a fajlnevet!";

            char Fname[100];
            std::cin >> Fname;

            std::ifstream fileS(Fname);

            return sysRead(fileS);
        }
        default:
            std::cout << "Nincs ilyen lehetoseg, kilepek :( " << std::endl;
            return NULL;
    }
}

int main() {
    System* system;

    system = miniMenu();

    std::cout << *system;

    return 0;
}