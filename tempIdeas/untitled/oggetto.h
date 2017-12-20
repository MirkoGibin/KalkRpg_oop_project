#ifndef OGGETTO_H
#define OGGETTO_H
#include<mathOp.h>
#include<map>
#include<list>
#include<iostream>
#include<algorithm>

using std::list;
using std::map; using std::string; using std::cout; using std::endl;

class Oggetto {
private:

    //parameters to describe the item
    int livello_;
    int rarita_;

    map<string, float> stats;

    /* parameters inside stats in Oggetto are:
     * spirito
     */

public:
    //costruttore di default
    Oggetto(int livello =0,
            int rarita =0,
            float spirito =0) : livello_(livello), rarita_(rarita) {
        stats.emplace("spirito", spirito);
    }

    //distruttore virtuale
    virtual ~Oggetto() {}


//---------METODI DI SET
    virtual void setLivello(int livello) {
        livello_=livello;
    }
    virtual void setRarita(int rarita) {
        rarita_=rarita;
    }
    virtual void insertStat(string str, float db) {
        stats.emplace(str, db);
    }

    virtual bool modifyStat(string str, float db) { //GESTIONE DEGLI ERRORI
        bool trovata=true;
        if(stats.count(str)) {
            stats[str] = db;
            return trovata;
        }
        else
            return !trovata;
    }

//------------METODI DI GET
    virtual float getLivello() const {
       return livello_;
    }
    virtual float getRarita() const {
        return rarita_;
    }
    virtual float getValoreStat(string str) const {
        return stats.at(str);
    }

    virtual float getSpirito() const {
        return getValoreStat("spirito");
    }

    virtual list<string>* getListaStats()  const {
        list<string>* keyList = new list<string>();
        for(map<string, float>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            keyList->push_back(it->first);
        return keyList;
    }

    virtual float getSommaStats() const {
        float sum = 0;
        for(map<string, float>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            sum+=it->second;
        return sum;
    }

    virtual float calcolaMana() const {
        return getSommaStats()*getLivello();
    }



//------------OPERAZIONI
    virtual void combina(Oggetto* object) {
        map<string, float> percentInvMap = stats; //copiata la mappa dell'oggetto di invocazione
        map<string, float> percentParMap = object->stats; //copiata la mappa dell'oggetto di invocazione


        float toMultiplyInv=getLivello()/calcolaMana();
        float toMultiplyPar=object->getLivello()/object->calcolaMana();

        mathOp::doMultiplyOnMap(percentInvMap, toMultiplyInv);
        mathOp::doMultiplyOnMap(percentParMap, toMultiplyPar);

        list<string>*InvMenoPar=mathOp::chiaviAmenoB(percentInvMap, percentParMap);
        list<string>*ParMenoInv=mathOp::chiaviAmenoB(percentParMap, percentInvMap);
        list<string>*InvePar=mathOp::chiaviAeB(percentInvMap, percentParMap);

        for(list<string>::const_iterator it = InvePar->begin(); it!=InvePar->end(); ++it) {
            percentInvMap[*it]=(percentInvMap.at(*it) + percentParMap.at(*it))/2;
        }

        float daDistribuire; //somma da distribuire sulle stats di a non presenti in b
        for(list<string>::const_iterator it=ParMenoInv->begin(); it!=ParMenoInv->end(); ++it) {
            daDistribuire+=percentParMap.at(*it);
        }

        daDistribuire=daDistribuire/InvMenoPar->size();
        for(list<string>::const_iterator it=InvMenoPar->begin(); it!=InvMenoPar->end(); ++it) {
            percentInvMap[*it] =(percentInvMap.at(*it) + daDistribuire)/2;
        }

        for(map<string,float>::const_iterator it=percentInvMap.begin(); it!=percentInvMap.end(); ++it) {
            stats[it->first] = stats.at(it->first)*getLivello() + it->second*object->calcolaMana();
        }
        //ora bisogna normalizzare stats a seconda del livello.
        normalizza();
        delete InvePar;
        delete InvMenoPar;
        delete ParMenoInv;

        //elimino l'oggetto passato come parametro
        delete object;
    }

    virtual void normalizza() {
        if(getLivello()*150 <= calcolaMana()) {
            float percentualeRiduzione=getLivello()*150/calcolaMana();
            mathOp::doMultiplyOnMap(stats, percentualeRiduzione);

            /*
            for(map<string,float>::const_iterator it=stats.begin(); it!=stats.end(); ++it)
                stats[it->first]=it->second*percentualeRiduzione;
            */

        }
    }

    //operazioni

    virtual float ricicla() {
        return getSommaStats()*getLivello()*getRarita();
    }

    virtual void crea(float mana, int livello, int rarita, string statistica) { //PRE = statistica è vuoto o è un valore valido

        this->setLivello(livello);
        this->setRarita(rarita);

        list<string>* parametri = getListaStats(); //DA DEALLOCARE
        float sumStats=mana/(livello*rarita);

        if(std::find(parametri->begin(), parametri->end(), statistica) != parametri->end()) { //RICHIEDE <ALGORITHM>
            modifyStat(statistica, sumStats/2);
            sumStats=sumStats/2;
            parametri->remove(statistica);
        }

        if(parametri->size()==0) { //oggetto con un solo parametro in stats (spirito)
            modifyStat(statistica, getValoreStat(statistica)+sumStats);

        } else {
            sumStats=sumStats/parametri->size();

            for(list<string>::const_iterator it=parametri->begin(); it!=parametri->end(); ++it)
                modifyStat(*it, sumStats);
        }
        delete parametri;
    }



};

#endif // OGGETTO_H
