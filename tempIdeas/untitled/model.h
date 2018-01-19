#ifndef MODEL_H
#define MODEL_H
#include<QObject>
#include<string>
#include<vector>
#include"oggetto.h"
#include"erba.h"
#include"unguento.h"
#include"pietra.h"
#include"cristallo.h"
#include"osso.h"
#include"amuleto.h"


using std::vector; using std::string;
class Model : public QObject {
Q_OBJECT
public:
    //Model();
    list<Oggetto*> memoria;
//------------------------------------------------------------
public slots:
    list<string>* getListaStatFromLastObj() {
        return (memoria.back())->getListaStats();
    }
    unsigned int getNumObjInMemory() const {
        return memoria.size();
    }
    bool setStatByName(QString name, unsigned int value) const {
        if(name=="livello")
            memoria.back()->setLivello(value);
        else if(name=="rarità")
                memoria.back()->setRarita(value);
        else
        memoria.back()->modifyStat(name.toStdString(), value);
        return true;
    }
    int ricycleLast() {
        return memoria.back()->ricicla();
    }
//-----------------------------------------------------------
    void createErba() {
        memoria.push_back(new Erba());
    }
    void createUnguento() {
        memoria.push_back(new Unguento());
    }
    void createPietra() {
        memoria.push_back(new Pietra());
    }
    void createCristallo() {
        memoria.push_back(new Cristallo());
    }
    void createOsso() {
        memoria.push_back(new Osso());
    }
    void createAmuleto() {
        memoria.push_back(new Amuleto());
    }



};

#endif // MODEL_H
