#ifndef OGGETTO_H
#define OGGETTO_H
#include<map>
#include<vector>

using std::vector;

using std::map; using std::string;

class Oggetto {
protected:
    //parameters to describe the item
    map<string, float> stats;

    /* parameters inside stats are:
     * livello
     * spirito
     * rarita
     */

public:
    //costruttore di default
    Oggetto(const float livello =0,
            const float spirito =0,
            const float rarita =0) {
        stats.emplace("livello", livello);
        stats.emplace("spirito", spirito);
        stats.emplace("rarita", rarita);
    }

    //distruttore virtuale
    virtual ~Oggetto() {}

    //metodi di servizio

    virtual float calculateMana() const {
        return getSumFromMapStats()*getDataFromKey("livello");
    }

    virtual float getLivello() const {
       return stats.at("livello");
    }
    virtual float getSpirito() const {
        return stats.at("spirito");
    }

    virtual float getRarita() const {
        return stats.at("rarita");
    }

    virtual void insertInMap(string str, const short db) {
        stats.emplace(str, db);
    }

    virtual double getDataFromKey(string str) const {
        return stats.at(str);
    }

    virtual vector<string> getKeyList()  const {
        vector<string> keyList;
        for(map<string, float>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            keyList.push_back(it->first);
        return keyList;
    }

    virtual short int getSumFromMapStats() const {
        short int sum;
        for(map<string, float>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            if(it->first != "livello" && it->first != "rarita" )
                sum+=it->second;
        return sum;
    }

    virtual void combina(Oggetto* object) {
        float manaInv = calculateMana();
        float manaPar =  object->calculateMana();

        int buffer = 0;

        for(map<string, float>::const_iterator itInv = stats.begin(); itInv!=stats.end(); ++itInv) {

            if(itInv->first != "livello" && itInv->first != "rarita" )

                for(map<string, float>::const_iterator itPar = object->stats.begin(); itPar!=object->stats.end(); ++itPar)

                    if(itInv->first == itPar->first)
                        itInv->second = (itInv->second * getDataFromKey("livello") + itPar->second * object->getDataFromKey("livello")) / getDataFromKey("livello");
                    else
                        buffer += itPar->second * object->getDataFromKey("livello");
        }



    }

    //operazioni

    static float parametersDistribution(map<string, float> a, map<string, float> b) {
        int buffer = 0;
        float contatore =0;

        for(map<string, float>::const_iterator it = stats.begin(); it!=stats.end(); ++it)
            if(b->first != "livello" && b->first != "rarita" )
                if(!a.find(it->first)) {
                    contatore++;
                    buffer+=it->second*b.at("livello");
                }
        return buffer/contatore;
    }

    // virtual oggetto* getFather() =0; Se tu metti puro virtuale qui e non le implementi in pietra, pietra rimarrà virtuale pura. Per questo quando vai a fare new pietra ti da errore.

    //virtual oggetto* estrazione() =0;

};

#endif // OGGETTO_H
