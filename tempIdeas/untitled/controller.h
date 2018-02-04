#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<QObject>
#include"model.h"
#include"viewexception.h"
#include<QGridLayout>
#include"displayandslider.h"
#include"button.h"
#include<QSlider>
#include<QList>
#include<QImage>
#include<QComboBox>

class Controller : public QObject {
Q_OBJECT
private:
    Model* modello;

    //data for setting object
    QMap<QString, QSlider*> tempDataToSet;
    QImage* image;
    QComboBox* combox;
    QString parametro;
    int mana;
    int livello;
    int rarita;

public:
    Controller();

    ~Controller();

//METODI DI GESTIONE-----------------------------
    void flushControllerMemory();
    void clearMemory() const;
    void deleteLastObj();
    void sceltiParametriPotenzia();
    void sceltiParametriCrea();

//METODI DI GET----------------------------------
    int getNumObjInMemory() const;
    QImage* getImage() const;
    QImage* getResultImage(int=0) const;
    QList<QString> getResultParametri(int =0) const;
    QList<QString> getParametri() const;

//METODI DI SET----------------------------------
    void setImage(QImage*);
    void setSelectedObject(QGridLayout*);
    void setPotenzia(QGridLayout*);
    void setCrea(QGridLayout*);
    void setStatsOnObj();

//OPERAZIONI-------------------------------------
    void combina() const;
    int ricicla() const;
    void potenzia() const;
    void crea() const;
    void distribuisci() const;
    void ripara() const;
    void duplica() const;
    void trasforma() const;
    void estrai() const;

//OGGETTI----------------------------------------------------------------------------
    void newErba();
    void newUnguento();
    void newPietra();
    void newCristallo();
    void newOsso();
    void newAmuleto();

signals:
    void nothingToDelete();

    void isCristallo(bool =false);
    void isUnguento(bool =false);
    void isAmuleto(bool =false);
};

#endif // CONTROLLER_H
