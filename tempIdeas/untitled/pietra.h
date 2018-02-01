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

    Pietra* clone() const {
        return new Pietra(*this);
    }

     float getDurezza() const {
        return getValoreStat(durezza_);
    }

     void editDurezza(float val) {
         incrementStat(durezza_, val);
     }

// ritorna il livello*rarita*(somma delle statistiche, senza lo spirito, durezza*2

    float ricicla() const {
        return calcolaMana() / 2 + getValoreStat(durezza_) * getRarita();
    }

    void potenzia(int mana, string parametro ="") {

        int divisore = 5;
        int incremento = mana / getLivello();

        incrementStat(durezza_, incremento * getRarita() / divisore); //Magia riceve un bonus sicuro oltre alla normale distribuzione

        if(parametro == "") {
            list<string> statsList = getListaStats();
            incremento = incremento / statsList.size();
            for(auto i = statsList.begin(); i != statsList.end(); i++)
                incrementStat(*i, incremento);
        }
        else {
                incrementStat(parametro, incremento);
        }
    }
};

#endif // PIETRA_H

