#ifndef OGGETTO_H
#define OGGETTO_H


class oggetto {
private:
    //parameters to describe the item
    unsigned short livello;
    unsigned short attacco;

    //utilities
    double probabilita;

public:
    //default constructor
    oggetto(unsigned short l =0, unsigned short a =0, double p =0) :
        livello(l), attacco(a), probabilita(p) {}

    //methods
    virtual void estrai() =0;

    virtual unsigned short getLivello() {
        return livello;
    }

    virtual unsigned short getAttacco() {
        return attacco;
    }
    virtual unsigned short getProbabilita() {
        return probabilita;
    }

};

#endif // OGGETTO_H
