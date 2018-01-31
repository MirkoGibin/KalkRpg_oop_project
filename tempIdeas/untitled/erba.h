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
    string vitalita_;
public:
    Erba(int livello =0,
         int rarita =0,
         float spirito =0,
         float vitalita =0) : Oggetto(livello, rarita, spirito), vitalita_("Vitalità") {
            insertStat(vitalita_, vitalita);
    }

    float getVitalita() const {
        return getValoreStat(vitalita_);
    }

     float ricicla() const {
        return getMana() / 2 + getValoreStat(vitalita_) * getRarita();

    }


};

#endif // ERBA_H
