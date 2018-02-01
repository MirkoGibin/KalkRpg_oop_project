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
    QMap<QString, int> getLastObj(int contatore =0) const {
        QMap<QString, int> values;
        if(!memoria.isEmpty()) {
            auto obj=--(memoria.end());
            if(contatore<memoria.size())
                for(int i=0;i<contatore;i++) obj--;

            values.insert("Livello", (*obj)->getLivello());
            values.insert("Rarità", (*obj)->getRarita());
            list<string> objListaStats=(*obj)->getListaStats();
            for(auto it=objListaStats.begin();it!=objListaStats.end();++it)
                values.insert(QString::fromStdString(*it), (*obj)->getValoreStat(*it));
        } else {} //eccezione
        return values;
    }

    QList<QString> getListaStatsFromLastObj(int contatore =0) const {
        if(!memoria.isEmpty())
            return QList<QString>(getLastObj(contatore).keys());
        else {}//throw exception
        return QList<QString>();
    }
    QImage* getImageFromLastObj(int contatore =0) const {
        if(!immagini.isEmpty())
            return immagini.value(counter-contatore);
        else return 0;
    }


    unsigned int getNumObjInMemory() const {
        return counter; //memoria.size();
    }

    bool setStatByName(QString name, unsigned int value) const {
        if(name=="Livello")
            memoria.back()->setLivello(value);
        else if(name=="Rarità")
                memoria.back()->setRarita(value);
        else
        memoria.back()->modifyStat(name.toStdString(), value);
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
        emit nothingToDelete();
    }
    void deleteLast() {
        if(counter) {
            Oggetto* o=memoria.back();
            memoria.pop_back();
            delete o;
            QImage* i=immagini.value(counter);
            immagini.remove(counter);
            delete i;
            counter--;
            if(!counter) emit nothingToDelete();
            if(counter && dynamic_cast<Cristallo*>(memoria.back())) emit isCristallo(true);
        }
        else emit nothingToDelete();
    }


//OPERATIONS-----------------------------------------------------------
    int ricycleLast() {
        return memoria.back()->ricicla();
    }
    void combina() {
        if(getNumObjInMemory()) {
            auto it=--(memoria.end());
            it--;
            Oggetto* nuovo=(memoria.back())->clone();
            nuovo->combina(*it);
            memoria.push_back(nuovo);
            QImage* toInsert=new QImage((*immagini.value(counter)));
            immagini.insert(++counter, toInsert);
        }
        emit opDone();
    }

    void potenzia(int mana, QString parametro) {
        if(getNumObjInMemory()) {
            Oggetto* nuovo=memoria.back()->clone();
            nuovo->potenzia(mana, parametro.toStdString());
            QImage* toInsert=new QImage((*immagini.value(counter)));
            immagini.insert(++counter, toInsert);
            memoria.push_back(nuovo);
        } else {} //ECCEZIONI
        emit opDone();
    }

    void crea(int mana, int livello, int rarita, QString parametro) {
        if(getNumObjInMemory()) {
            Oggetto* nuovo=memoria.back()->clone();
            nuovo->crea(mana, livello, rarita, parametro.toStdString());
            QImage* toInsert=new QImage((*immagini.value(counter)));
            immagini.insert(++counter, toInsert);
            memoria.push_back(nuovo);
        } else {} //eccezioni
        emit opDone();
    }

    void distribuisci() {
        if(getNumObjInMemory()>1) {
            auto it=--(memoria.end());
            it--;
            Cristallo*cri=(dynamic_cast<Cristallo*>(*it))->clone();
            QImage* criImage=new QImage((*immagini.value(counter-1)));

            Oggetto* parametro=(memoria.back())->clone();
            QImage* parametroImage=new QImage((*immagini.value(counter)));

            cri->distribuisci(parametro);

            memoria.push_back(cri);
            immagini.insert(++counter, criImage);

            memoria.push_back(parametro);
            immagini.insert(++counter, parametroImage);
        }
        emit opDone();
    }

//CREATE OBJECT IN MEMORY------------------------------------------------
    void createErba() {
        memoria.push_back(new Erba());
        counter++;
    }
    void createUnguento() {
        memoria.push_back(new Unguento());
        counter++;
    }
    void createPietra() {
        memoria.push_back(new Pietra());
        counter++;
    }
    void createCristallo() {
        memoria.push_back(new Cristallo());
        counter++;
    }
    void createOsso() {
        memoria.push_back(new Osso());
        counter++;
    }
    void createAmuleto() {
        memoria.push_back(new Amuleto());
        counter++;
    }
signals:
    void opDone();
    void nothingToDelete();
    void isCristallo(bool =false);

};

#endif // MODEL_H
