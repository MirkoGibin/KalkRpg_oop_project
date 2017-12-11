#ifndef OGGETTO_H
#define OGGETTO_H


class oggetto {
private:
    //parameters to describe the item
    unsigned short livello_;
    unsigned short attacco_;

    //utilities
    double probabilita_;

public:
    //default constructor
    oggetto(unsigned short livello =0,
            unsigned short attacco =0,
            double probabilita =0) :
                livello_(livello),
                attacco_(attacco),
                probabilita_(probabilita) {}
    virtual ~oggetto() {}

    //methods
    virtual unsigned short getLivello() {
        return livello_;
    }

    virtual unsigned short getAttacco() {
        return attacco_;
    }
    virtual double getProbabilita() {
        return probabilita_;
    }
   // virtual oggetto* getFather() =0; Se tu metti puro virtuale qui e non le implementi in pietra, pietra rimarrà virtuale pura. Per questo quando vai a fare new pietra ti da errore.

    //virtual oggetto* estrazione() =0;

};

#endif // OGGETTO_H
