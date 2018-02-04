#ifndef ERBA_H
#define ERBA_H
#include <typeinfo>
#include <list>
#include "oggetto.h"

class Erba : public Oggetto{
    /* le stats dentro Erba sono:
     * spirito
     * Vitalità
     */
    string vitalita_;
public:
    Erba(int livello =1,
         int rarita =1,
         double spirito =1,
         double vitalita =1);

    //METODI DI GET

    double getVitalita() const;

    //METODI DI SUPPORTO

    Erba* clone() const;

    //OPERAZIONI CALCOLATRICE

    double ricicla() const;

    void potenzia(double mana, string parametro ="");





};

#endif // ERBA_H
