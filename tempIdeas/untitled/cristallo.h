#ifndef CRISTALLO_H
#define CRISTALLO_H
#include "pietra.h"
#include<typeinfo>

class Erba;
class Unguento;
class Osso;
class Amuleto;

class Cristallo : public Pietra {
private:

    /* parameters inside stats in Oggetto are:
     * spirito
     * attacco
     * durezza
     * magia
     */
    string magia_;

public:
    //default constructor
    Cristallo(const int livello =1,
              const int rarita =1,
              const double spirito =1,
              const double durezza =1,
              const double magia =1);

    //METODI DI GET
    virtual double getMagia() const;

    //METODI DI SUPPORTO
    Cristallo* clone() const;

    //OPERAZIONI CALCOLATRICE

    void potenzia(double mana, string parametro ="");

    double ricicla() const;

    void estraiDa(Oggetto* oggetto);
    /*Specifica di cristallo. Se la durezza è almeno la metà della magia, dimezza la propria magia per potenziare obj.*/

    void distribuisci(Oggetto* obj);



};

#endif // CRISTALLO_H

