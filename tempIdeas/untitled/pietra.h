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
    Pietra(int livello =1,
           int rarita =1,
           double spirito =1,
           double durezza =1) : Oggetto(livello, rarita, spirito), durezza_("Durezza") {
        insertStat(durezza_, durezza);
        sanitizeInput();
    }

    Pietra* clone() const {
        return new Pietra(*this);
    }

     double getDurezza() const {
        return getValoreStat(durezza_);
    }

     void editDurezza(double val) {
         incrementStat(durezza_, val);
     }

// ritorna il livello*rarita*(somma delle statistiche, senza lo spirito, durezza*2

    double ricicla() const {
        return calcolaMana() / 2 + getValoreStat(durezza_) * getRarita();
    }

    void potenzia(double mana, string parametro ="") {

        mana = sanitizeMana(mana);

        int divisore = 5;
        double incremento = mana / getLivello();

        incrementStat(durezza_, incremento * getRarita() / divisore); //Magia riceve un bonus sicuro oltre alla normale distribuzione

        list<string> statsList = getListaStats();
        if(parametro == "" || !(std::find(statsList.begin(), statsList.end(), parametro) != statsList.end())) {

            incremento = incremento / statsList.size();
            for(auto i = statsList.begin(); i != statsList.end(); i++)
                incrementStat(*i, incremento);
        }
        else {
                incrementStat(parametro, incremento);
        }

        normalizza();
    }
};

#endif // PIETRA_H

