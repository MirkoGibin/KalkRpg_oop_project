#ifndef ERBA_H
#define ERBA_H
#include "oggetto.h"
#include <typeinfo>

class Erba : public Oggetto{
    /* le stats dentro Erba sono:
     * spirito
     * puntiVita
     */
public:
    Erba(int livello =0,
         int rarita =0,
         float spirito =0,
         float puntiVita =0) : Oggetto(livello, rarita, spirito) {
            insertStat("puntiVita", puntiVita);
    }

    float getPuntiVita() const {
        return getValoreStat("puntiVita");
    }

    virtual float ricicla() {
        float mana = getSommaStats() - getSpirito()/2 + 2 * getPuntiVita() + getRarita() * getRarita();
        delete this;
        return mana;
    }
};

#endif // ERBA_H
