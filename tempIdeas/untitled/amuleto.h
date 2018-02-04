#ifndef AMULETO_H
#define AMULETO_H

#include"osso.h"

class Erba;
class Unguento;
class Pietra;
class Cristallo;

class Amuleto : public Osso {
private:
    /* parameters inside stats in Amuleto:
     * spirito
     * attacco
     * difesa
     * fortuna
     */
    string fortuna_;

public:
    Amuleto(int livello =1,
            int rarita =1,
            double spirito =1,
            double attacco =1,
            double difesa =1,
            double fortuna =1);

    //METODI DI GET
    double getFortuna() const;

    //METODI DI SUPPORTO
    Amuleto* clone() const;

    //OPERAZIONI CALCOLATRICE

    double ricicla() const;

    void potenzia(double mana, string parametro ="");

    void estraiDa(Oggetto* oggetto);

    /* Specifico di amuleto. Crea una copia perfetta o con statistiche dimezzate di obj, in base alla rarità ( >= 4 oppure < 5).
     * La fortuna deve però essere almeno pari alla media del valore delle statistiche,
     * altrimenti la fortuna scenderà a 1 e la copia avrà tutti i parametri a 1*/
    Oggetto* duplica(const Oggetto * obj);

};

#endif // AMULETO_H
