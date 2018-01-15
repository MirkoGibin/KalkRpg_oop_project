#ifndef PIETRA_H
#define PIETRA_H
#include"oggetto.h"

class Pietra : public Oggetto {
private:

    /* parameters inside stats in Oggetto are:
     * spirito
     * attacco
     * durezza
     */

public:
    //default construtor
    Pietra(int livello =0,
           int rarita =0,
           float spirito =0,
           float durezza =0) : Oggetto(livello, rarita, spirito) {
        insertStat("durezza", durezza);
    }

    float getAttacco() const {
        return getValoreStat("attacco");
    }
    float getDurezza() const {
        return getValoreStat("durezza");
    }

// ritorna il livello*rarita*(somma delle statistiche, senza lo spirito, durezza*2
    float ricicla() {
        float mana=getLivello()*getRarita()*(getSommaStats()-getSpirito()+getDurezza());
        delete *this;
        return mana;
    }
};

#endif // PIETRA_H

