#ifndef OPERATIONEXCEPTION_H
#define OPERATIONEXCEPTION_H
#include<string>
using std::string;

class OperationException {

public:

  enum ecc {
      trasformazione = 0,
      estrazione = 1
  };

  OperationException(ecc tipo ) : tipo_(tipo) {}

  string getErrore() const {
      string errore = "";
      switch(tipo_) {

      case 0 :
          errore = "Impossibile trasformare dall'oggetto indicato: il numero di statistiche dell'oggetto da trasformare non può essere minore\
                    del numero di statistiche dell'oggetto che si vuole ottenere.";
          break;

      case 1 :
          errore = "Impossibile estrarre dall'oggetto indicato. Le estrazioni possibili sono: \n\
                    \t erba => unguento;\
                    \t pietra => cristallo;\
                    \t osso => amuleto";                     ;
          break;
      }

      return errore;
  }

private:
    ecc tipo_;
};

#endif // ERRORE_H

