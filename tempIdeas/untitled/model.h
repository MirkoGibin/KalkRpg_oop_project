#ifndef MODEL_H
#define MODEL_H
#include<QObject>
#include<QMap>
#include<QString>
#include<QImage>
#include<QSlider>
#include<QList>
#include<list>
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
    Model() : counter(0) {}

//------------------------------------------------------------
    QList<QString>* getListaStatsFromLastObj() {
        if(!memoria.isEmpty())
            return new QList<QString>(getLastObj()->keys());
        else return 0;
    }
    QImage* getImageFromLastObj() {
        if(!immagini.isEmpty())
            return immagini.value(counter);
        else return 0;
    }

    QMap<QString, int>* getLastObj() {
        if(!memoria.isEmpty()) {
            QMap<QString, int>* values=new QMap<QString, int>();
            values->insert("Livello", memoria.front()->getLivello());
            values->insert("Rarità", memoria.front()->getRarita());
            list<string>* objListaStats=memoria.front()->getListaStats();
            for(auto it=objListaStats->begin();it!=objListaStats->end();++it)
                values->insert(QString::fromStdString(*it), memoria.front()->getValoreStat(*it));
            return values;
        } else return 0;
    }

    unsigned int getNumObjInMemory() const {
        return counter;//memoria.size();
    }

    bool setStatByName(QString name, unsigned int value) const {
        if(name=="Livello")
            memoria.front()->setLivello(value);
        else if(name=="Rarità")
                memoria.front()->setRarita(value);
        else
        memoria.front()->modifyStat(name.toStdString(), value);
        return true;
    }

    void setImage(QImage* immagine) {
        counter++;
        immagini.insert(counter, new QImage(*immagine));
    }
    void clearMemory() {
        if(counter) {
            memoria.clear();
            immagini.clear();
            counter=0;
        }
        else emit nothingToDelete();

    }
    void deleteLast() {
        if(!memoria.isEmpty()) {
            Oggetto* o=memoria.front();
            memoria.pop_front();
            delete o;
            QImage* i=immagini.value(counter);
            immagini.remove(counter);
            delete i;
            counter--;
        } else emit nothingToDelete();
    }


//-----------------------------------------------------------
    int ricycleLast() {
        return memoria.front()->ricicla();
    }
    void combina() {
        if(getNumObjInMemory()) {
            auto it=memoria.begin();
            it++;
            Oggetto* nuovo=(memoria.front())->clone();
            nuovo->combina(*it);
            memoria.push_front(nuovo);
            QImage* toInsert=new QImage((*immagini.value(counter)));
            immagini.insert(++counter, toInsert);
        }
        emit opDone();
    }
    void createErba() {
        memoria.push_front(new Erba());
    }
    void createUnguento() {
        memoria.push_front(new Unguento());
    }
    void createPietra() {
        memoria.push_front(new Pietra());
    }
    void createCristallo() {
        memoria.push_front(new Cristallo());
    }
    void createOsso() {
        memoria.push_front(new Osso());
    }
    void createAmuleto() {
        memoria.push_front(new Amuleto());
    }
signals:
    void opDone();
    void nothingToDelete();

};

#endif // MODEL_H
