#ifndef AMULETO_H
#define AMULETO_H

#include"osso.h"

class Erba;
class Unguento;
class Pietra;
class Cristallo;

class Amuleto : public Osso {
private:
    /* parameters inside stats in Amuleto:
     * spirito
     * attacco
     * difesa
     * fortuna
     */

public:
    Amuleto(int livello =0,
            int rarita =0,
            float spirito =0,
            float attacco =0,
            float difesa =0,
            float fortuna =0) : Osso(livello,rarita,spirito,attacco,difesa) {
        insertStat("Fortuna", fortuna);
    }
    float getFortuna() const {
        return getValoreStat("Fortuna");
    }

    float ricicla() {
        return 0;
    }

    void potenzia(int mana, string parametro ="") {

        int incremento = mana / getLivello();
        int divisore;

        if(parametro == "") {
            divisore = 10;
            list<string>* statsList = getListaStats();
            incremento = incremento / statsList->size();
            for(auto i = statsList->begin(); i != statsList->end(); i++)
                incrementStat(*i, incremento);
            delete statsList;
        }
        else {
            divisore = 5;
            incrementStat(parametro, incremento);
        }

        incrementStat("Fortuna", incremento * getRarita() / divisore); //Fortuna riceve un bonus sicuro oltre alla normale distribuzione

    }
};

#endif // AMULETO_H
