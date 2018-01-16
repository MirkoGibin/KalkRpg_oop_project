#ifndef MODEL_H
#define MODEL_H
#include<QObject>
#include<string>
#include<vector>
#include"oggetto.h"
#include"pietra.h"
#include"cristallo.h"
#include"osso.h"
#include"erba.h"
#include"unguento.h"

using std::vector; using std::string;
class Model : public QObject {
Q_OBJECT
public:
    Modello();
    list<Oggetto*> memoria;

public slots:
    void createErba() {
        memoria.push_back(new Erba());
    }
    list<string>* retrieveListaStats() {
        return (memoria.back())->getListaStats();
    }



signals:
    void statNeeded(int, string);



};

#endif // MODEL_H
