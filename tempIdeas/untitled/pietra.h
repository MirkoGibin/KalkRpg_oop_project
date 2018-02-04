#ifndef PIETRA_H
#define PIETRA_H
#include"oggetto.h"

class Osso;
class Amuleto;
class Erba;
class Unguento;

class Pietra : public Oggetto {
private:

    /* parameters inside stats in Oggetto are:
     * spirito
     * attacco
     * durezza
     */
    string durezza_;

public:
    //default construtor
    Pietra(int livello =1,
           int rarita =1,
           double spirito =1,
           double durezza =1);

    //METODI DI GET

    double getDurezza() const;

    //METODI DI SUPPORTO
    Pietra* clone() const;

     void editDurezza(double val);

    //OPERAZIONI CALCOLATRICE

    double ricicla() const;

    void potenzia(double mana, string parametro ="");
};

#endif // PIETRA_H

