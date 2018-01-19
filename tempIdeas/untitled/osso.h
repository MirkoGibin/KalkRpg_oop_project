#ifndef OSSO_H
#define OSSO_H

#include<typeinfo>

#include"oggetto.h"

class Erba;
class Unguento;
class Pietra;
class Cristallo;

class Osso : public Oggetto {
private:

    /* parameters inside stats in Osso are:
     * spirito
     * attacco
     * difesa
     */

public:
    Osso(int livello =0,
         int rarita =0,
         float spirito =0,
         float attacco =0,
         float difesa =0) : Oggetto(livello, rarita, spirito) {
        insertStat("attacco",attacco);
        insertStat("difesa", difesa);
    }

    float getAttacco() const {
        return getValoreStat("attacco");
    }

    float getDifesa() const {
        return getValoreStat("difesa");
    }

//ricicla fa la moltiplicazione della sommaStats in cui attacco e difesa sono raddoppiati, moltiplicato per livello e rarita
    float ricicla() {
        float mana=(getSommaStats() + getAttacco() + getDifesa()) * getLivello() * getRarita();
        delete this;
        return mana;
    }

/*    void ottieniDa(Pietra* pietra) {
        if(typeid(pietra) == typeid(pietra)) { //tipo dinamico deve essere uguale a tipo statico
            float pSpir=pietra->getSpirito();
            float pDur=pietra->getDurezza();

            float oSpir=pSpir*0.50;
            float oAtt=pDur;
            float oDif=pDur*0.50;
            setLivello(pietra->getLivello());
            setRarita(pietra->getRarita());
            modifyStat("spirito", oSpir);
            modifyStat("attacco", oAtt);
            modifyStat("difesa", oDif);
        } else {
            //lancia eccezione
        }
    }

    void ottieniDa(Erba* erba) {
    /*    if(typeid(erba) == typeid(*erba)) {

        } else {
            //lancia eccezione contro parametri illegali
        }

    }

    void estraiDa(Oggetto*obj) {
        //lancia eccezione, non si puo' invocare questo metodo a questo livello
    }*/




};

#endif // OSSO_H
