#ifndef PIETRA_H
#define PIETRA_H
#include"oggetto.h"
//#include"cristallo.h"

class pietra : public oggetto {
private:
    //parameters to describe the item
    unsigned int durezza;

public:
    //default construtor
    pietra(unsigned short l =0, unsigned short a =0, double p =0,
           unsigned short d =0) :
        oggetto(l, a, p), durezza(d) {}

    //methods

    virtual unsigned short getDurezza() {
        return durezza;
    }

    /*void estrai() {
        (this)=new cristallo(getLivello(),
                              getAttacco(),
                              getProbabilita(),
                              getDurezza(),
                              getDurezza()*getProbabilita());
    }*/

};

#endif // PIETRA_H
