#include "model.h"
#include"memoryexception.h"


Model::Model() : counter(0) {}

QMap<QString, int> Model::getLastObj(int contatore) const {
    if(!memoria.isEmpty()) {
        QMap<QString, int> values;
        auto obj=--(memoria.end());
        if(contatore<memoria.size())
            for(int i=0;i<contatore;i++) obj--;

        values.insert("Livello", (*obj)->getLivello());
        values.insert("Rarità", (*obj)->getRarita());
        list<string> objListaStats=(*obj)->getListaStats();
        for(auto it=objListaStats.begin();it!=objListaStats.end();++it)
            values.insert(QString::fromStdString(*it), (*obj)->getValoreStat(*it));
        return values;
    } else throw MemoryException("mv");
}

QList<QString> Model::getListaStatsFromLastObj(int contatore) const {
    if(!memoria.isEmpty())
        return QList<QString>(getLastObj(contatore).keys());
    else throw MemoryException("mv");
}

QImage *Model::getImageFromLastObj(int contatore) const {
    if(!immagini.isEmpty())
        return immagini.value(counter-contatore);
    else throw MemoryException("mv");
}

unsigned int Model::getNumObjInMemory() const {
    return counter; //memoria.size();
}

bool Model::setStatByName(QString name, unsigned int value) const {
    if(!memoria.isEmpty()) {
        if(name=="Livello")
            memoria.back()->setLivello(value);
        else if(name=="Rarità")
            memoria.back()->setRarita(value);
        else
            memoria.back()->modifyStat(name.toStdString(), value);
        return true;
    } else throw MemoryException("mv");
}

void Model::setImage(QImage *immagine) {
    if(!memoria.isEmpty())
        immagini.insert(counter, new QImage(*immagine));
    else throw MemoryException("mv");
}

void Model::clearMemory() {
    if(counter) {
        memoria.clear();
        immagini.clear();
        counter=0;
    }
    emit nothingToDelete();
}

void Model::deleteLast() {
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

int Model::ricycleLast() {
    if(!memoria.isEmpty()) return memoria.back()->ricicla();
    else throw MemoryException("mv");
}

void Model::combina() {
    if(getNumObjInMemory()>1) {
        auto it=--(memoria.end());
        it--;
        Oggetto* inv=(*it)->clone();
        Oggetto*parametro=memoria.back();
        inv->combina(parametro);
        memoria.push_back(inv);
        QImage* toInsert=new QImage((*immagini.value(counter-1)));
        immagini.insert(++counter, toInsert);
    } else throw MemoryException("mv");
}

void Model::potenzia(int mana, QString parametro) {
    if(getNumObjInMemory()) {
        Oggetto* nuovo=memoria.back()->clone();
        nuovo->potenzia(mana, parametro.toStdString());
        QImage* toInsert=new QImage((*immagini.value(counter)));
        immagini.insert(++counter, toInsert);
        memoria.push_back(nuovo);
    } else throw MemoryException("mv");
}

void Model::crea(int mana, int livello, int rarita, QString parametro) {
    if(getNumObjInMemory()) {
        Oggetto* nuovo=memoria.back()->clone();
        nuovo->crea(mana, livello, rarita, parametro.toStdString());
        QImage* toInsert=new QImage((*immagini.value(counter)));
        immagini.insert(++counter, toInsert);
        memoria.push_back(nuovo);
    } else throw MemoryException("mv");
}

void Model::distribuisci() {
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
        }
    } else throw MemoryException("mv");
}

void Model::ripara() {
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
        }
    } else throw MemoryException("mv");
}

void Model::duplica() {
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
        }
    } else throw MemoryException("mv");
}

void Model::trasforma() {
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
            Oggetto*o=memoria.back();
            memoria.pop_back();
            delete o;
            throw ViewException(QString::fromStdString(oe.getErrore()));
        }
    } else throw MemoryException("mv");
}

void Model::estrai() {
    if(getNumObjInMemory()>1) {
        try {
            auto it=--(memoria.end());
            it--;
            Oggetto*inv=(memoria.back())->clone();
            Oggetto* parametro=(*it);

            Cristallo*c =dynamic_cast<Cristallo*>(inv);
            if(c) c->estraiDa(parametro);
            else {
                Amuleto* a =dynamic_cast<Amuleto*>(inv);
                if(a) a->estraiDa(parametro);
                else {
                    Unguento* u =dynamic_cast<Unguento*>(inv);
                    if(u) u->estraiDa(parametro);
                    else {
                        delete inv;
                        throw OperationException(OperationException::estrazione);
                    }
                }
            }
            memoria.push_back(inv);
            QImage* toInsert=new QImage((*immagini.value(counter)));
            immagini.insert(++counter, toInsert);
        } catch(OperationException oe) {
            throw ViewException(QString::fromStdString(oe.getErrore()));

        }
    } else throw MemoryException("mv");
}

void Model::createErba() {
    memoria.push_back(new Erba());
    counter++;
}

void Model::createUnguento() {
    memoria.push_back(new Unguento());
    counter++;
}

void Model::createPietra() {
    memoria.push_back(new Pietra());
    counter++;
}

void Model::createCristallo() {
    memoria.push_back(new Cristallo());
    counter++;
}

void Model::createOsso() {
    memoria.push_back(new Osso());
    counter++;
}

void Model::createAmuleto() {
    memoria.push_back(new Amuleto());
    counter++;
}

void Model::whatsInMemory() {
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
