#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<QObject>
#include"model.h"
#include"QGridLayout"
#include"displayandslider.h"
#include"button.h"
#include<QSlider>

class Controller : public QObject {
Q_OBJECT
private:
    Model* modello;

    //data for setting object
    QMap<QString, QSlider*> tempDataToSet;

public:
    Controller(Model*model_ =0) : modello(model_) {}
    ~Controller() {
        delete modello;
    }
    void flushControllerMemory() {
        tempDataToSet.clear();
    }

public slots:
    bool newErba() {
        int before=modello->getNumObjInMemory();
        modello->createErba();
        int after=modello->getNumObjInMemory();
        return before++==after;
    }

    void showSelectedObject(QGridLayout* griglia, Button* pressedButton) {

        Button*button=new Button(pressedButton->getIcona(), pressedButton->getTesto(), griglia->parentWidget());

        griglia->addWidget(button,0,0);
        list<string>* listaStats=modello->getListaStatFromLastObj();

        auto it=listaStats->begin();

        int counter=0;
        DisplayAndSlider* displayandslider;

        displayandslider=new DisplayAndSlider(griglia->parentWidget(), "livello");
        griglia->addWidget(displayandslider,2,counter++);
        tempDataToSet.insert("livello", displayandslider->getSlider());

        displayandslider=new DisplayAndSlider(griglia->parentWidget(), "rarita");
        griglia->addWidget(displayandslider,2,counter++);
        tempDataToSet.insert("rarita", displayandslider->getSlider());

        for(; it!=listaStats->end();++it) {
            QString name=QString::fromStdString(*it);
            displayandslider=new DisplayAndSlider(griglia->parentWidget(), name);
            tempDataToSet.insert(name, displayandslider->getSlider());
            griglia->addWidget(displayandslider,2,counter++);
        }
        delete listaStats;
        //return griglia;
    }
    void setStatsOnObj() const {
        for(auto it=tempDataToSet.begin();it!=tempDataToSet.end();++it) {
            modello->setStatByName(it.key(), it.value()->value());
        }
    }
};

#endif // CONTROLLER_H
