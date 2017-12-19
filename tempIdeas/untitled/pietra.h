#ifndef PIETRA_H
#define PIETRA_H
#include"oggetto.h"

class Pietra : public Oggetto {
private:
    //parameters to describe the item
    //unsigned short durezza_;

public:
    //default construtor
    Pietra(float livello =0,
           float spirito =0,
           float rarita =0,
           float attacco =0,
           float durezza =0) : Oggetto(livello, spirito, rarita) {
        setStat("attacco", attacco);
        setStat("durezza", durezza);
    }

    //other constructor

    /*pietra(oggetto* object, unsigned short d):
            oggetto(    object->getLivello(),
                        object->getAttacco(),
                        object->getProbabilita()),
            durezza_(d) {}
    */

    //methods
    //copyConstructor
    /*pietra(const pietra& p) {
        this->livello=p.getLivello();
        this->attacco=p.getAttacco();
        this->probabilita=p.getProbabilita();
        this->durezza=p.getDurezza();
    }*/

    virtual unsigned short getDurezza() {
        return getValoreStat("durezza");
    }
};

#endif // PIETRA_H

