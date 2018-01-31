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

    Erba* clone() const {
        return new Erba(*this);
    }

     float ricicla() const {
        return calcolaMana() / 2 + getValoreStat(vitalita_) * getRarita();

    }

     void potenzia(int mana, string parametro ="") {

         int divisore = 10;
         int incremento = mana / getLivello();

         incrementStat(vitalita_, incremento * getRarita() / divisore); //Vitalità riceve un bonus sicuro oltre alla normale distribuzione

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

#endif // ERBA_H
