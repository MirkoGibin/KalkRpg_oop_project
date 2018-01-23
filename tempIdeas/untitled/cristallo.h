#ifndef CRISTALLO_H
#define CRISTALLO_H
#include "pietra.h"
#include<typeinfo>

class Erba;
class Unguento;
class Osso;
class Amuleto;

class Cristallo : public Pietra {
private:

    /* parameters inside stats in Oggetto are:
     * spirito
     * attacco
     * durezza
     * magia
     */

public:
    //default constructor
    Cristallo(const int livello =0,
              const int rarita =0,
              const float spirito =0,
              const float durezza =0,
              const float magia =0) : Pietra(livello, rarita, spirito, durezza) {
        Oggetto::insertStat("Magia", magia);
    }

    //methods
    virtual double getMagia() const {
        return getValoreStat("Magia");
    }

    void potenzia(int mana, string parametro ="") {

        int divisore = 5;
        int incremento = mana / getLivello();

        incrementStat("Magia", incremento * getRarita() / divisore); //Magia riceve un bonus sicuro oltre alla normale distribuzione

        if(parametro == "") {
            list<string>* statsList = getListaStats();
            incremento = incremento / statsList->size();
            for(auto i = statsList->begin(); i != statsList->end(); i++)
                incrementStat(*i, incremento);
            delete statsList;
        }
        else {
            if(parametro == "Spirito")
                incrementStat(parametro, incremento/getMagia());
            else
                incrementStat(parametro, incremento);
        }
    }
};

#endif // CRISTALLO_H

