#include "pietra.h"

Pietra::Pietra(int livello, int rarita, double spirito, double durezza) : Oggetto(livello, rarita, spirito), durezza_("Durezza") {
    insertStat(durezza_, durezza);
}

double Pietra::getDurezza() const {
    return getValoreStat(durezza_);
}

Pietra *Pietra::clone() const {
    return new Pietra(*this);
}

void Pietra::editDurezza(double val) {
    incrementStat(durezza_, val);
}

double Pietra::ricicla() const {
    return calcolaMana() / 2 + getValoreStat(durezza_) * getRarita();
}

void Pietra::potenzia(double mana, std::string parametro) {

    mana = sanitizeMana(mana);

    int divisore = 5;
    double incremento = mana / getLivello();

    incrementStat(durezza_, incremento * getRarita() / divisore); //Magia riceve un bonus sicuro oltre alla normale distribuzione

    list<string> statsList = getListaStats();
    if((std::find(statsList.begin(), statsList.end(), parametro) == statsList.end())) {

        incremento = incremento / statsList.size();
        for(auto i = statsList.begin(); i != statsList.end(); i++)
            incrementStat(*i, incremento);
    }
    else {
        incrementStat(parametro, incremento);
    }

    normalizza();
}
