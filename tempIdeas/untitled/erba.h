#ifndef ERBA_H
#define ERBA_H
#include "oggetto.h"
#include <typeinfo>

class Osso;
class Pietra;
class Amuleto;
class Cristallo;

class Erba : public Oggetto{
    /* le stats dentro Erba sono:
     * spirito
     * puntiVita
     */
public:
    Erba(int livello =0,
         int rarita =0,
         float spirito =0,
         float puntiVita =0) : Oggetto(livello, rarita, spirito) {
            insertStat("puntiVita", puntiVita);
    }

    float getPuntiVita() const {
        return getValoreStat("puntiVita");
    }

    // ricicla ritorna il mana che si ottiene dalla distruzione di un'erba. Si sommano le statistiche,
    // si toglie metà dello spirito, si contano ulteriormente i punti vita in quanto stat caratterizzante,
    // si somma il quadrato della rarità in quanto conta molto nel mana restituito.
    virtual float ricicla() {
        float mana = getSommaStats() - getSpirito()/2 + 2 * getPuntiVita() + getRarita() * getRarita();
        delete this;
        return mana;
    }

    // il metodo ottiene un'Erba a partire da una pietra. Viene effettuato un controllo TS(pietra) == TD(pietra) per avere la
    // certezza di effettuare l'operazione su una pietra e non su un suo sottotipo.
    virtual void ottieniDa(Pietra* pietra) {
        /*if(typeid(pietra) == typeid(*pietra)) {

        }
        else {
            //lancia eccezione
        }*/
    }

    // il metodo ottiene un'Erba a partire da un osso. Viene effettuato un controllo TS(osso) == TD(osso) per avere la
    // certezza di effettuare l'operazione su un osso e non su un suo sottotipo.
    virtual void ottieniDa(Osso* osso) {
        /*if(typeid(pietra) == typeid(*pietra)) {

        }
        else {
            //lancia eccezione
        }*/

    }


};

#endif // ERBA_H
