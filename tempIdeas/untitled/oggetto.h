#ifndef OGGETTO_H
#define OGGETTO_H
#include<map>
#include<vector>

using std::vector;

using std::map; using std::string;

class oggetto {
protected:
    //parameters to describe the item
    map<string, unsigned short int> stats;

    /* parameters inside stats are:
     * mana
     * livello
     * spirito
     * rarita
     */

public:
    //costruttore di default
    oggetto(const unsigned short int mana =0,
            const unsigned short int livello =0,
            const unsigned short int spirito =0,
            const unsigned short int rarita =0) {
        stats.emplace("mana", mana);
        stats.emplace("livello", livello);
        stats.emplace("spirito", spirito);
        stats.emplace("rarita", rarita);
    }

    //distruttore virtuale
    virtual ~oggetto() {}

    //metodi di servizio
    virtual unsigned short int getMana() const {
        return stats.at("mana");
    }

    virtual unsigned short int calculateMana() const {
        return getSumFromMapStats()*getDataFromKey("livello);
    }

    virtual unsigned short getLivello() const {
       return stats.at("livello");
    }
    virtual unsigned short getSpirito() const {
        return stats.at("spirito");
    }

    virtual unsigned short getRarita() const {
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
        for(map<string, unsigned short int>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            keyList.push_back(it->first);
        return keyList;
    }

    virtual short int getSumFromMapStats() const {
        short int sum;
        for(map<string, unsigned short int>::const_iterator it= stats.begin(); it!=stats.end(); ++it)
            if(it->first != "livello")
                sum+=it->second;
        return sum;
    }

    //operazioni

    // virtual oggetto* getFather() =0; Se tu metti puro virtuale qui e non le implementi in pietra, pietra rimarrà virtuale pura. Per questo quando vai a fare new pietra ti da errore.

    //virtual oggetto* estrazione() =0;

};

#endif // OGGETTO_H
