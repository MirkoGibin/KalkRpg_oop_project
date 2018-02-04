#include "osso.h"

Osso::Osso(int livello, int rarita, double spirito, double attacco, double difesa) : Oggetto(livello, rarita, spirito), attacco_("Attacco"), difesa_("Difesa") {
    insertStat(attacco_,attacco);
    insertStat(difesa_, difesa);
}

double Osso::getAttacco() const {
    return getValoreStat(attacco_);
}

double Osso::getDifesa() const {
    return getValoreStat(difesa_);
}

Osso *Osso::clone() const {
    return new Osso(*this);
}

double Osso::ricicla() const {
    return calcolaMana() / 2 + getRarita() * ((getValoreStat(attacco_) + getValoreStat(difesa_))) / 2 ;

}

void Osso::potenzia(double mana, std::string parametro) {

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
