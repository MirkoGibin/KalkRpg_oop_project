#ifndef CRISTALLO_H
#define CRISTALLO_H
#include "pietra.h"
#include<typeinfo>

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
              const float attacco =0,
              const float durezza =0,
              const float magia =0) : Pietra(livello, rarita, spirito, attacco, durezza) {
        setStat("magia", magia);
    }

    //methods
    virtual double getMagia() const {
        return getValoreStat("magia");
    }
};

#endif // CRISTALLO_H

