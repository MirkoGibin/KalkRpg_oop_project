#ifndef CRISTALLO_H
#define CRISTALLO_H
#include "pietra.h"
#include<typeinfo>

class cristallo : public pietra {
private:
    //parameters to describe the item
    unsigned short magia;

public:
    //default constructor
    cristallo(unsigned short l =0, unsigned short a =0, double p=0,
              unsigned short d =0,
              unsigned short m =0) :
        pietra(l, a, p, d), magia(m) {}

    //other constructor
    cristallo(pietra*, unsigned short m) :
        pietra(*getFather()), magia(m) {}

    //methods
    virtual unsigned short getMagia() {
        return magia;
    }
    pietra*getFather() {
        return new pietra(getLivello(),
                          getAttacco(),
                          getProbabilita(),
                          getDurezza());

    }
    cristallo* estrazione(pietra*p) {
        //unsigned short probToTransform=0;
        //probToTransform=p->getLivello()*p->getDurezza()*p->getProbabilita();
        unsigned short newLevel=getLivello()+1;
        unsigned short newAttac=getAttacco()-2;
        double newProb=getProbabilita();
        unsigned short newDur=getDurezza()+20;
        unsigned short magic=getLivello()*getAttacco()*getProbabilita();
        return new cristallo(newLevel, newAttac, newProb, newDur, magic);
    }

};

#endif // CRISTALLO_H
