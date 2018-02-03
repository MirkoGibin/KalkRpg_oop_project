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
    Cristallo(const int livello =1,
              const int rarita =1,
              const double spirito =1,
              const double durezza =1,
              const double magia =1) : Pietra(livello, rarita, spirito, durezza), magia_("Magia") {
        Oggetto::insertStat(magia_, magia);
        sanitizeInput();
    }

    //methods
    virtual double getMagia() const {
        return getValoreStat(magia_);
    }

    Cristallo* clone() const {
        return new Cristallo(*this);
    }

    virtual void potenzia(double mana, string parametro ="") {

        mana = sanitizeMana(mana);

        double incremento = mana * getLivello() * getRarita();
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
        if(typeid(Pietra) == typeid(*oggetto)) {

            list<string> s = getListaStats();

            if((static_cast<Pietra*>(oggetto))->getDurezza() >= 10) {
                setLivello(oggetto->getLivello());
                setRarita(oggetto->getRarita());

                int numeroStat = s.size();

                for(auto i = s.begin(); i != s.end(); ++i)
                    if(*i == magia_) incrementStat(*i, (oggetto->getSommaStats() - getSpirito()) / numeroStat);
                    else incrementStat(*i, oggetto->getValoreStat(*i) * (numeroStat - 1) / numeroStat );
            }
            else {
                for(auto i = s.begin(); i != s.end(); ++i)
                    modifyStat(*i, 1);
            }
        }
        else {
            throw OperationException(OperationException::estrazione);
        }
    }

    double ricicla() const {
        return Pietra::ricicla() + getMagia() * getRarita();
    }

    void distribuisci(Oggetto* obj) {
        double val = getMagia() / 2;

        if(getDurezza() < val + 1) {
            return;
        }

        editDurezza(-val);

        list<string> parametri = obj->getListaStats();

        for(auto it = parametri.begin(); it != parametri.end(); ++it)
            obj->incrementStat(*it, val / parametri.size());

        obj->normalizza();
    }



};

#endif // CRISTALLO_H

