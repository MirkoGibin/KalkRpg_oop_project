#ifndef UNGUENTO_H
#define UNGUENTO_H
#include "oggetto.h"
#include "erba.h"

class Amuleto;
class Cristallo;
class Pietra;
class Osso;

class Unguento : public Erba{
    string energia_;
public:
    Unguento(int livello =1,
             int rarita =1,
             double spirito =1,
             double vitalita =1,
             double energia =1);
    //METODI DI GET
    double getEnergia() const;

    //METODI DI SUPPORTO
    Unguento*clone() const;

    //OPERAZIONI CALCOLATRICE
    void potenzia(double mana, string parametro ="");

    double ricicla() const;

    void estraiDa(Oggetto* oggetto);

    /*Specifico di unguento.
     * Viene calcolata la differenza tra i parametri di obj con il valore più alto e più basso tramite la funzione findMinMaxStat.
     *  Se l’energia dell’unguento è sufficiente a coprire questo gap, in caso di rarità di unguento <= 7,
     * la statistica più passa di obj viene portata al valore della statistica più alta;
     * se la rarità è >7 tutte le statistiche vengono portate al valore più alto.
     * */
    void ripara(Oggetto* obj);



};

#endif // UNGUENTO_H
