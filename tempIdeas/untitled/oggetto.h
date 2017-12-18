#ifndef OGGETTO_H
#define OGGETTO_H
#include<map>
#include<vector>
#include<iostream>

using std::vector;

using std::map; using std::string; using std::cout;

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
    Oggetto(const float livello =0,
            const float spirito =0,
            const float rarita =0) : livello_(livello), rarita_(rarita) {
        stats.emplace("spirito", spirito);
    }

    /*
    //distruttore virtuale
    virtual ~Oggetto() {}
    */


    //metodi di servizio

    virtual float calculateMana() const {
        return getSumFromMapStats()*getLivello();
    }

    virtual float getLivello() const {
       return livello_;
    }
    virtual float getSpirito() const {
        return stats.at("spirito");
    }

    virtual float getRarita() const {
        return rarita_;
    }

    virtual void insertInMap(string str, const float db) {
        stats.emplace(str, db);
    }

    virtual float getDataFromKey(string str) const {
        return stats.at(str);
    }

    virtual vector<string> getKeyList()  const {
        vector<string> keyList;
        for(map<string, float>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            keyList.push_back(it->first);
        return keyList;
    }

    virtual float getSumFromMapStats() const {
        float sum = 0;
        for(map<string, float>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            sum+=it->second;
        return sum;
    }

    virtual void combina(Oggetto* object) {
        float manaInv = calculateMana();
        float manaPar =  object->calculateMana();
        map<string, float> percentInvMap = stats; //copiata la mappa dell'oggetto di invocazione
        map<string, float> percentParMap = object->stats; //copiata la mappa dell'oggetto di invocazione

        for(map<string, float>::const_iterator it= stats.begin(); it!=stats.end(); ++it) {
            percentInvMap[it->first] = it->second * getLivello() / manaInv; // percentuale di partecipazione della statistica sul mana
        }
        // POST = updateObj contiene le percentuali di partecipazione delle varie statistiche sul mana totale

        for(map<string, float>::const_iterator it= object->stats.begin(); it!=object->stats.end(); ++it) {
            percentParMap[it->first] = it->second * object->getLivello() / manaPar; // percentuale di partecipazione della statistica sul mana
        }

        vector<string> aMenob, bMenoa, aeb;


        for(map<string, float>::const_iterator it=percentInvMap.begin(); it!=percentInvMap.end(); ++it) {
            if(!percentParMap.count(it->first))
                aMenob.push_back(it->first);
            else
                aeb.push_back(it->first);
        }
        for(map<string, float>::const_iterator it=percentParMap.begin(); it!=percentParMap.end(); ++it) {
            if(!percentInvMap.count(it->first))
                bMenoa.push_back(it->first);
        }

        for(vector<string>::const_iterator it = aeb.begin(); it!=aeb.end(); ++it) {
            percentInvMap[*it]=(percentInvMap.at(*it) + percentParMap.at(*it))/2;
        }

        float daDistribuire; //somma da distribuire sulle stats di a non presenti in b
        for(vector<string>::const_iterator it=bMenoa.begin(); it!=bMenoa.end(); ++it) {
            daDistribuire+=percentParMap.at(*it);
        }
        daDistribuire=daDistribuire/aMenob.size();

        for(vector<string>::const_iterator it=aMenob.begin(); it!=aMenob.end(); ++it) {
            cout << "Cazzo@";
            percentInvMap[*it] =(percentInvMap.at(*it) + daDistribuire)/2;
        }

        for(map<string,float>::const_iterator it=percentInvMap.begin(); it!=percentInvMap.end(); ++it) {
            stats[it->first] = stats.at(it->first)*getLivello() + it->second*manaPar;
        }

        //ora bisogna normalizzare stats a seconda del livello.
        normalizeStats();

    }

    virtual void normalizeStats() {
        if(getLivello()*150 <= calculateMana()) {
            float percentualeRiduzione=getLivello()*150/calculateMana();

            for(map<string,float>::const_iterator it=stats.begin(); it!=stats.end(); ++it) {
                stats[it->first]=it->second*percentualeRiduzione;
            }
        }
    }

    //operazioni

    // virtual oggetto* getFather() =0; Se tu metti puro virtuale qui e non le implementi in pietra, pietra rimarrà virtuale pura. Per questo quando vai a fare new pietra ti da errore.

    //virtual oggetto* estrazione() =0;

};

#endif // OGGETTO_H
