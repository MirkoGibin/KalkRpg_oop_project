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
    string attacco_;
    string difesa_;


public:
    Osso(int livello =0,
         int rarita =0,
         float spirito =0,
         float attacco =0,
         float difesa =0) : Oggetto(livello, rarita, spirito), attacco_("Attacco"), difesa_("Difesa") {
        insertStat(attacco_,attacco);
        insertStat(difesa_, difesa);
    }

    float getAttacco() const {
        return getValoreStat(attacco_);
    }

    float getDifesa() const {
        return getValoreStat(difesa_);
    }

    Osso* clone() const {
        return new Osso(*this);
    }

//ricicla fa la moltiplicazione della sommaStats in cui attacco e difesa sono raddoppiati, moltiplicato per livello e rarita
    float ricicla() const {
        return calcolaMana() / 2 + (getValoreStat(attacco_) + getValoreStat(difesa_)) / 2 * getRarita();

    }

    void potenzia(int mana, string parametro ="") {

        int incremento = mana / getLivello();
        int divisore;

        if(parametro == "") {
            divisore = 10;
            list<string> statsList = getListaStats();
            incremento = incremento / statsList.size();
            for(auto i = statsList.begin(); i != statsList.end(); i++)
                incrementStat(*i, incremento);
        }
        else {
            divisore = 5;
            incrementStat(parametro, incremento);
        }

        incrementStat(attacco_, incremento * getRarita() / (2*divisore));
        incrementStat(difesa_, incremento * getRarita() / (2*divisore));
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
        if(typeid(erba) == typeid(*erba)) {

        } else {
            //lancia eccezione contro parametri illegali
        }

    }

    void estraiDa(Oggetto*obj) {
        //lancia eccezione, non si puo' invocare questo metodo a questo livello
    }*/




};

#endif // OSSO_H
