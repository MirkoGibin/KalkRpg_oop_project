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

    virtual void potenzia(int mana, string parametro ="") {

        int divisore = 5;
        int incremento = mana / getLivello();

        incrementStat("Magia", incremento * getRarita() / divisore); //Magia riceve un bonus sicuro oltre alla normale distribuzione

        if(parametro == "") {
            list<string> statsList = getListaStats();
            incremento = incremento / statsList.size();
            for(auto i = statsList.begin(); i != statsList.end(); i++)
                incrementStat(*i, incremento);
        }
        else {
            if(parametro == "Spirito")
                incrementStat(parametro, incremento/getMagia());
            else
                incrementStat(parametro, incremento);
        }
    }

    virtual void estraiDa(Oggetto* oggetto) {
        if(dynamic_cast<Pietra*>(oggetto)) {
            if(getDurezza() >= 10) {

                setLivello(oggetto->getLivello());
                setRarita(oggetto->getRarita());
                list<string> s = oggetto->getListaStats();
                int numeroStat = s.size();

                for(auto i = s.begin(); i != s.end(); ++i)
                    if(*i == "Magia") incrementStat(*i, (oggetto->getSommaStats() - getSpirito()) / numeroStat);
                    else incrementStat(*i, getValoreStat(*i) / numeroStat * (numeroStat - 1));
            }
            else {}
                //eccezione durezza troppo poca
        }
        else {
            //eccezione no estrazione possibile
        }
    }
};

#endif // CRISTALLO_H

