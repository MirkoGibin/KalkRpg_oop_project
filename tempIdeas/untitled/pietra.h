#ifndef PIETRA_H
#define PIETRA_H
#include"oggetto.h"

class pietra : public oggetto {
private:
    //parameters to describe the item
    unsigned short durezza;

public:
    //default construtor
    pietra(unsigned short l =0,
           unsigned short a =0,
           double p =0,
           unsigned short d =0) :
        oggetto(l, a, p), durezza(d) {}

    //other constructor
    pietra(oggetto* o, unsigned short d):
            oggetto(    o->getLivello(),
                        o->getAttacco(),
                        o->getProbabilita()),
            durezza(d) {}

    //methods
    //copyConstructor
    /*pietra(const pietra& p) {
        this->livello=p.getLivello();
        this->attacco=p.getAttacco();
        this->probabilita=p.getProbabilita();
        this->durezza=p.getDurezza();
    }*/

    virtual unsigned short getDurezza() {
        return durezza;
    }
};

#endif // PIETRA_H
