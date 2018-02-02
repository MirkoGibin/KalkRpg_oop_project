#include "controller.h"

Controller::Controller() : modello(new Model()), image(0),
    combox(0), parametro(""), mana(1), livello(1), rarita(1)  {
    connect(modello, SIGNAL(nothingToDelete()), this, SIGNAL(nothingToDelete()));
    connect(modello, SIGNAL(isCristallo(bool)), this, SIGNAL(isCristallo(bool)));
    connect(modello, SIGNAL(isUnguento(bool)), this, SIGNAL(isUnguento(bool)));
    connect(modello, SIGNAL(isAmuleto(bool)), this, SIGNAL(isAmuleto(bool)));
}

Controller::~Controller() {
    delete modello;
}

void Controller::flushControllerMemory() {
    tempDataToSet.clear();
}

void Controller::clearMemory() const {
    modello->clearMemory();
}

void Controller::deleteLastObj() {
    modello->deleteLast();
}

void Controller::sceltiParametriPotenzia() {
    parametro=combox->currentText();
    mana=tempDataToSet.value("Mana")->value();
    flushControllerMemory();
}

void Controller::sceltiParametriCrea() {
    parametro=combox->currentText();
    mana=tempDataToSet.value("Mana")->value();
    livello=tempDataToSet.value("Livello")->value();
    rarita=tempDataToSet.value("Rarità")->value();
    flushControllerMemory();
}

QImage *Controller::getImage() const {
    return image;
}

int Controller::getNumObjInMemory() const {
    return modello->getNumObjInMemory();
}

QImage *Controller::getResultImage(int contatore) const {
    return modello->getImageFromLastObj(contatore);
}

QList<QString> Controller::getResultParametri(int contatore) const {
    QList<QString> parametri;
    QMap<QString, int> values=modello->getLastObj(contatore);
    for(auto it=values.begin();it!=values.end();++it) {
        parametri.push_back(it.key() + '\n' + QString::number(it.value()));
    }
    return parametri;
}

QList<QString> Controller::getParametri() const {
    QList<QString> parametri;
    for(auto it=tempDataToSet.begin();it!=tempDataToSet.end();++it) {
        parametri.push_back(it.key() + '\n' + QString::number(it.value()->value()));
    }
    return parametri;
}

void Controller::setImage(QImage *img) {
    image = img;
    modello->setImage(image);
}

void Controller::setSelectedObject(QGridLayout *griglia) {

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
}

void Controller::setPotenzia(QGridLayout *griglia) {

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

void Controller::setCrea(QGridLayout *griglia) {
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

void Controller::setStatsOnObj() {
    for(auto it=tempDataToSet.begin();it!=tempDataToSet.end();++it) {
        modello->setStatByName(it.key(), it.value()->value());
    }
    flushControllerMemory();
}

void Controller::combina() const {
    modello->combina();
}

int Controller::ricicla() const {
    return modello->ricycleLast();
}

void Controller::potenzia() const {
    modello->potenzia(mana, parametro);
}

void Controller::crea() const {
    modello->crea(mana, livello, rarita, parametro);
}

void Controller::distribuisci() const {
    modello->distribuisci();
}

void Controller::ripara() const {
    modello->ripara();
}

void Controller::duplica() const {
    modello->duplica();
}

void Controller::trasforma() const {
    modello->trasforma();
}

void Controller::estrai() const {
    modello->estrai();
}

void Controller::newErba() {
    modello->createErba();
}

void Controller::newUnguento() {
    modello->createUnguento();
}

void Controller::newPietra() {
    modello->createPietra();
}

void Controller::newCristallo() {
    modello->createCristallo();
}

void Controller::newOsso() {
    modello->createOsso();
}

void Controller::newAmuleto() {
    modello->createAmuleto();
}
