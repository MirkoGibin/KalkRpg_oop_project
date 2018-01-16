#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<QWidget>
#include<QObject>
#include"model.h"
#include"QGridLayout"
#include"displayandslider.h"

class Controller : public QObject {
Q_OBJECT
private:
    Model* modello;
public:
    Controller(Model*model_ =0) : modello(model_) {}
public slots:
    list<string>* erbaButton() {
        modello->createErba();
        return modello->retrieveListaStats();
    }
    QGridLayout* buildObjSliderLCD(QGridLayout* griglia) {
        modello->createErba();
        list<string>* listaStats=modello->retrieveListaStats();
        auto it=listaStats->begin();
        int counter=0;
        for(; it!=listaStats->end();++it) {
            QString name=QString::fromStdString(*it);
            griglia->addWidget(new DisplayAndSlider(0, name),1,counter++);
        }
        delete listaStats;
        return griglia;
    }
};

#endif // CONTROLLER_H
