#ifndef OGGETTO_H
#define OGGETTO_H
#include<map>
#include<string>
using std::string;
using std::map;

class oggetto {
private:
    //statistiche di un oggetto: mana, livello, spirito, rarita
    map<string, short int> stats;

public:
    //costruttore

    //metodi virtuali getter

    virtual short int getMana();
    virtual short int getLivello();
    virtual short int getSpirito();
    virtual short int getRarita();
    virtual short int getLivello();

    //metodi virtuali puri

    virtual float combina(Oggetto& object) {
     /*
        sommo il contenuto degli elementi di this.stats => SUM;
        per ogni this.stats[i] calcolo il complementare della percentuale di partecipazione a SUM => perc[i]
        sommo tutte le perc[i] => SUM_PERC
        perc[i] / SUM_PERC => distr[i]
        sommo il contenuto di object.stats NEW_SUM;
        this.stats[i] += NEW_SUM * distr[i]



        distruggo object;

     */
    }
    virtual float estrai(Oggetto&);
    virtual float rimuoviMalus();
    virtual float potenzia();
    virtual float costruisci();
    virtual float ricicla();
    virtual float trasforma();

};

#endif // OGGETTO_H
