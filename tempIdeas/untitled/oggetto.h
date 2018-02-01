#ifndef OGGETTO_H
#define OGGETTO_H
#include<map>
#include<list>
#include<algorithm>
#include<mathOp.h>
#include<typeinfo>
#include<climits>
#include<tuple>
#include"errore.h"

using std::list;
using std::map;
using std::string;

class Oggetto {
private:

    //parameters to describe the item
    int livello_;
    int rarita_;
    string spirito_;

    map<string, float> stats;

    /* parameters inside stats in Oggetto are:
     * spirito
     */
    void normalizza() {
        if(getLivello()*150 <= calcolaMana()) {
            float percentualeRiduzione=getLivello()*150/calcolaMana();
            mathOp::doMultiplyOnMap(stats, percentualeRiduzione);

        }
    }

public: /* void incrementStat(list<string> stats, float value) {
        for(auto i = stats.begin(); i != stats.end(); ++i)
            incrementStat(*i, value);
    }*/
    //costruttore di default
    Oggetto(int livello =0,
            int rarita =0,
            float spirito =0) : livello_(livello), rarita_(rarita), spirito_("Spirito") {
        stats.emplace(spirito_, spirito);
    }

    //distruttore virtuale
    virtual ~Oggetto() {}

    virtual Oggetto* clone() const =0;

//---------METODI DI SET
    void setLivello(int livello) {
        livello_=livello;
    }
    void setRarita(int rarita) {
        rarita_=rarita;
    }
    void insertStat(string str, float db) {
        stats.emplace(str, db);
    }

    void incrementStat(string stat, float value){
        stats[stat] += value;
    }

    bool modifyStat(string str, float db) { //GESTIONE DEGLI ERRORI
        bool trovata=true;
        if(stats.count(str)) {
            stats[str] = db;
            return trovata;
        }
        else
            return !trovata;
    }

//------------METODI DI GET
    //ritorna una coppia di stringhe. La prima indica la statistica con il minor valore, la seconda la statistica con il maggior valore.
    std::pair<string,string> findMinMaxStat() const {
        //std::pair<string, string> minmax;
        float max = -1;
        float min = INT_MAX;

        string statMax;
        string statMin;

        for(auto it = stats.begin(); it != stats.end(); it++) {
            if(it->second > max) {
                max = it->second;
                //minmax.second
                statMax= it->first;
            }
            else {
                if(it->second <= min) { // a parità di valore, voglio la stat più in fondo alla lista
                    min = it->second;
                    //minmax.first
                    statMin= it->first;
                }
            }
        }

        return std::make_pair(statMin, statMax);
    }

    float getLivello() const {
       return livello_;
    }
    float getRarita() const {
        return rarita_;
    }
    float getValoreStat(string str) const {
        return stats.at(str);
    }

    float getSpirito() const {
        return getValoreStat(spirito_);
    }

    list<string> getListaStats()  const {
        list<string> keyList;
        for(map<string, float>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            keyList.push_back(it->first);
        return keyList;
    }

    float getSommaStats() const {
        float sum = 0;
        for(map<string, float>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            sum+=it->second;
        return sum;
    }

    float calcolaMana() const {
        return getSommaStats()*getLivello();
    }



//------------OPERAZIONI
    void combina(Oggetto* object) {
        map<string, float> percentInvMap = stats; //copiata la mappa dell'oggetto di invocazione
        map<string, float> percentParMap = object->stats; //copiata la mappa dell'oggetto di invocazione


        float toMultiplyInv=getLivello()/calcolaMana();
        float toMultiplyPar=object->getLivello()/object->calcolaMana();

        mathOp::doMultiplyOnMap(percentInvMap, toMultiplyInv);
        mathOp::doMultiplyOnMap(percentParMap, toMultiplyPar);

        list<string> InvMenoPar=mathOp::chiaviAmenoB(percentInvMap, percentParMap);
        list<string> ParMenoInv=mathOp::chiaviAmenoB(percentParMap, percentInvMap);
        list<string> InvePar=mathOp::chiaviAeB(percentInvMap, percentParMap);

        for(list<string>::const_iterator it = InvePar.begin(); it!=InvePar.end(); ++it) {
            percentInvMap[*it]=(percentInvMap.at(*it) + percentParMap.at(*it))/2;
        }

        float daDistribuire; //somma da distribuire sulle stats di a non presenti in b
        for(list<string>::const_iterator it=ParMenoInv.begin(); it!=ParMenoInv.end(); ++it) {
            daDistribuire+=percentParMap.at(*it);
        }

        daDistribuire=daDistribuire/InvMenoPar.size();
        for(list<string>::const_iterator it=InvMenoPar.begin(); it!=InvMenoPar.end(); ++it) {
            percentInvMap[*it] =(percentInvMap.at(*it) + daDistribuire)/2;
        }

        for(map<string,float>::const_iterator it=percentInvMap.begin(); it!=percentInvMap.end(); ++it) {
            stats[it->first] = stats.at(it->first)*getLivello() + it->second*object->calcolaMana();
        }
        //ora bisogna normalizzare stats a seconda del livello.
        normalizza();
    }



    //operazioni

    virtual float ricicla() const = 0;

    virtual void potenzia(int mana, string parametro ="") = 0;

    void trasformaDa(Oggetto *obj) {
        //if(dynamic_cast<Erba*>(obj)) {} //throw eccezione
        if(typeid(*this) == typeid(*obj)) {} //throw eccezione

        if(getListaStats().size() > obj->getListaStats().size()) {} //throw eccezione

        setLivello(obj->getLivello());
        setRarita(obj->getRarita());
        list<string> parametri = obj->getListaStats();
        int val = 0;
        for(auto i = parametri.begin(); i != parametri.end(); ++i) {
            if(!modifyStat(*i, obj->getValoreStat(*i)/2))
                val += obj->getValoreStat(*i);
        }

        parametri.clear();

        if(val > 0) {
            for(auto it = stats.begin(); it != stats.end(); ++it){
                if(it->second == 0)
                    parametri.push_back(it->first);
            }

            val /= parametri.size();

            for(auto i = parametri.begin(); i != parametri.end(); i++)
                modifyStat(*i, val * getRarita());

        }
    }

    void crea(float mana, int livello, int rarita, string statistica) { //PRE = statistica è vuoto o è un valore valido

        setLivello(livello);
        setRarita(rarita);

        list<string> parametri = getListaStats();
        float sumStats=mana/(livello*rarita);

        if(statistica != "" && std::find(parametri.begin(), parametri.end(), statistica) != parametri.end()) { //RICHIEDE <ALGORITHM>
            modifyStat(statistica, sumStats/2);
            sumStats=sumStats/2;
            parametri.remove(statistica);
        }

        sumStats=sumStats/parametri.size();

        for(list<string>::const_iterator it=parametri.begin(); it!=parametri.end(); ++it)
            modifyStat(*it, sumStats);
    }

};

#endif // OGGETTO_H
