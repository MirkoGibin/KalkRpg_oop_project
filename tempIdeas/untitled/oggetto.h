#ifndef OGGETTO_H
#define OGGETTO_H
#include<map>
#include<list>
#include<algorithm>
#include<mathOp.h>
#include<typeinfo>
#include<climits>
#include<tuple>

#include"operationexception.h"

using std::list;
using std::map;
using std::string;

class Oggetto {
private:

    //parameters to describe the item
    int livello_;
    int rarita_;
    string spirito_;

    map<string, double> stats;

    /* parameters inside stats in Oggetto are:
     * spirito
     */


public:
    //costruttore di default
    Oggetto(int livello =1,
            int rarita =1,
            double spirito =1) : livello_(livello), rarita_(rarita), spirito_("Spirito") {
        stats.emplace(spirito_, spirito);
        normalizza();
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
    void insertStat(string str, double db) {
        stats.emplace(str, db);
    }

    void incrementStat(string stat, double value){
        stats[stat] += value;
    }

    bool modifyStat(string str, double db) { //GESTIONE DEGLI ERRORI
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
        double max = -1;
        double min = INT_MAX;

        string statMax;
        string statMin;

        for(auto it = stats.begin(); it != stats.end(); it++) {
            if(it->second > max) {
                max = it->second;
                statMax= it->first;
            }
            else {
                if(it->second <= min) { // a parità di valore, voglio la stat più in fondo alla lista
                    min = it->second;
                    statMin= it->first;
                }
            }
        }

        return std::make_pair(statMin, statMax);
    }

    double getLivello() const {
       return livello_;
    }
    double getRarita() const {
        return rarita_;
    }
    double getValoreStat(string str) const {
        return stats.at(str);
    }

    double getSpirito() const {
        return getValoreStat(spirito_);
    }

    list<string> getListaStats()  const {
        list<string> keyList;
        for(map<string, double>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            keyList.push_back(it->first);
        return keyList;
    }

    double getSommaStats() const {
        double sum = 0;
        for(map<string, double>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            sum+=it->second;
        return sum;
    }

    double calcolaMana() const {
        return getSommaStats()*getLivello();
    }



//------------OPERAZIONI
    void normalizza() {
        int maxStat = 150;
        if(getLivello()*maxStat*stats.size() <= calcolaMana()) {
            double percentualeRiduzione=getLivello()*maxStat*stats.size()/calcolaMana();
            mathOp::doMultiplyOnMap(stats, percentualeRiduzione);
        }
    }

    void sanitizeInput() {
        if(livello_ < 1)
            livello_ = 1;
        else
            if(livello_ >10)
                livello_ = 10;

        if(rarita_ < 1)
            rarita_ = 1;
        else
            if(rarita_>10)
                rarita_ = 10;


        double sum = 0;

        for(auto it = stats.begin(); it != stats.end(); ++it) {
            if(it->second < 1) it->second = 1;
            else sum += it->second;
        }

      if(sum > 150 * livello_ * stats.size())
         normalizza();
      }

    void combina(Oggetto* object) {
        map<string, double> percentInvMap = stats; //copiata la mappa dell'oggetto di invocazione
        map<string, double> percentParMap = object->stats; //copiata la mappa dell'oggetto di invocazione


        double toMultiplyInv=getLivello()/calcolaMana();
        double toMultiplyPar=object->getLivello()/object->calcolaMana();

        mathOp::doMultiplyOnMap(percentInvMap, toMultiplyInv);
        mathOp::doMultiplyOnMap(percentParMap, toMultiplyPar);

        list<string> InvMenoPar=mathOp::chiaviAmenoB(percentInvMap, percentParMap);
        list<string> ParMenoInv=mathOp::chiaviAmenoB(percentParMap, percentInvMap);
        list<string> InvePar=mathOp::chiaviAeB(percentInvMap, percentParMap);

        for(list<string>::const_iterator it = InvePar.begin(); it!=InvePar.end(); ++it) {
            percentInvMap[*it]=(percentInvMap.at(*it) + percentParMap.at(*it))/2;
        }

        double daDistribuire; //somma da distribuire sulle stats di a non presenti in b
        for(list<string>::const_iterator it=ParMenoInv.begin(); it!=ParMenoInv.end(); ++it) {
            daDistribuire+=percentParMap.at(*it);
        }

        daDistribuire=daDistribuire/InvMenoPar.size();
        for(list<string>::const_iterator it=InvMenoPar.begin(); it!=InvMenoPar.end(); ++it) {
            percentInvMap[*it] =(percentInvMap.at(*it) + daDistribuire)/2;
        }

        for(map<string,double>::const_iterator it=percentInvMap.begin(); it!=percentInvMap.end(); ++it) {
            stats[it->first] = stats.at(it->first)*getLivello() + it->second*object->calcolaMana();
        }
        //ora bisogna normalizzare stats a seconda del livello.
        normalizza();
    }



    //operazioni

    virtual double ricicla() const = 0;

    virtual void potenzia(double mana, string parametro ="") = 0;

    void trasformaDa(const Oggetto *obj) {

        if(getListaStats().size() > obj->getListaStats().size()) {
            throw OperationException(OperationException::trasformazione);
        }

        setLivello(obj->getLivello());
        setRarita(obj->getRarita());
        list<string> parametri = obj->getListaStats();
        double val = 0;
        for(auto i = parametri.begin(); i != parametri.end(); ++i) {
            if(!modifyStat(*i, obj->getValoreStat(*i)/2))
                val += obj->getValoreStat(*i);
        }

        parametri.clear();

//FARE ATTENZIONE QUI: la prossima parametri risulta vuota.
        if(val > 0) {
            for(auto it = stats.begin(); it != stats.end(); ++it){
                if(it->second == 1)
                    parametri.push_back(it->first);
            }

            int par=parametri.size();
            if(par > 0) { // c'è almeno un parametro caratteristico da settare
                val = val/par;

                for(auto i = parametri.begin(); i != parametri.end(); i++)
                  modifyStat(*i, val * getRarita());
            }
            normalizza();

        }
//------------------------------------
    }

    void crea(double mana, int livello, int rarita, string statistica = "") { //PRE = statistica è vuoto o è un valore valido

        setLivello(livello);
        setRarita(rarita);

        list<string> parametri = getListaStats();
        double sumStats=mana/(livello*rarita);

        if(statistica != "" && std::find(parametri.begin(), parametri.end(), statistica) != parametri.end()) { //RICHIEDE <ALGORITHM>
            modifyStat(statistica, sumStats/2);
            sumStats=sumStats/2;
            parametri.remove(statistica);
        }

        sumStats=sumStats/parametri.size();

        for(list<string>::const_iterator it=parametri.begin(); it!=parametri.end(); ++it)
            modifyStat(*it, sumStats);

        normalizza();
    }

};

#endif // OGGETTO_H
