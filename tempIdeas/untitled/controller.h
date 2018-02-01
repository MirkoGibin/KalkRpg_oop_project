#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<QObject>
#include"model.h"
#include"QGridLayout"
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
    Controller(/*QImage* img =0*/) : modello(new Model()), image(/*img*/0),
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
        //int mana=tempDataToSet.value("mana")->value();
        modello->potenzia(mana, parametro);
        //flushControllerMemory();
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
            connect(displayandslider->getSlider(), SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));
            griglia->addWidget(displayandslider,2,counter++);
        }

        //return griglia;
    }

    void setPotenzia(QGridLayout* griglia) {

        QList<QString> listaStats=modello->getListaStatsFromLastObj();

        auto it=listaStats.begin();

        //int counter=0;
        DisplayAndSlider* mana=new DisplayAndSlider(griglia->parentWidget(), "Mana");
        tempDataToSet.insert("Mana", mana->getSlider());

        combox=new QComboBox;

        for(; it!=listaStats.end(); ++it)
            if(*it!="Livello" && *it!="Rarità")
                combox->addItem(*it);

        griglia->addWidget(combox, 2, 1);
        griglia->addWidget(mana, 2,0);
    }

    void setCrea(QGridLayout* griglia) {
        QList<QString> listaStats=modello->getListaStatsFromLastObj();

        auto it=listaStats.begin();

        //int counter=0;
        DisplayAndSlider* mana=new DisplayAndSlider(griglia->parentWidget(), "Mana");
        tempDataToSet.insert("Mana", mana->getSlider());
        DisplayAndSlider* livello=new DisplayAndSlider(griglia->parentWidget(), "Livello");
        tempDataToSet.insert("Livello", livello->getSlider());
        DisplayAndSlider* rarita=new DisplayAndSlider(griglia->parentWidget(), "Rarità");
        tempDataToSet.insert("Rarità", rarita->getSlider());

        combox=new QComboBox;
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
        //modello->setImage(image);
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
    bool newErba() {
        int before=modello->getNumObjInMemory();
        modello->createErba();
        //modello->setImage(image);
        int after=modello->getNumObjInMemory();
        return before++==after;
    }

    bool newUnguento() {
        int before=modello->getNumObjInMemory();
        modello->createUnguento();
        //modello->setImage(image);
        int after=modello->getNumObjInMemory();
        return before++==after;
    }

    bool newPietra() {
        int before=modello->getNumObjInMemory();
        modello->createPietra();
        //modello->setImage(image);
        int after=modello->getNumObjInMemory();
        return before++==after;
    }

    bool newCristallo() {
        int before=modello->getNumObjInMemory();
        modello->createCristallo();
        //modello->setImage(image);
        int after=modello->getNumObjInMemory();
        return before++==after;
    }

    bool newOsso() {
        int before=modello->getNumObjInMemory();
        modello->createOsso();
        //modello->setImage(image);
        int after=modello->getNumObjInMemory();
        return before++==after;
    }

    bool newAmuleto() {
        int before=modello->getNumObjInMemory();
        modello->createAmuleto();
        //modello->setImage(image);
        int after=modello->getNumObjInMemory();
        return before++==after;
    }
    void sliderChanged(int) {
        emit somethingChanged(true);
    }

signals:
    void somethingChanged(bool =false);
    void opIsDone();
    void nothingToDelete();

    void isCristallo(bool =false);
    void isUnguento(bool =false);
    void isAmuleto(bool =false);
};

#endif // CONTROLLER_H
