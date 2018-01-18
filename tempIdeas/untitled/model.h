#ifndef MODEL_H
#define MODEL_H
#include<QObject>
#include<string>
#include<vector>
#include"oggetto.h"
#include"erba.h"


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
    list<string>* getListaStatFromLastObj() {
        return (memoria.back())->getListaStats();
    }
    unsigned int getNumObjInMemory() const {
        return memoria.size();
    }
    bool setStatByName(QString name, unsigned int value) const {
        if(name=="livello")
            memoria.back()->setLivello(value);
        else if(name=="rarita")
                memoria.back()->setRarita(value);
        else
        memoria.back()->modifyStat(name.toStdString(), value);
        return true;
    }

};

#endif // MODEL_H
