#include "unguento.h"


Unguento::Unguento(int livello, int rarita, double spirito, double vitalita, double energia) : Erba(livello, rarita, spirito, vitalita), energia_("Energia") {
    insertStat(energia_, energia);
}

double Unguento::getEnergia() const {
    return getValoreStat(energia_);
}

Unguento *Unguento::clone() const {
    return new Unguento(*this);
}

void Unguento::potenzia(double mana, std::string parametro) {

    mana = sanitizeMana(mana);
    int divisore;

    if(getRarita() > 6)
        divisore = 9;
    else
        divisore = 12;

    incrementStat(energia_, mana * getLivello() * getRarita() / divisore); //Energia riceve un bonus sicuro oltre alla normale distribuzione
    Erba::potenzia(mana, parametro);
}

double Unguento::ricicla() const {
    return Erba::ricicla() + getValoreStat(energia_) * getRarita();
}

void Unguento::estraiDa(Oggetto *oggetto) {
    if(typeid(Erba) == typeid(*oggetto)) {
        setLivello(oggetto->getLivello());
        setRarita(oggetto->getRarita());
        list<string> s = getListaStats();
        int numeroStat = s.size();

        for(auto i = s.begin(); i != s.end(); ++i)
            if(*i == energia_) {
                double val = oggetto->getSommaStats() / numeroStat;
                if(val<1) val = 1;
                modifyStat(*i, val);
            }
            else
                if(getRarita() > 7)
                    modifyStat(*i,  oggetto->getValoreStat(*i));
                else {
                    double val = oggetto->getValoreStat(*i) *(numeroStat - 1) / numeroStat;
                    if(val < 1) val =1;
                    modifyStat(*i, val);
                }
    }
    else {
        throw OperationException(OperationException::estrazione);
    }
}

void Unguento::ripara(Oggetto *obj) {

    std::pair<string, string> minmax = obj->findMinMaxStat();

    double maxValue = obj->getValoreStat(minmax.second);
    double diff = maxValue - obj->getValoreStat(minmax.first);

    if(getValoreStat(energia_) < diff + 1) {
        return;
    }

    incrementStat(energia_, -diff);

    if(getRarita() > 7) {
        list<string> parametri = obj->getListaStats();
        for(auto it = parametri.begin(); it != parametri.end(); it++) {
            obj->modifyStat(*it, maxValue);
        }
    }
    else {
        obj->modifyStat(minmax.first, maxValue);
    }
    obj->normalizza();
}
