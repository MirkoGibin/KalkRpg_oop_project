#ifndef OGGETTO_H
#define OGGETTO_H
#include<map>
#include<list>
#include<algorithm>
#include<mathOp.h>
#include<typeinfo>
#include<climits>
#include<tuple>

#include"operationexception.h"

using std::list;
using std::map;
using std::string;

class Oggetto {
private:

    //parameters to describe the item
    int livello_;
    int rarita_;
    string spirito_;

    map<string, double> stats;

    /* parameters inside stats in Oggetto are:
     * spirito
     */


public:
    //costruttore di default
    Oggetto(int livello =1,
            int rarita =1,
            double spirito =1);

    //distruttore virtuale
    virtual ~Oggetto();



//---------METODI DI SET
    void setLivello(int livello);
    void setRarita(int rarita);
    void insertStat(string str, double db);

    void incrementStat(string stat, double value);

    bool modifyStat(string str, double db);

//------------METODI DI GET
    //ritorna una coppia di stringhe. La prima indica la statistica con il minor valore, la seconda la statistica con il maggior valore.
    std::pair<string,string> findMinMaxStat() const;

    int getLivello() const;

    int getRarita() const;

    double getValoreStat(string str) const;

    double getSpirito() const;

    double getSommaStats() const;

    list<string> getListaStats()  const;

    double calcolaMana() const;



//------------OPERAZIONI DI CONTROLLO INPUT
    void normalizza();

    void sanitizeInput();

    static double sanitizeMana(double mana);

    static int sanitizeLivRar(int l);

    //OPERAZIONI CALCOLATRICE

    /*Il metodo fa side effect sull’oggetto di invocazione.
     * Per entrambi gli oggetti, calcola una percentuale di distribuzione basata sul livello e sul mana.
     *  All’oggetto di invocazione vengono aumentate le statistiche in base a queste percentuali, distinguendo
     * il caso di statistiche presenti in entrambi e statistiche peculiari di ogni oggetto.*/
    void combina(const Oggetto* object);

    /*Il metodo fa side effect sull’oggetto di invocazione.
    Viene controllato se il suo numero di parametri è maggiore di obj. In tal caso, viene lanciata un’eccezione.
    Altrimenti vi sono sufficienti statistiche per inizializzare tutto. A parametri uguali viene destinato metà dell’originale valore.
    Il rimanente, derivante da eventuali parametri caratteristici, viene usato per incrementare le statistiche rimanenti dell’oggetto di invocazione;
    in questo caso la rarità funge da moltiplicatore.*/
    void trasformaDa(const Oggetto *obj);

    /*Controlla l’input e imposta i parametri di livello e rarita.
    Se è stato indicato un parametro, metà del mana verrà riservato ad esso.
    Altrimenti viene equamente diviso tra le statistiche.*/
    void crea(double mana, int livello, int rarita, string statistica = "");

    //OPERAZIONI VIRTUALI PURE
    virtual Oggetto* clone() const =0;
    virtual double ricicla() const = 0;
    virtual void potenzia(double mana, string parametro ="") = 0;
};

#endif // OGGETTO_H
