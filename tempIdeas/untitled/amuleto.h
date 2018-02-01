#ifndef AMULETO_H
#define AMULETO_H

#include"osso.h"

class Erba;
class Unguento;
class Pietra;
class Cristallo;

class Amuleto : public Osso {
private:
    /* parameters inside stats in Amuleto:
     * spirito
     * attacco
     * difesa
     * fortuna
     */
    string fortuna_;

public:
    Amuleto(int livello =0,
            int rarita =0,
            float spirito =0,
            float attacco =0,
            float difesa =0,
            float fortuna =0) : Osso(livello,rarita,spirito,attacco,difesa), fortuna_("Fortuna") {
        insertStat(fortuna_, fortuna);
    }
    float getFortuna() const {
        return getValoreStat(fortuna_);
    }

    Amuleto* clone() const {
        return new Amuleto(*this);
    }

    float ricicla() const {
        return Osso::ricicla() + getValoreStat(fortuna_) * getRarita();
    }

    void potenzia(int mana, string parametro ="") {

        int divisore;

        if(getRarita() > 6 && getLivello() > 6)
            divisore = 10;
        else
            divisore = 15;

        incrementStat(fortuna_, mana * getLivello() * getRarita() / divisore); //Fortuna riceve un bonus sicuro oltre alla normale distribuzione

        Osso::potenzia(mana, parametro);
    }

    virtual void estraiDa(Oggetto* oggetto) {
        if(typeid(Osso*) == typeid(*oggetto)) {
            setLivello(oggetto->getLivello());
            setRarita(oggetto->getRarita());
            list<string> s = getListaStats();
            int numeroStat = s.size();

            for(auto i = s.begin(); i != s.end(); ++i) {
                if(*i == fortuna_)
                    incrementStat(*i, oggetto->getSommaStats() / numeroStat);
                else
                    incrementStat(*i,  oggetto->getValoreStat(*i) * (numeroStat - 1) / numeroStat );
            }

        }
        else {
           return;// throw Errore("estrai");
        }

    }

    Oggetto* duplica(Oggetto * obj) {

        list<string> parametri = obj->getListaStats();
        float val = obj->getSommaStats() / parametri.size();

        Oggetto* newObj = obj->clone();

        if(getFortuna() < val ) {
            modifyStat(fortuna_, 1);
            for(auto it = parametri.begin(); it != parametri.end(); it++) {
                newObj->modifyStat(*it, 1);
            }
        }
        else {
            incrementStat(fortuna_, -val);

            if(getRarita() < 5) {
                for(auto it = parametri.begin(); it != parametri.end(); it++) {
                    if(newObj->getValoreStat(*it) > val/2)
                        newObj->modifyStat(*it, val/2);
                }
            }
        }

        return newObj;

    }

};

#endif // AMULETO_H
