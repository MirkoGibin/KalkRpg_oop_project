#ifndef OSSO_H
#define OSSO_H

#include<typeinfo>

#include"oggetto.h"

class Erba;
class Unguento;
class Pietra;
class Cristallo;

class Osso : public Oggetto {
private:

    /* parameters inside stats in Osso are:
     * spirito
     * attacco
     * difesa
     */
    string attacco_;
    string difesa_;


public:
    Osso(int livello =1,
         int rarita =1,
         double spirito =1,
         double attacco =1,
         double difesa =1);

    double getAttacco() const;

    double getDifesa() const;

    Osso* clone() const;

//ricicla fa la moltiplicazione della sommaStats in cui attacco e difesa sono raddoppiati, moltiplicato per livello e rarita
    double ricicla() const;

    void potenzia(double mana, string parametro ="");
};

#endif // OSSO_H
