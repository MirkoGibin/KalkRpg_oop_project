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
    Osso(int livello =1,
         int rarita =1,
         double spirito =1,
         double attacco =1,
         double difesa =1) : Oggetto(livello, rarita, spirito), attacco_("Attacco"), difesa_("Difesa") {
        insertStat(attacco_,attacco);
        insertStat(difesa_, difesa);
    }

    double getAttacco() const {
        return getValoreStat(attacco_);
    }

    double getDifesa() const {
        return getValoreStat(difesa_);
    }

    Osso* clone() const {
        return new Osso(*this);
    }

//ricicla fa la moltiplicazione della sommaStats in cui attacco e difesa sono raddoppiati, moltiplicato per livello e rarita
    double ricicla() const {
        return calcolaMana() / 2 + getRarita() * ((getValoreStat(attacco_) + getValoreStat(difesa_))) / 2 ;

    }

    void potenzia(double mana, string parametro ="") {

        mana = sanitizeMana(mana);

        double incremento = mana / getLivello();
        int divisore;

        list<string> statsList = getListaStats();

        if((std::find(statsList.begin(), statsList.end(), parametro) == statsList.end())) {
            divisore = 10;
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

        normalizza();
    }




};

#endif // OSSO_H
