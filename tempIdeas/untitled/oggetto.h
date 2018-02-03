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
        bool trovata=false;
        if(stats.count(str)) {
            stats[str] = db;
            trovata=true;
        }
        return trovata;
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

    int getLivello() const {
       return livello_;
    }
    int getRarita() const {
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
        livello_ = sanitizeLivRar(livello_);
        rarita_ = sanitizeLivRar(rarita_);

        double sum = 0;

        for(auto it = stats.begin(); it != stats.end(); ++it) {
            if(it->second < 1) it->second = 1;
            else
                if(it->second > 150) it->second = 150;

            sum += it->second;
        }


      if(sum > 150 * livello_ * stats.size())
         normalizza();
      }

    static double sanitizeMana(double mana) {
        if(mana > 6000) mana = 6000;
        else
            if(mana < 1) mana = 1;

        return mana;
    }

    static int sanitizeLivRar(int l) {
        if(l < 1) l = 1;
        else
            if(l > 10) l = 10;

        return l;
    }

    void combina(Oggetto* object) {
        map<string, double> invMap = stats; //copiata la mappa dell'oggetto di invocazione
        map<string, double> parMap = object->stats; //copiata la mappa dell'oggetto di invocazione


        double toMultiplyInv=getLivello()/calcolaMana();
        double toMultiplyPar=object->getLivello()/object->calcolaMana();

        mathOp::doMultiplyOnMap(invMap, toMultiplyInv);
        mathOp::doMultiplyOnMap(parMap, toMultiplyPar);

        list<string> InvMenoPar=mathOp::chiaviAmenoB(invMap, parMap);
        list<string> ParMenoInv=mathOp::chiaviAmenoB(parMap, invMap);
        list<string> InvePar=mathOp::chiaviAeB(invMap, parMap);

        for(list<string>::const_iterator it = InvePar.begin(); it!=InvePar.end(); ++it) {
            invMap[*it]=(invMap.at(*it) + parMap.at(*it))/2;
        }

        double daDistribuire =0; //somma da distribuire sulle stats di a non presenti in b
        for(list<string>::const_iterator it=ParMenoInv.begin(); it!=ParMenoInv.end(); ++it) {
            daDistribuire+=parMap.at(*it);
        }

        daDistribuire=daDistribuire/InvMenoPar.size();
        for(list<string>::const_iterator it=InvMenoPar.begin(); it!=InvMenoPar.end(); ++it) {
            invMap[*it] =(invMap.at(*it) + daDistribuire)/2;
        }

        for(map<string,double>::const_iterator it=invMap.begin(); it!=invMap.end(); ++it) {
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

        livello = sanitizeLivRar(livello);
        rarita = sanitizeLivRar(rarita);
        mana = sanitizeMana(mana);

        setLivello(livello);
        setRarita(rarita);

        list<string> parametri = getListaStats();
        double sumStats=mana/(livello*rarita);

        if(statistica != "" && std::find(parametri.begin(), parametri.end(), statistica) != parametri.end()) { //RICHIEDE <ALGORITHM>
            if(sumStats < 2) sumStats=2;
             modifyStat(statistica, sumStats/2);
            sumStats=sumStats/2;
            parametri.remove(statistica);
        }

        sumStats=sumStats/parametri.size();
        if(sumStats < 1) sumStats = 1;

        for(list<string>::const_iterator it=parametri.begin(); it!=parametri.end(); ++it)
            modifyStat(*it, sumStats);

        normalizza();
    }

};

#endif // OGGETTO_H
