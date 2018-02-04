#include "amuleto.h"

Amuleto::Amuleto(int livello, int rarita, double spirito, double attacco, double difesa, double fortuna) : Osso(livello,rarita,spirito,attacco,difesa), fortuna_("Fortuna") {
    insertStat(fortuna_, fortuna);
}

double Amuleto::getFortuna() const {
    return getValoreStat(fortuna_);
}

Amuleto *Amuleto::clone() const {
    return new Amuleto(*this);
}

double Amuleto::ricicla() const {
    return Osso::ricicla() + getValoreStat(fortuna_) * getRarita();
}

void Amuleto::potenzia(double mana, std::string parametro) {

    mana = sanitizeMana(mana);

    int divisore;

    if(getRarita() > 6 && getLivello() > 6)
        divisore = 10;
    else
        divisore = 15;

    incrementStat(fortuna_, mana * getLivello() * getRarita() / divisore); //Fortuna riceve un bonus sicuro oltre alla normale distribuzione

    Osso::potenzia(mana, parametro);

}

void Amuleto::estraiDa(Oggetto *oggetto) {
    if(typeid(Osso) == typeid(*oggetto)) {
        setLivello(oggetto->getLivello());
        setRarita(oggetto->getRarita());
        list<string> s = getListaStats();
        int numeroStat = s.size();

        for(auto i = s.begin(); i != s.end(); ++i) {
            if(*i == fortuna_)
                incrementStat(*i, oggetto->getSommaStats() / numeroStat);
            else
                incrementStat(*i,  oggetto->getValoreStat(*i) * (numeroStat - 1) / numeroStat );
        }

    }
    else {
        throw OperationException(OperationException::estrazione);
    }

}

Oggetto *Amuleto::duplica(const Oggetto *obj) {

    list<string> parametri = obj->getListaStats();
    double val = obj->getSommaStats() / parametri.size();

    Oggetto* newObj = obj->clone();

    if(getFortuna() < val + 1) {
        modifyStat(fortuna_, 1);
        for(auto it = parametri.begin(); it != parametri.end(); it++) {
            newObj->modifyStat(*it, 1);
        }
    }
    else {
        incrementStat(fortuna_, -val);

        if(getRarita() < 5) {
            for(auto it = parametri.begin(); it != parametri.end(); it++) {
                if(newObj->getValoreStat(*it) > val/2)
                    newObj->modifyStat(*it, val/2);
            }
        }
    }

    return newObj;

}
