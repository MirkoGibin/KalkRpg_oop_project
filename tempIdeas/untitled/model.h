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
    QMap<QString, int> getLastObj() const {
        QMap<QString, int> values;
        if(!memoria.isEmpty()) {
            values.insert("Livello", memoria.front()->getLivello());
            values.insert("Rarità", memoria.front()->getRarita());
            list<string> objListaStats=memoria.front()->getListaStats();
            for(auto it=objListaStats.begin();it!=objListaStats.end();++it)
                values.insert(QString::fromStdString(*it), memoria.front()->getValoreStat(*it));
        } else {} //eccezione
        return values;
    }

    QList<QString> getListaStatsFromLastObj() const {
        if(!memoria.isEmpty())
            return QList<QString>(getLastObj().keys());
        else {}//throw exception
        return QList<QString>();
    }
    QImage* getImageFromLastObj() const {
        if(!immagini.isEmpty())
            return immagini.value(counter);
        else return 0;
    }


    unsigned int getNumObjInMemory() const {
        return counter; //memoria.size();
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
        if(counter) {
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
        counter++;
    }
    void createUnguento() {
        memoria.push_front(new Unguento());
        counter++;
    }
    void createPietra() {
        memoria.push_front(new Pietra());
        counter++;
    }
    void createCristallo() {
        memoria.push_front(new Cristallo());
        counter++;
    }
    void createOsso() {
        memoria.push_front(new Osso());
        counter++;
    }
    void createAmuleto() {
        memoria.push_front(new Amuleto());
        counter++;
    }
signals:
    void opDone();
    void nothingToDelete();

};

#endif // MODEL_H
