#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

#include "Controller.h"
#include "Conveyor.h"
#include "Junction.h"
#include "Luggage.h"
#include "System.h"


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
 * beolvassa a rendszert a megadott forrásbol
 * @param is a rendszert leiró szöveg forrása
 * @return a felépitett rendszerre mutató pointer
 */
System* sysRead(std::istream& is){
    compType actType;

    char* actLine;

    System* sys = new System;

    std::cout << "Adja meg a komponenseket!" << std::endl;

    actType = readType(is, actLine);

    while(actType != endconf){
        //std::cerr << "while elejen actType: " << actType << std::endl;

        switch (actType){
            case inp: {
                //std::cerr << "inp" << std::endl;

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
                std::cout << "Eszlelt tipus: " << actType  << " id: " << sys->addJunction(tmpJunct) << std::endl;
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

                        //std::cerr << "jID: " << jId << " iId :" << iId << std::endl;

                        Conveyor* conveyor = new Conveyor;

                        System::addConveyor(conveyor);                 //conveyor hozzadasa a rendszerhez
                        sys->getInput(iId)->setNext(conveyor);      //input next-jenek beallitasa
                        conveyor->setNext(sys->getJunction(jId));      //conveyor next-jenek beallitasa
/*
                        std::cerr << "most letrehozott conv: ";
                        conveyor->write(std::cerr);
                        std::cerr << "juntcion next: " << sys->getJunction(jId)->getNext()->getType() << std::endl;*/

                        lineStream.str("\0");
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

                            //std::cerr << "j1ID: " << j1Id << "j2Id :" << j2Id << std::endl;

                            Conveyor* conveyor = new Conveyor;

                            System::addConveyor(conveyor);
                            sys->getJunction(j1Id)->addOutput(conveyor);
                            conveyor->setNext(sys->getJunction(j2Id));

                            lineStream.str("\0");
                        }
                        else if(actLine[1] == 'o') {
                            pushLine(actLine, 2);

                            std::stringstream lineStream;
                            lineStream << actLine;

                            int jId, oId;

                            lineStream >> jId >> oId;

                            //std::cerr << "jId: " << jId << "oId :" << oId << std::endl;

                            Conveyor* conveyor = new Conveyor;
                            System::addConveyor(conveyor);
                            conveyor->setNext(sys->getOutput(oId));
                            sys->getJunction(jId)->addOutput(conveyor);

                            lineStream.str("\0");
                        }

                    }
                    break;
                }
            }
            default:
                std::cerr << "Nem felismerheto lehetoseg" << std::endl;
        }

        actType = readType(is, actLine);
    }

    return sys;
}

/**
 * egy kis menü a betöltés elejen, amivel kiválaszthatjuk, honnan akarjuk betölteni a rendszert és be is tölti onnan a sysRead függvény segítségével
 * @return
 */
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

            if(fileS.fail()){
                std::cerr << "Nem sikerult megnyitni a file-t, kilepek :( " << std::endl;
                return NULL;
            }

            return sysRead(fileS);
        }
        default:
            std::cerr << "Nincs ilyen lehetoseg, kilepek :( " << std::endl;
            return NULL;
    }
}

int main() {
    System* system;

    system = miniMenu();

    if(system != NULL)
        system->list(std::cout);

    return 0;
}