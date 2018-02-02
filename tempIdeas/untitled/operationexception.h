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

  OperationException(ecc);

  string getErrore() const;

private:
    ecc tipo_;
};

#endif // ERRORE_H

