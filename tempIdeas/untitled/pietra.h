#ifndef PIETRA_H
#define PIETRA_H
#include"oggetto.h"
//#include "cristallo.h"

class Pietra : public Oggetto {
private:

    /* parameters inside stats in Oggetto are:
     * spirito
     * durezza
     */

public:
    //default construtor
    Pietra(int livello =0,
           int rarita =0,
           float spirito =0,
           float durezza =0) : Oggetto(livello, rarita, spirito) {
        insertStat("attacco", attacco);
        insertStat("durezza", durezza);
    }

    virtual float getDurezza() const {
        return getValoreStat("durezza");
    }

    virtual Oggetto& estrai() {
        return new Cristallo();
    }
};

#endif // PIETRA_H

