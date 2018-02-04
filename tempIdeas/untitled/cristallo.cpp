#include "cristallo.h"

Cristallo::Cristallo(const int livello, const int rarita, const double spirito, const double durezza, const double magia) : Pietra(livello, rarita, spirito, durezza), magia_("Magia") {
    Oggetto::insertStat(magia_, magia);
}

double Cristallo::getMagia() const {
    return getValoreStat(magia_);
}

Cristallo *Cristallo::clone() const {
    return new Cristallo(*this);
}

void Cristallo::potenzia(double mana, std::string parametro) {

    mana = sanitizeMana(mana);

    double incremento = mana * getLivello() * getRarita();
    int divisore =1;

    if(parametro == "Spirito") {
        divisore = 15;
        incrementStat(parametro, incremento/getMagia());
        incrementStat(magia_, incremento * getRarita() / divisore);
    }
    else {
        divisore = 10;
        incrementStat(magia_, incremento * getRarita() / divisore);
        Pietra::potenzia(mana, parametro);
    }
    normalizza();
}

double Cristallo::ricicla() const {
    return Pietra::ricicla() + getMagia() * getRarita();
}

void Cristallo::estraiDa(Oggetto *oggetto) {
    if(typeid(Pietra) == typeid(*oggetto)) {

        list<string> s = getListaStats();

        if((static_cast<Pietra*>(oggetto))->getDurezza() >= 10) {
            setLivello(oggetto->getLivello());
            setRarita(oggetto->getRarita());

            int numeroStat = s.size();

            for(auto i = s.begin(); i != s.end(); ++i)
                if(*i == magia_) incrementStat(*i, (oggetto->getSommaStats() - oggetto->getSpirito()) / numeroStat);
                else incrementStat(*i, oggetto->getValoreStat(*i) * (numeroStat - 1) / numeroStat );
        }
        else {
            for(auto i = s.begin(); i != s.end(); ++i)
                modifyStat(*i, 1);
        }
    }
    else {
        throw OperationException(OperationException::estrazione);
    }
}

void Cristallo::distribuisci(Oggetto *obj) {
    double val = getMagia() / 2;

    if(getDurezza() < val + 1) {
        return;
    }

    editDurezza(-val);

    list<string> parametri = obj->getListaStats();

    for(auto it = parametri.begin(); it != parametri.end(); ++it)
        obj->incrementStat(*it, val / parametri.size());

    obj->normalizza();
}
