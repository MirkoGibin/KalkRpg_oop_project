#ifndef PIETRA_H
#define PIETRA_H
#include"oggetto.h"

class Osso;
class Amuleto;
class Erba;
class Unguento;

class Pietra : public Oggetto {
private:

    /* parameters inside stats in Oggetto are:
     * spirito
     * attacco
     * durezza
     */
    string durezza_;

public:
    //default construtor
    Pietra(int livello =0,
           int rarita =0,
           float spirito =0,
           float durezza =0) : Oggetto(livello, rarita, spirito), durezza_("Durezza") {
        insertStat(durezza_, durezza);
    }

     float getDurezza() const {
        return getValoreStat(durezza_);
    }

// ritorna il livello*rarita*(somma delle statistiche, senza lo spirito, durezza*2
    float ricicla() {
        return getLivello()*getRarita()*(getSommaStats()-getSpirito()+getDurezza());

    }

    float ricicla() const {
        return getMana() / 2 + getValoreStat(durezza_) * getRarita();
    }
};

#endif // PIETRA_H

