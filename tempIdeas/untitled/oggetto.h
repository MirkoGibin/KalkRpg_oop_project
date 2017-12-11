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
    oggetto(unsigned short l =0,
            unsigned short a =0,
            double p =0) :
                livello(l),
                attacco(a),
                probabilita(p) {}

    //methods
    virtual oggetto*estrazione() =0;

    virtual unsigned short getLivello() {
        return livello;
    }

    virtual unsigned short getAttacco() {
        return attacco;
    }
    virtual double getProbabilita() {
        return probabilita;
    }
    virtual oggetto*getFather() =0;

};

#endif // OGGETTO_H
