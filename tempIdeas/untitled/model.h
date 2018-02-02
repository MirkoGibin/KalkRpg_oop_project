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
            if(counter)
                whatsInMemory();
        }
        else emit nothingToDelete();
    }
    void whatsInMemory() {
        if(dynamic_cast<Cristallo*>(memoria.back())) {
            emit isCristallo(true);
            emit isUnguento(false);
            emit isAmuleto(false);
        } else
        if(dynamic_cast<Unguento*>(memoria.back())) {
            emit isUnguento(true);
            emit isCristallo(false);
            emit isAmuleto(false);
        } else
        if(dynamic_cast<Amuleto*>(memoria.back())) {
            emit isAmuleto(true);
            emit isCristallo(false);
            emit isUnguento(false);
        }
        else {
            emit isAmuleto(false);
            emit isCristallo(false);
            emit isUnguento(false);
        }
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
            if(cri) {
                cri->distribuisci(parametro);

                memoria.push_back(cri);
                immagini.insert(++counter, criImage);

                memoria.push_back(parametro);
                immagini.insert(++counter, parametroImage);
            } else {} //LANCIA ECCEZIONE
        }
        emit opDone();
    }

    void ripara() {
        if(getNumObjInMemory()>1) {
            auto it=--(memoria.end());
            it--;
            Unguento*ung=(dynamic_cast<Unguento*>(*it))->clone();
            QImage* ungImage=new QImage((*immagini.value(counter-1)));

            Oggetto* parametro=(memoria.back())->clone();
            QImage* parametroImage=new QImage((*immagini.value(counter)));
            if(ung) {
                ung->ripara(parametro);

                memoria.push_back(ung);
                immagini.insert(++counter, ungImage);

                memoria.push_back(parametro);
                immagini.insert(++counter, parametroImage);
            } else {} //LANCIA ECCEZIONE
        }
        emit opDone();
    }

    void duplica() {
        if(getNumObjInMemory()>1) {
            auto it=--(memoria.end());
            it--;
            Amuleto*amu=(dynamic_cast<Amuleto*>(*it)->clone());
            QImage* amuImage=new QImage((*immagini.value(counter-1)));

            Oggetto* parametro=(memoria.back());
            QImage* parametroImage=new QImage((*immagini.value(counter)));
            if(amu) {
                Oggetto*nuovo=amu->duplica(parametro);

                memoria.push_back(amu);
                immagini.insert(++counter, amuImage);

                memoria.push_back(nuovo);
                immagini.insert(++counter, parametroImage);
            } else {} //LANCIA ECCEZIONE
        }
        emit opDone();
    }

    void trasforma() {
        if(getNumObjInMemory()>1) {
            try {
                auto it=--(memoria.end());
                it--;
                Oggetto*inv=(memoria.back())->clone();
                Oggetto* parametro=(*it);
                memoria.push_back(inv);
                inv->trasformaDa(parametro);
                QImage* toInsert=new QImage((*immagini.value(counter)));
                immagini.insert(++counter, toInsert);
            } catch(OperationException oe) {
                //emit error(QString::fromStdString(oe));
                Oggetto*o=memoria.back();
                memoria.pop_back();
                delete o;
                throw ViewException(QString::fromStdString(oe.getErrore()));
            }
        }
        emit opDone();
    }

    void estrai() {
        if(getNumObjInMemory()>1) {
            try {
                auto it=--(memoria.end());
                it--;
                Oggetto*inv=(memoria.back())->clone();
                Oggetto* parametro=(*it);

                if(dynamic_cast<Cristallo*>(inv))
                    dynamic_cast<Cristallo*>(inv)->estraiDa(parametro);
                else
                if(dynamic_cast<Unguento*>(inv))
                    dynamic_cast<Unguento*>(inv)->estraiDa(parametro);
                else
                if(dynamic_cast<Amuleto*>(inv))
                    dynamic_cast<Amuleto*>(inv)->estraiDa(parametro);
                else {
                    delete inv;
                    throw OperationException(OperationException::estrazione);
                }

                memoria.push_back(inv);
                QImage* toInsert=new QImage((*immagini.value(counter)));
                immagini.insert(++counter, toInsert);
            } catch(OperationException oe) {
                //emit error(QString::fromStdString(oe));
                throw ViewException(QString::fromStdString(oe.getErrore()));

            }
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
    void isUnguento(bool =false);
    void isAmuleto(bool =false);

    void error(QString);
};

#endif // MODEL_H
