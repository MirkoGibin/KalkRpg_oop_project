#ifndef OGGETTO_H
#define OGGETTO_H
#include<map>
#include<utility>

using std::map; using std::string;

class oggetto {
private:
    //parameters to describe the item
    map<string, double> parametri_;


    /*
    unsigned short livello_;
    unsigned short attacco_;

    //utilities
    double probabilita_;
    */


    //default constructor
public:
    //costruttore di default
    oggetto(const short livello =0,
            const short attacco =0,
            const double probabilita =0) {
        parametri_.emplace(std::make_pair("livello", livello));
        parametri_.emplace(std::make_pair("attacco", attacco));
        parametri_.emplace(std::make_pair("probabilita", probabilita));
    }
        // map<string, double>::value_type livello_("livello", livello);
        // map<string, double>::value_type attacco_("attacco", attacco);
        // map<string, double>::value_type probabilita_("probabilita", probabilita);
        // parametri_.insert(livello_);
        // parametri_.insert(attacco_);
        // parametri_.insert(probabilita_);

    virtual ~oggetto() {}

    //methods
    virtual unsigned short getLivello() {
        return parametri_["livello"];
    }

    virtual unsigned short getAttacco() {
        return parametri_["attacco"];
    }
    virtual double getProbabilita() {
        return parametri_["probabilita"];
    }

    virtual void insertInPrivateMap(string str, double db) {
        parametri_.emplace(std::make_pair(str, db));
    }

    virtual double getDataFromKey(string str) {
        return parametri_[str];
    }


    // virtual oggetto* getFather() =0; Se tu metti puro virtuale qui e non le implementi in pietra, pietra rimarrà virtuale pura. Per questo quando vai a fare new pietra ti da errore.

    //virtual oggetto* estrazione() =0;

};

#endif // OGGETTO_H
