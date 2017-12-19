#ifndef CRISTALLO_H
#define CRISTALLO_H
#include "pietra.h"
#include<typeinfo>

class Cristallo : public Pietra {
private:
    //parameters to describe the item
    //unsigned short magia_;

public:
    //default constructor
    Cristallo(float livello =0,
              float spirito =0,
              float rarita =0,
              float attacco =0,
              float durezza =0,
              float magia =0) : Pietra(livello, spirito, rarita, attacco, durezza) {
        setStat("magia", magia);
    }

    //other constructor
    /*cristallo(pietra*, unsigned short magia) :
        pietra(*getFather()), magia_(magia) {}
    */

    //methods
    virtual double getMagia() {
        return getValoreStat("magia");
    }

    /*pietra*getFather() {
        return new pietra(getLivello(),
                          getAttacco(),
                          getProbabilita(),
                          getDurezza());

    }*/

    /*cristallo* estrazione(pietra*p) {
        //unsigned short probToTransform=0;
        //probToTransform=p->getLivello()*p->getDurezza()*p->getProbabilita();
        unsigned short newLevel=getLivello()+1;
        unsigned short newAttac=getAttacco()-2;
        double newProb=getProbabilita();
        unsigned short newDur=getDurezza()+20;
        unsigned short magic=getLivello()*getAttacco()*getProbabilita();
        return new cristallo(newLevel, newAttac, newProb, newDur, magic);
    }*/

};

#endif // CRISTALLO_H

