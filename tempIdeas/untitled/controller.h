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
    Controller() : modello(new Model()), image(0),
        combox(0), parametro(""), mana(1), livello(1), rarita(1)  {
        connect(modello, SIGNAL(nothingToDelete()), this, SIGNAL(nothingToDelete()));
        connect(modello, SIGNAL(isCristallo(bool)), this, SIGNAL(isCristallo(bool)));
        connect(modello, SIGNAL(isUnguento(bool)), this, SIGNAL(isUnguento(bool)));
        connect(modello, SIGNAL(isAmuleto(bool)), this, SIGNAL(isAmuleto(bool)));
    }

    ~Controller() {
        delete modello;
    }

    void flushControllerMemory() {
        tempDataToSet.clear();
    }

    QImage* getImage() const {
       return image;
    }

    void setImage(QImage* img) {
        image = img;
        modello->setImage(image);
    }
    int getNumObjInMemory() const {
        return modello->getNumObjInMemory();
    }

    void clearMemory() const {
        modello->clearMemory();
    }

    QImage* getResultImage(int contatore =0) const {
        return modello->getImageFromLastObj(contatore);
    }
    QList<QString> getResultParametri(int contatore =0) const {
        QList<QString> parametri;
        QMap<QString, int> values=modello->getLastObj(contatore);
        for(auto it=values.begin();it!=values.end();++it) {
            parametri.push_back(it.key() + '\n' + QString::number(it.value()));
        }
        return parametri;
    }
    void deleteLastObj() {
        modello->deleteLast();
    }

    void combina() const {
        modello->combina();
        connect(modello, SIGNAL(opDone()), this, SIGNAL(opIsDone()));
    }

    int ricicla() const {
        return modello->ricycleLast();
    }

    void potenzia() const {
        modello->potenzia(mana, parametro);
    }

    void crea() const {
        modello->crea(mana, livello, rarita, parametro);
    }
    void distribuisci() const {
        modello->distribuisci();
    }
    void ripara() const {
        modello->ripara();
    }
    void duplica() const {
        modello->duplica();
    }
    void trasforma() const {
        modello->trasforma();
    }
    void estrai() const {
        modello->estrai();
    }


//------------------------------------------------------------------------
public slots:
    void setSelectedObject(QGridLayout* griglia) {

        QList<QString> listaStats=modello->getListaStatsFromLastObj();

        auto it=listaStats.begin();

        int counter=0;
        DisplayAndSlider* displayandslider =0;

        for(; it!=listaStats.end();++it) {
            QString name=(*it);
            displayandslider=new DisplayAndSlider(griglia->parentWidget(), name);
            tempDataToSet.insert(name, displayandslider->getSlider());
            griglia->addWidget(displayandslider,2,counter++);
        }

        //return griglia;
    }

    void setPotenzia(QGridLayout* griglia) {

        QList<QString> listaStats=modello->getListaStatsFromLastObj();

        auto it=listaStats.begin();

        DisplayAndSlider* mana=new DisplayAndSlider(griglia->parentWidget(), "Mana", true);
        tempDataToSet.insert("Mana", mana->getSlider());

        combox=new QComboBox;
        combox->addItem("");

        for(; it!=listaStats.end(); ++it)
            if(*it!="Livello" && *it!="Rarità")
                combox->addItem(*it);

        griglia->addWidget(combox, 2, 1);
        griglia->addWidget(mana, 2,0);
    }

    void setCrea(QGridLayout* griglia) {
        QList<QString> listaStats=modello->getListaStatsFromLastObj();

        auto it=listaStats.begin();

        DisplayAndSlider* mana=new DisplayAndSlider(griglia->parentWidget(), "Mana", true);
        tempDataToSet.insert("Mana", mana->getSlider());
        DisplayAndSlider* livello=new DisplayAndSlider(griglia->parentWidget(), "Livello");
        tempDataToSet.insert("Livello", livello->getSlider());
        DisplayAndSlider* rarita=new DisplayAndSlider(griglia->parentWidget(), "Rarità");
        tempDataToSet.insert("Rarità", rarita->getSlider());

        combox=new QComboBox;
        combox->addItem("");
        for(; it!=listaStats.end(); ++it)
            if(*it!="Livello" && *it!="Rarità")
                combox->addItem(*it);

        griglia->addWidget(combox, 2, 3);
        griglia->addWidget(mana, 2,0);
        griglia->addWidget(livello, 2,1);
        griglia->addWidget(rarita, 2,2);
    }

    void sceltiParametriPotenzia() {
        parametro=combox->currentText();
        mana=tempDataToSet.value("Mana")->value();
        flushControllerMemory();
    }
    void sceltiParametriCrea() {
        parametro=combox->currentText();
        mana=tempDataToSet.value("Mana")->value();
        livello=tempDataToSet.value("Livello")->value();
        rarita=tempDataToSet.value("Rarità")->value();
        flushControllerMemory();
    }

    void setStatsOnObj() {
        for(auto it=tempDataToSet.begin();it!=tempDataToSet.end();++it) {
            modello->setStatByName(it.key(), it.value()->value());
        }
        flushControllerMemory();
    }

    QList<QString> getParametri() const {
        QList<QString> parametri;
        for(auto it=tempDataToSet.begin();it!=tempDataToSet.end();++it) {
            parametri.push_back(it.key() + '\n' + QString::number(it.value()->value()));
        }
        return parametri;
    }



//----------------------------------------------------------------------------
    void newErba() {
        modello->createErba();
    }

    void newUnguento() {
        modello->createUnguento();
    }

    void newPietra() {
        modello->createPietra();
    }

    void newCristallo() {
        modello->createCristallo();
    }

    void newOsso() {
        modello->createOsso();
    }

    void newAmuleto() {
        modello->createAmuleto();
    }

signals:
    void opIsDone();
    void nothingToDelete();

    void isCristallo(bool =false);
    void isUnguento(bool =false);
    void isAmuleto(bool =false);

};

#endif // CONTROLLER_H
