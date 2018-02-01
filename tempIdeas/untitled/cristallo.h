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
    string magia_;

public:
    //default constructor
    Cristallo(const int livello =0,
              const int rarita =0,
              const float spirito =0,
              const float durezza =0,
              const float magia =0) : Pietra(livello, rarita, spirito, durezza), magia_("Magia") {
        Oggetto::insertStat(magia_, magia);
    }

    //methods
    virtual double getMagia() const {
        return getValoreStat(magia_);
    }

    Cristallo* clone() const {
        return new Cristallo(*this);
    }

    virtual void potenzia(int mana, string parametro ="") {

        int incremento = mana * getLivello() * getRarita();
        int divisore;

        if(parametro == "Spirito") {
            divisore = 15;
            incrementStat(parametro, incremento/getMagia());
            incrementStat(magia_, incremento * getRarita() / divisore);
        }
        else {
            divisore = 10;
            incrementStat(magia_, incremento * getRarita() / divisore);
            Pietra::potenzia(mana, parametro);
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
                    if(*i == magia_) incrementStat(*i, (oggetto->getSommaStats() - getSpirito()) / numeroStat);
                    else incrementStat(*i, getValoreStat(*i) / numeroStat * (numeroStat - 1));
            }
            else {}
                //eccezione durezza troppo poca
        }
        else {
            //eccezione no estrazione possibile
        }
    }

    float ricicla() const {
        return Pietra::ricicla() + getValoreStat(magia_) * getRarita();
    }

    void distribuisci(Oggetto* obj) {
        float val = getMagia() / 2;

        if(getDurezza() < val) {} //throw eccezione

        editDurezza(-val);

        list<string> parametri = obj->getListaStats();

        for(auto it = parametri.begin(); it != parametri.end(); ++it)
            obj->incrementStat(*it, val / parametri.size());
    }

};

#endif // CRISTALLO_H

