#ifndef CRISTALLO_H
#define CRISTALLO_H
#include "pietra.h"

class cristallo : public pietra {
private:
    //parameters to describe the item
    unsigned int magia;

public:
    //default constructor
    cristallo(unsigned short l =0, unsigned short a =0, double p=0,
              unsigned short d =0,
              unsigned short m =0) :
        pietra(l, a, p, d), magia(m) {}
    //methods
    virtual unsigned short getMagia() {
        return magia;
    }

};

#endif // CRISTALLO_H
