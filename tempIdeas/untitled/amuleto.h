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
        if(dynamic_cast<Osso*>(oggetto)) {
            setLivello(oggetto->getLivello());
            setRarita(oggetto->getRarita());
            list<string> s = oggetto->getListaStats();
            int numeroStat = s.size();

            for(auto i = s.begin(); i != s.end(); ++i) {
                if(*i == fortuna_ && getRarita() > 7)
                    incrementStat(*i, oggetto->getSommaStats() / numeroStat);
                else
                    incrementStat(*i, getValoreStat(*i) / numeroStat * (numeroStat - 1));
            }

        }
        else {}
                //eccezione
    }

};

#endif // AMULETO_H
