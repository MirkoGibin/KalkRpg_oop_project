#ifndef ERBA_H
#define ERBA_H
#include <typeinfo>
#include <list>
#include "oggetto.h"

class Erba : public Oggetto{
    /* le stats dentro Erba sono:
     * spirito
     * Vitalità
     */
public:
    Erba(int livello =0,
         int rarita =0,
         float spirito =0,
         float vitalita =0) : Oggetto(livello, rarita, spirito) {
            insertStat("Vitalità", vitalita);
    }

    float getVitalita() const {
        return getValoreStat("Vitalità");
    }

    virtual float ricicla() {
        float mana = getSommaStats() - getSpirito()/2 + 2 * getVitalita() + getRarita() * getRarita();
        delete this;
        return mana;
    }


};

#endif // ERBA_H
