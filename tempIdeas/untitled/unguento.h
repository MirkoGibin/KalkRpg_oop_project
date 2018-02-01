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
    Unguento(int livello =0,
             int rarita =0,
             float spirito =0,
             float vitalita =0,
             float energia =0) : Erba(livello, rarita, spirito, vitalita), energia_("Energia") {
        insertStat(energia_, energia);
    }

   void potenzia(int mana, string parametro ="") {
       int divisore;

       if(getRarita() > 6)
           divisore = 9;
       else
           divisore = 12;

       incrementStat(energia_, mana * getLivello() * getRarita() / divisore); //Energia riceve un bonus sicuro oltre alla normale distribuzione
       Erba::potenzia(mana, parametro);
   }

   //estraiDa permette di creare un Unguento da una sua superclasse.
   virtual void estraiDa(Oggetto* oggetto) {
       if(dynamic_cast<Erba*>(oggetto)) {
           setLivello(oggetto->getLivello());
           setRarita(oggetto->getRarita());
           list<string> s = oggetto->getListaStats();
           int numeroStat = s.size();

           for(auto i = s.begin(); i != s.end(); ++i)
               if(*i == energia_) incrementStat(*i, oggetto->getSommaStats() / numeroStat);
               else incrementStat(*i, getValoreStat(*i) / numeroStat * (numeroStat - 1));
       }
       else {
           //eccezione
       }
   }

   float ricicla() const {
       return Erba::ricicla() + getValoreStat(energia_) * getRarita();
   }

   void ripara(Oggetto* obj) {

       std::pair<string, string> minmax = findMinMaxStat();

       float maxValue = obj->getValoreStat(minmax.second);
       float diff = maxValue - obj->getValoreStat(minmax.first);

       if(getValoreStat(energia_) < diff) {} //throw

       incrementStat(energia_, -diff);

       if(getRarita() > 7) {
           list<string> parametri = obj->getListaStats();
           for(auto it = parametri.begin(); it != parametri.end(); it++) {
               obj->modifyStat(*it, maxValue);
           }
       }
       else {
           obj->modifyStat(minmax.first, maxValue);
       }
   }



};

#endif // UNGUENTO_H
