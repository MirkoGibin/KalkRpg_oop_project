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
             float vitalita =0,
             float energia =0) : Erba(livello, rarita, spirito, vitalita) {
        insertStat("Energia", energia);
    }

    void potenzia(int mana, string parametro ="") {

        int divisore = 10;
        int incremento = mana / getLivello();

        incrementStat("Energia", incremento * getRarita() / divisore); //Energia riceve un bonus sicuro oltre alla normale distribuzione

        if(parametro == "") {
            list<string>* statsList = getListaStats();
            incremento = incremento / statsList->size();
            for(auto i = statsList->begin(); i != statsList->end(); i++)
                incrementStat(*i, incremento);
            delete statsList;
        }
        else {
            incrementStat(parametro, incremento);
        }

    }

    //estraiDa permette di creare un Unguento da una sua superclasse.
    virtual void estraiDa(Oggetto* oggetto) {
        if(dynamic_cast<Erba*>(oggetto)) {
            setLivello(oggetto->getLivello());
            setRarita(oggetto->getRarita());
            list<string> *s = oggetto->getListaStats();
            int numeroStat = s->size();

            for(auto i = s->begin(); i != s->end(); ++i)
                if(*i == "Energia") incrementStat(*i, oggetto->getSommaStats() / numeroStat);
                else incrementStat(*i, getValoreStat(*i) / numeroStat * (numeroStat - 1));

            delete s;
        }
        else {
            //eccezione
        }
    }

    //ottieniDa permette di creare un Unguento a partire da un cristallo TS(cristallo) == TD(cristallo)
    /*virtual void ottieniDa(Cristallo* cristallo) {
        if(typeid(cristallo) == typeid(*cristallo)) {

        }
        else {
            //lancia eccezione
        }
    }
    //ottieniDa permette di creare un Unguento a partire da un amuleto TS(amuleto) == TD(amuleto)
    virtual void ottieniDa(Amuleto* amuleto) {
        if(typeid(amuleto) == typeid(*amuleto)) {

        }
        else {
            //lancia eccezione
        }
    }*/
};

#endif // UNGUENTO_H
