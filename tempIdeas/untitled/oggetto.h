#ifndef OGGETTO_H
#define OGGETTO_H
#include<map>
#include<vector>

using std::vector;

using std::map; using std::string;

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

    //distruttore virtuale
    virtual ~Oggetto() {}

    //metodi di servizio

    virtual float calculateMana() const {
        return getSumFromMapStats()*getDataFromKey("livello");
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

    /*virtual void combina(Oggetto* object) {
        float manaInv = calculateMana();
        float manaPar =  object->calculateMana();

        int buffer = 0;

        for(map<string, float>::const_iterator itInv = stats.begin(); itInv!=stats.end(); ++itInv) {

            for(map<string, float>::const_iterator itPar = object->stats.begin(); itPar!=object->stats.end(); ++itPar)

                    if(itInv->first == itPar->first)
                        itInv->second = (itInv->second * getDataFromKey("livello") + itPar->second * object->getDataFromKey("livello")) / getDataFromKey("livello");
                    else
                        buffer += itPar->second * object->getDataFromKey("livello");
        }



    }*/

    //operazioni

    /* parametersDistribution prende due mappe a e b.
     * Le entry di b che non sono presenti in a vengono sommate in un buffer.
     * Il buffer viene poi restituito diviso per il numero
     * di campi che hanno contribuito
     */
    static float parametersDistribution(map<string, float> a, map<string, float> b) {
        float buffer = 0;
        int contatore =0;

        for(map<string, float>::const_iterator it = b.begin(); it!=b.end(); ++it)
            if(!(a.count(it->first))) {
                contatore++;
                buffer += it->second*b.at("livello");
        }
        return buffer / contatore;
    }

    // virtual oggetto* getFather() =0; Se tu metti puro virtuale qui e non le implementi in pietra, pietra rimarrà virtuale pura. Per questo quando vai a fare new pietra ti da errore.

    //virtual oggetto* estrazione() =0;

};

#endif // OGGETTO_H
