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
    Erba(int livello =1,
         int rarita =1,
         double spirito =1,
         double vitalita =1) : Oggetto(livello, rarita, spirito), vitalita_("Vitalità") {
            insertStat(vitalita_, vitalita);
            sanitizeInput();
    }

    double getVitalita() const {
        return getValoreStat(vitalita_);
    }

    Erba* clone() const {
        return new Erba(*this);
    }

     double ricicla() const {
        return calcolaMana() / 2 + getValoreStat(vitalita_) * getRarita();

    }

     void potenzia(double mana, string parametro ="") {

         int divisore = 10;
         double incremento = mana / getLivello();

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

         normalizza();
     }





};

#endif // ERBA_H
