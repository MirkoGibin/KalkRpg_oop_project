#ifndef ERRORE_H
#define ERRORE_H
#include<string>
using std::string;

class Errore {
private:
    string tipo_;
public:
    Errore(string tipo = "") : tipo_(tipo) {}
    string getTipo() const {
        return tipo_;
    }
};

#endif // ERRORE_H
