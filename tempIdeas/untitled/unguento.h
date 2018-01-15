#ifndef UNGUENTO_H
#define UNGUENTO_H
#include "oggetto.h"
#include "erba.h"

class Amuleto;
class Cristallo;
class Pietra;
class Osso;

class Unguento : public Erba{
    /* non ci sono stats aggiuntive in Unguento */
public:
    Unguento(int livello =0,
             int rarita =0,
             float spirito =0,
             float puntiVita =0) : Erba(livello, rarita, spirito, puntiVita) {}

    //estraiDa permette di creare un Unguento da una sua superclasse.
    virtual void estraiDa(Oggetto* oggetto) {
        if(dynamic_cast<Erba*>(oggetto)) {

        }
        else {
            //lancia eccezione
        }
    }

    //ottieniDa permette di creare un Unguento a partire da un cristallo TS(cristallo) == TD(cristallo)
    virtual void ottieniDa(Cristallo* cristallo) {
        /*if(typeid(cristallo) == typeid(*cristallo)) {

        }
        else {
            //lancia eccezione
        }*/
    }
    //ottieniDa permette di creare un Unguento a partire da un amuleto TS(amuleto) == TD(amuleto)
    virtual void ottieniDa(Amuleto* amuleto) {
        /*if(typeid(amuleto) == typeid(*amuleto)) {

        }
        else {
            //lancia eccezione
        }*/
    }
};

#endif // UNGUENTO_H
