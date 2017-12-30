#ifndef PIETRA_H
#define PIETRA_H
#include"oggetto.h"
#include "cristallo.h"

class Pietra : public Oggetto {
private:

    /* parameters inside stats in Oggetto are:
     * spirito
     * attacco
     * durezza
     */

public:
    //default construtor
    Pietra(float livello =0,
           float rarita =0,
           float spirito =0,
           float attacco =0,
           float durezza =0) : Oggetto(livello, rarita, spirito) {
        insertStat("attacco", attacco);
        insertStat("durezza", durezza);
    }

    virtual float getAttacco() const {
        return getValoreStat("attacco");
    }
    virtual float getDurezza() const {
        return getValoreStat("durezza");
    }

    virtual Oggetto& estrai() {
        return new Cristallo();
    }
};

#endif // PIETRA_H

