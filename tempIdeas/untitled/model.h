#ifndef MODEL_H
#define MODEL_H
#include<QObject>
#include<QMap>
#include<QString>
#include<QImage>
#include<QSlider>
#include<QList>
#include<list>
#include"operationexception.h"
#include"viewexception.h"
#include"oggetto.h"
#include"erba.h"
#include"unguento.h"
#include"pietra.h"
#include"cristallo.h"
#include"osso.h"
#include"amuleto.h"

using std::vector; using std::string; using std::list;

class Model : public QObject {
    Q_OBJECT
private:
    unsigned int counter;
    QMap<unsigned int, QImage*> immagini;
    QList<Oggetto*> memoria;

public:
    Model();

//METODI DI GET------------------------------------------------------------
    QMap<QString, int> getLastObj(int =0) const;

    QList<QString> getListaStatsFromLastObj(int =0) const;
    QImage* getImageFromLastObj(int =0) const;

    unsigned int getNumObjInMemory() const;

    void whatsInMemory();

//METODI DI SET--------------------------------------------
    bool setStatByName(QString, unsigned int) const;
    void setImage(QImage*);

//METODI DI MEMORY MANAGEMENT
    void clearMemory();
    void deleteLast();

//OPERATIONS-----------------------------------------------------------
    int ricycleLast();
    void combina();
    void potenzia(int, QString);
    void crea(int, int, int, QString);
    void distribuisci();
    void ripara();
    void duplica();
    void trasforma();
    void estrai();

//CREATE OBJECT IN MEMORY------------------------------------------------
    void createErba();
    void createUnguento();
    void createPietra();
    void createCristallo();
    void createOsso();
    void createAmuleto();

signals:
    void nothingToDelete();
    void isCristallo(bool =false);
    void isUnguento(bool =false);
    void isAmuleto(bool =false);

    void error(QString);
};

#endif // MODEL_H
