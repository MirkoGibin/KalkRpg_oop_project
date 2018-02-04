#include "erba.h"


Erba::Erba(int livello, int rarita, double spirito, double vitalita) : Oggetto(livello, rarita, spirito), vitalita_("Vitalità") {
    insertStat(vitalita_, vitalita);
}

double Erba::getVitalita() const {
    return getValoreStat(vitalita_);
}

Erba *Erba::clone() const {
    return new Erba(*this);
}

double Erba::ricicla() const {
    return calcolaMana() / 2 + getValoreStat(vitalita_) * getRarita();

}

void Erba::potenzia(double mana, std::string parametro) {

    mana = sanitizeMana(mana);

    int divisore = 10;
    double incremento = mana / getLivello();

    incrementStat(vitalita_, incremento * getRarita() / divisore); //Vitalità riceve un bonus sicuro oltre alla normale distribuzione

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
