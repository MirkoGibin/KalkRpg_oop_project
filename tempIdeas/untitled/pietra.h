#ifndef PIETRA_H
#define PIETRA_H
#include"oggetto.h"

class pietra : public oggetto {
private:
    //parameters to describe the item
    //unsigned short durezza_;

public:
    //default construtor
    pietra(unsigned short livello =0,
           unsigned short attacco =0,
           double probabilita =0,
           unsigned short durezza =0) : oggetto(livello, attacco, probabilita) {
        insertInMap("durezza", durezza);

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
        return getDataFromKey("durezza");
    }
};

#endif // PIETRA_H

