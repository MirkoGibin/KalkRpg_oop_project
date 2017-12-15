#ifndef CRISTALLO_H
#define CRISTALLO_H
#include "pietra.h"
#include<typeinfo>

class cristallo : public pietra {
private:
    //parameters to describe the item
    //unsigned short magia_;

public:
    //default constructor
    cristallo(unsigned short livello =0,
              unsigned short attacco =0,
              double probabilita =0,
              unsigned short durezza =0,
              unsigned short magia =0) : pietra(livello, attacco, probabilita, durezza) {
        insertInMap("magia", magia);
    }

    //other constructor
    /*cristallo(pietra*, unsigned short magia) :
        pietra(*getFather()), magia_(magia) {}
    */

    //methods
    virtual double getMagia() {
        return getDataFromKey("magia");
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

