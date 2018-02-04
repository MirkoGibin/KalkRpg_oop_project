#ifndef UNGUENTO_H
#define UNGUENTO_H
#include "oggetto.h"
#include "erba.h"

class Amuleto;
class Cristallo;
class Pietra;
class Osso;

class Unguento : public Erba{
    string energia_;
public:
    Unguento(int livello =1,
             int rarita =1,
             double spirito =1,
             double vitalita =1,
             double energia =1) : Erba(livello, rarita, spirito, vitalita), energia_("Energia") {
        insertStat(energia_, energia);
    }
    //METODI DI GET
    double getEnergia() const {
        return getValoreStat(energia_);
    }

    //METODI DI SUPPORTO
    Unguento*clone() const {
        return new Unguento(*this);
    }

    //OPERAZIONI CALCOLATRICE
    void potenzia(double mana, string parametro ="") {

        mana = sanitizeMana(mana);
        int divisore;

        if(getRarita() > 6)
            divisore = 9;
        else
            divisore = 12;

        incrementStat(energia_, mana * getLivello() * getRarita() / divisore); //Energia riceve un bonus sicuro oltre alla normale distribuzione
        Erba::potenzia(mana, parametro);
    }

    double ricicla() const {
        return Erba::ricicla() + getValoreStat(energia_) * getRarita();
    }

    void estraiDa(Oggetto* oggetto) {
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

    void ripara(Oggetto* obj) {

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



};

#endif // UNGUENTO_H
