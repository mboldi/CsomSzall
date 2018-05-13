#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

#include "memtrace.h"

#include "Controller.h"
#include "Conveyor.h"
#include "Junction.h"
#include "Luggage.h"
#include "System.h"

/**
 * megadott bemenetről beolvassa, hogy milyen típusú komponenst akarnak hozzáadni
 * @param is a bemenet
 * @param actLine az aktuális sort tároló char tömbre mutató pointer
 * @return a beolvasott típus
 */
compType readType(std::istream& is, char* actLine) {
    compType actType;

    bool success = false;

    while(!success){
        try {
            is.getline(actLine, 16);
            if(strcmp(actLine, "\0") == 0){
                success = false;
            }
            else {
                actType = whatType(actLine);
                success = true;
            }
        }
        catch (std::exception& e) {
            success = false;
            std::cerr << e.what() << std::endl;
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

    char* actLine = new char[16];

    System* sys = new System;

    std::cout << "Adja meg a komponenseket!" << std::endl;

    while((actType = readType(is, actLine)) != endconf){
        //std::cerr << "while elejen actLine: " << actLine << std::endl;

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
                pushLine(actLine, 1);
                switch (actLine[0]) {
                    case 'i': {
                        //input - junction conveyor
                        pushLine(actLine, 2);

                        std::stringstream lineStream;
                        lineStream << actLine;

                        int iId, jId;

                        lineStream >> iId >> jId;

                        if(jId >= sys->getNumJuncts() || iId >= sys->getNumIns()) {
                            std::cerr << "Rossz ID" << std::endl;
                        }
                        else {
                            Conveyor* conveyor = new Conveyor;

                            System::addConveyor(conveyor);                 //conveyor hozzadasa a rendszerhez
                            sys->getInput(iId)->setNext(conveyor);      //input next-jenek beallitasa
                            conveyor->setNext(sys->getJunction(jId));      //conveyor next-jenek beallitasa
                        }
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

                            if(j1Id >= sys->getNumJuncts() || j2Id >= sys->getNumJuncts()) {
                                std::cerr << "Rossz ID" << std::endl;
                            }
                            else {
                                Conveyor *conveyor = new Conveyor;

                                System::addConveyor(conveyor);
                                sys->getJunction(j1Id)->addOutput(conveyor);
                                conveyor->setNext(sys->getJunction(j2Id));
                            }
                        }
                        else if(actLine[1] == 'o') {
                            pushLine(actLine, 2);

                            std::stringstream lineStream;
                            lineStream << actLine;

                            int jId, oId;

                            lineStream >> jId >> oId;

                            if(jId >= sys->getNumJuncts() || oId >= sys->getNumOuts()) {
                                std::cerr << "Rossz ID" << std::endl;
                            }
                            else {
                                Conveyor *conveyor = new Conveyor;
                                System::addConveyor(conveyor);
                                conveyor->setNext(sys->getOutput(oId));
                                sys->getJunction(jId)->addOutput(conveyor);
                            }
                        }

                    }
                        break;
                }
                break;
            }
            default:
                std::cerr << "Nem felismerheto lehetoseg" << std::endl;
        }
    } //while vege

    delete[] actLine;

    return sys;
}

/**
 * egy kis menü a betöltés elejen, amivel kiválaszthatjuk, honnan akarjuk betölteni a rendszert és be is tölti onnan a sysRead függvény segítségével
 * @return a létrehozott rendszerre mutató pointer
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

/**
 * a csomagok hozzáadásáért és útjukra indításukért felelő függvény
 * @param sys a már felépített rendszerre mutató pointer
 * @param is a használt std::istream
 * @param os a használt std::ostream
 * @return ha true, akkor end-et kapott és kiléphet a program, false, ha még nem kapott vége jelzést
 */
bool bagAdder(System& sys, std::istream& is, std::ostream& os) {
    int inId = -1, outId = -1;

    char text[4];

    is >> text;

    text[4] = '\0';

    if(strcmp(text, "bag") == 0) {
        is >> inId >> outId;

        os << "inId: " << inId << " outId: " << outId << std::endl;

        if(inId == -1 || outId == -1 || inId >= sys.getNumIns() || outId >= sys.getNumOuts()){
            throw std::invalid_argument("Rossz id");
        }
        else {
            Luggage* tmpBag = new Luggage;

            sys.addBag(tmpBag, outId);
            sys.getInput(inId)->setBag(tmpBag);
            sys.getInput(inId)->transmit();
        }
    }
    else if(strcmp(text, "end") == 0) {
        return true;
    }
    else {
        throw std::invalid_argument("Nem tudom ertelmezni");
    }

    return false;
}

int main() {
    System* system;

    system = miniMenu();

    if(system != NULL){
        system->list(std::cout);

        std::cout << "\nA csomagokat a kovetkezo formatumban varom:\n\t\"bag\" *bemenet id-je(ahol bekerul a rendszerbe a csomag)* *kimenet id-je(ahova el kell jusson a csomag)*\nMiutan megadta a csomagot, vegigkovetheti annak utjat a rendszeren\nHa nem akar tobbet beadni, akkor irja be: end"
                  << std::endl;

        bool end = false;

        while(!end) {
            try {
                end = bagAdder(*system, std::cin, std::cout);
            }
            catch (std::exception& e) {
                std::cerr << "Hiba a csomag beolvasa kozben: " << e.what() << std::endl;
            }

        }
    }

    delete system;

    return 0;
}