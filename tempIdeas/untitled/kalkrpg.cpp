#include"kalkrpg.h"

Button *KalkRpg::createObjButton(const char *path, const QString &testo, const char *member) {
    Button *button = new Button(testo, path);
    connect(button, SIGNAL(clicked()), this, SLOT(commonTasksForObject()));
    connect(button, SIGNAL(clicked()), this, member);
    connect(button, SIGNAL(clicked(bool)), this,SLOT(objectClicked()));
    connect(this, SIGNAL(objToClick(bool)),button, SLOT(setEnabled(bool)));
    return button;
}

Button *KalkRpg::createOpButton(const char *path, const QString &testo, const char *member) {
    Button *button = new Button(testo, path);
    connect(button, SIGNAL(clicked()), this, member);
    connect(button, SIGNAL(clicked(bool)), this,SLOT(operationClicked()));
    connect(this, SIGNAL(opToClick(bool)),button, SLOT(setEnabled(bool)));
    button->setDisabled();
    return button;
}

void KalkRpg::removeSettingPanel() { //nasconde pannello di settaggio. Fa il flush del controller. DA METTERE IN PRIVATE
    expansionAndSetGrid->parentWidget()->hide();
    this->adjustSize();
    expansionAndSetGrid->deleteLater();
    confirmObj->deleteLater();
    child->deleteLater();
}

void KalkRpg::showResult(int ris, int contatore) {
    if(controller->getNumObjInMemory()) {
        if(ris)
            display->show(QString::number(ris));
        else display->show(controller->getResultImage(contatore), controller->getResultParametri(contatore));
    }
}

void KalkRpg::showResult(QString s) {
    display->show(s);
}

void KalkRpg::showToSet(Button *pressedButton) {
    settingObj=true;
    settingObjState();

    child=new QWidget(this);
    expansionAndSetGrid=new QGridLayout(child);

    QLabel *image = new QLabel();
    image->setAlignment(Qt::AlignCenter);
    QPixmap *pix = new QPixmap(pressedButton->getPath());
    image->setPixmap(*pix);

    mainLayout->addWidget(child, 3, 0, 1, 3 );

    if(potenziaOp) controller->setPotenzia(expansionAndSetGrid);
    else if(creaOp) controller->setCrea(expansionAndSetGrid);
    else {
        controller->setSelectedObject(expansionAndSetGrid);
    }

    expansionAndSetGrid->addWidget(image, 0, 0, 1, expansionAndSetGrid->columnCount());
    confirmObj=new QPushButton(tr("Conferma"), child);
    confirmObj->setFixedSize(200,50);

    expansionAndSetGrid->addWidget(confirmObj, expansionAndSetGrid->rowCount(), 0, 1, expansionAndSetGrid->columnCount(), Qt::AlignCenter);
    connect(confirmObj, SIGNAL(clicked()), this, SLOT(confirmObjClicked()));

}

void KalkRpg::commonTasksForObject() {
    amuletoObj=false;
    unguentoObj=false;
    cristalloObj=false;
}

void KalkRpg::setChildVariables() {
    if(cristalloObj) cristalloObj=false;
    if(unguentoObj) unguentoObj=false;
    if(amuletoObj) unguentoObj=false;
}

KalkRpg::KalkRpg(QWidget *parent, Controller *controller_) :
    QWidget(parent),
    child(0),
    mainLayout(new QGridLayout),
    controller(controller_),
    expansionAndSetGrid(0),
    confirmObj(0),
    display(new Display),
    waitingOperand(false),
    settingObj(false),
    running(false),
    riciclaOp(false),
    potenziaOp(false),
    creaOp(false),
    trasformaOp(false),
    cristalloObj(false),
    unguentoObj(false),
    amuletoObj(false) {
    setWindowTitle("KalkRPG");

    //creazione pulsanti oggetti
    Button* erbaButton = createObjButton(":/icons/erba.png", tr("Erba"), SLOT(erbaClicked()));
    Button* unguentoButton = createObjButton(":/icons/unguento.png", tr("Unguento"), SLOT(unguentoClicked()));
    Button* pietraButton = createObjButton(":/icons/pietra.png", tr("Pietra"), SLOT(pietraClicked()));
    Button* cristalloButton = createObjButton(":/icons/cristallo.png", tr("Cristallo"), SLOT(cristalloClicked()));
    Button* ossoButton = createObjButton(":/icons/osso.png", tr("Osso"), SLOT(ossoClicked()));
    Button* amuletoButton = createObjButton(":/icons/amuleto.png", tr("Amuleto"), SLOT(amuletoClicked()));

    //creazione pulsanti operazioni unarie
    Button* creaButton = createOpButton(":/icons/crea.png", tr("Crea"), SLOT(creaClicked()));
    //connect(controller, SIGNAL(somethingChanged(bool)), creaButton, SLOT(setDisabled(bool)));
    connect(this, SIGNAL(startOp(bool)), creaButton, SLOT(setEnabled(bool)));
    Button* riciclaButton = createOpButton(":/icons/ricicla.png", tr("Ricicla"), SLOT(riciclaClicked()));
    connect(this, SIGNAL(startOp(bool)), riciclaButton, SLOT(setEnabled(bool)));
    Button* potenziaButton = createOpButton(":/icons/potenzia.png", tr("Potenzia"), SLOT(potenziaClicked()));

    //creazione pulsanti operazioni binarie
    Button* combinaButton = createOpButton(":/icons/combina.png", tr("Combina"), SLOT(combinaClicked()));
    Button* estraiButton = createOpButton(":/icons/estrai.png", tr("Estrai"), SLOT(estraiClicked()));
    Button* trasformaButton = createOpButton(":/icons/trasforma.png", tr("Trasforma"), SLOT(trasformaClicked()));


    Button* distribuisciButton = createOpButton(":/icons/distribuisci.png", tr("Distribuisci"), SLOT(distribuisciClicked()));;
    connect(this, SIGNAL(distribuisciToClick(bool)), distribuisciButton, SLOT(setEnabled(bool)));
    Button* duplicaButton = createOpButton(":/icons/duplica.png", tr("Duplica"), SLOT(duplicaClicked()));;
    connect(this, SIGNAL(duplicaToClick(bool)), duplicaButton, SLOT(setEnabled(bool)));
    Button* riparaButton = createOpButton(":/icons/ripara.png", tr("Ripara"), SLOT(riparaClicked()));;
    connect(this, SIGNAL(riparaToClick(bool)), riparaButton, SLOT(setEnabled(bool)));

    connect(this, SIGNAL(unaryOp(bool)), distribuisciButton, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(unaryOp(bool)), duplicaButton, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(unaryOp(bool)), riparaButton, SLOT(setEnabled(bool)));

    //creazione pulsanti gestione memoria
    Button*backspaceButton=new Button(tr("Backspace"), ":/icons/backspace.png");
    connect(backspaceButton, SIGNAL(clicked()), this, SLOT(backspaceClicked()));
    connect(this, SIGNAL(backspaceToClick(bool)), backspaceButton, SLOT(setEnabled(bool)));

    Button*eraseButton=new Button(tr("Cancella"),":/icons/cancella.png");
    connect(eraseButton, SIGNAL(clicked()), this, SLOT(eraseClicked()));
    connect(this, SIGNAL(eraseToClick(bool)), eraseButton, SLOT(setEnabled(bool)));

    Button*confermaOpButton=new Button(tr("Conferma"),":/icons/confermaOp.png");
    connect(confermaOpButton, SIGNAL(clicked()), this, SLOT(confirmOpClicked()));
    connect(this, SIGNAL(confirmOpToClick(bool)), confermaOpButton, SLOT(setEnabled(bool)));


    //condizione iniziale
    backspaceButton->setDisabled();
    eraseButton->setDisabled();
    confermaOpButton->setDisabled();
    emit startOp(true);
    emit unaryOp(false);

    //creazione del layout
    QGridLayout *objectLayout = new QGridLayout;
    QGridLayout *operationLayout = new QGridLayout;
    QGridLayout *memoryLayout = new QGridLayout;

    //display calcolatrice
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    objectLayout->setSizeConstraint(QLayout::SetFixedSize);
    operationLayout->setSizeConstraint(QLayout::SetFixedSize);
    memoryLayout->setSizeConstraint(QLayout::SetFixedSize);


    objectLayout->addWidget(erbaButton, 0, 0);
    objectLayout->addWidget(unguentoButton, 0, 1);
    objectLayout->addWidget(pietraButton, 1, 0);
    objectLayout->addWidget(cristalloButton, 1, 1);
    objectLayout->addWidget(ossoButton, 2, 0);
    objectLayout->addWidget(amuletoButton, 2, 1);

    operationLayout->addWidget(creaButton, 0, 0);
    operationLayout->addWidget(riciclaButton, 0, 1);
    operationLayout->addWidget(potenziaButton, 0, 2);
    operationLayout->addWidget(estraiButton, 1, 0);
    operationLayout->addWidget(combinaButton, 1, 1);
    operationLayout->addWidget(trasformaButton, 1, 2);
    operationLayout->addWidget(distribuisciButton, 2, 0);
    operationLayout->addWidget(duplicaButton, 2, 1);
    operationLayout->addWidget(riparaButton, 2, 2);

    memoryLayout->addWidget(backspaceButton, 0,0);
    memoryLayout->addWidget(eraseButton,0,1);
    memoryLayout->addWidget(confermaOpButton, 0, 2);

    mainLayout->addLayout(objectLayout, 0, 0);
    mainLayout->addWidget(display, 0, 1, 2, 1);
    mainLayout->addLayout(operationLayout, 0, 2);
    mainLayout->addLayout(memoryLayout, 1, 2, Qt::AlignBottom);

    setLayout(mainLayout);

    //connects per la gestione dei pulsanti della gestione della memoria nella view
    connect(controller, SIGNAL(nothingToDelete()), eraseButton, SLOT(setDisabled()));

    //connects per la gestione dei pulsanti delle operazioni child-only nei back
    connect(controller, SIGNAL(isCristallo(bool)), this, SLOT(cristalloInMemory(bool)));
    connect(controller, SIGNAL(isUnguento(bool)), this, SLOT(unguentoInMemory(bool)));
    connect(controller, SIGNAL(isAmuleto(bool)), this, SLOT(amuletoInMemory(bool)));
}

KalkRpg::~KalkRpg() {
    delete child;
    delete mainLayout;
    delete controller;
    delete expansionAndSetGrid;
    delete display;
    delete confirmObj;
}

void KalkRpg::erbaClicked() {
    controller->newErba();
}

void KalkRpg::unguentoClicked(){
    controller->newUnguento();
    unguentoObj=true;
}

void KalkRpg::pietraClicked(){
    controller->newPietra();
}

void KalkRpg::cristalloClicked() {
    cristalloObj=true;
    controller->newCristallo();
}

void KalkRpg::ossoClicked() {
    controller->newOsso();
}

void KalkRpg::amuletoClicked() {
    amuletoObj=true;
    controller->newAmuleto();
}

void KalkRpg::confirmObjClicked() {
    settingObj=false;
    if(potenziaOp) {
        confirmOpToClickState();
        controller->sceltiParametriPotenzia();
        removeSettingPanel();
    } else if(creaOp) {
        confirmOpToClickState();
        display->show(controller->getImage(), controller->getParametri());
        controller->sceltiParametriCrea();
        removeSettingPanel();
    } else if(trasformaOp){//PER TRASFORMAOP
        display->show(controller->getResultImage(), controller->getResultParametri());
        confirmOpToClickState();
    } else {
        if(!waitingOperand) {
            objIsCreatedState();
        }
        else {
            confirmOpToClickState();
        }
        display->show(controller->getImage(), controller->getParametri());
        controller->setStatsOnObj();
        removeSettingPanel();
    }
    waitingOperand=false;
}

void KalkRpg::objectClicked() {
    Button*pressedButton=qobject_cast<Button*>(sender());
    controller->setImage(new QImage(pressedButton->getPath()));
    if(!trasformaOp)
        showToSet(pressedButton);
    else {
        confirmObjClicked();
    }
}

void KalkRpg::creaClicked() {
    if(running) {
        controller->crea();
        opButton=nullptr;
        creaOp=false;
        running=false;
        showResult();
    } else {
        waitingOperand=true;
        creaOp=true;
        running=true;
    }
}

void KalkRpg::riciclaClicked() {
    if(running) {
        int result=controller->ricicla();
        running=false;
        opButton=nullptr;
        riciclaOp=false;
        showResult(result);
    } else {
        waitingOperand=true;
        running=true;
        riciclaOp=true;
    }
}

void KalkRpg::combinaClicked() {
    if(running) {
        controller->combina();
        running=false;
        opButton=nullptr;
        showResult();
    } else {
        waitingOperand=true;
        running=true;
    }
}

void KalkRpg::estraiClicked() {
    if(running) {
        try {
            controller->estrai();
            showResult();
        } catch(ViewException ve) {
            showResult(ve.getErrore());
        }
        running=false;
        trasformaOp=false; //USIAMO LA STESSA VARIABILE di trasformaOp PERCHE IL COMPORTAMENTO E' LO STESSO
        opButton=nullptr;
    } else {
        waitingOperand=true;
        running=true;
        trasformaOp=true;
    }
}

void KalkRpg::potenziaClicked() {
    if(running) {
        controller->potenzia();
        running=false;
        opButton=nullptr;
        potenziaOp=false;
        showResult();
    } else {
        potenziaOp=true;
        showToSet(qobject_cast<Button*>(sender()));
        //waitingOperand=false;
        running=true;
    }
}

void KalkRpg::trasformaClicked() {
    if(running) {
        try {
            controller->trasforma();
            showResult();
        } catch(ViewException ve) {
            showResult(ve.getErrore());
        }
        running=false;
        trasformaOp=false;
        opButton=nullptr;
    } else {
        waitingOperand=true;
        running=true;
        trasformaOp=true;
    }
}

void KalkRpg::distribuisciClicked(){
    if(running) {
        controller->distribuisci();
        running=false;
        opButton=nullptr;
        showResult(0,1);
        showResult(0,0);
    } else {
        waitingOperand=true;
        running=true;
    }
}

void KalkRpg::duplicaClicked(){
    if(running) {
        controller->duplica();
        running=false;
        opButton=nullptr;
        showResult(0,1);
        showResult(0,0);
    } else {
        waitingOperand=true;
        running=true;
    }
}

void KalkRpg::riparaClicked(){
    if(running) {
        controller->ripara();
        running=false;
        opButton=nullptr;
        showResult(0,1);
        showResult(0,0);
    } else {
        waitingOperand=true;
        running=true;
    }
}

void KalkRpg::operationClicked() {
    if(running) {
        opButton=qobject_cast<Button*>(sender());
        display->show(opButton->getPath());
        if(!potenziaOp) objIsCreatedState();
    }
}

void KalkRpg::confirmOpClicked() {
    opButton->setEnabled();
    opButton->animateClick();
    display->show(qobject_cast<Button*>(sender())->getPath());
    doneState();
}

void KalkRpg::backspaceClicked() {
    if(settingObj) { //pressing back in first settingObject
        settingObj=false;
        setChildVariables();
        removeSettingPanel();
        if(potenziaOp) {
            display->back();
            potenziaOp=false;
            running=false;
            controller->flushControllerMemory();
        } else if(creaOp) {
            controller->deleteLastObj();
            waitingOperand=true;
        }
        else controller->deleteLastObj();
    } else if(!waitingOperand && running) { //in CONFIRM STATE
        display->back();
        if(potenziaOp) { //per potenziaOp
            running=false;
            potenziaOp=false;
        } else { //valido anche per creaOp, trasformaOp, estraiOp
            waitingOperand=true;
            controller->deleteLastObj();
            setChildVariables();
        }
    } else if(waitingOperand && running) {
        display->back();
        waitingOperand=false;
        running=false;
        riciclaOp=false;
        creaOp=false;
        trasformaOp=false;
    } else {
        setChildVariables();
        display->back();
        controller->deleteLastObj();
    }
    return objIsCreatedState();
}

void KalkRpg::eraseClicked() {
    waitingOperand=false;
    running=false;

    riciclaOp=false;
    potenziaOp=false;
    creaOp=false;
    trasformaOp=false;

    cristalloObj=false;
    unguentoObj=false;
    amuletoObj=false;

    if(settingObj) { //se clicco erase mentre sto settando oggetti
        removeSettingPanel();
        settingObj=false;
    }
    controller->clearMemory();
    objIsCreatedState();
    display->clear();
}

void KalkRpg::settingObjState() {
    emit objToClick(false);
    emit opToClick(false);
    emit confirmOpToClick(false);
    emit backspaceToClick(true);
    emit eraseToClick(true);
}

void KalkRpg::setChildMethods() {
    if(cristalloObj) emit distribuisciToClick(true);
    else emit distribuisciToClick(false);
    if(unguentoObj) emit riparaToClick(true);
    else emit riparaToClick(false);
    if(amuletoObj) emit duplicaToClick(true);
    else emit duplicaToClick(false);
}

void KalkRpg::objIsCreatedState() {
    emit objToClick(true);
    if(waitingOperand)
        emit opToClick(false);
    else  {
        emit opToClick(true);
        setChildMethods();
    }
    emit confirmOpToClick(false);
    emit backspaceToClick(true);
    if(controller->getNumObjInMemory()) emit eraseToClick(true);
    else {
        emit eraseToClick(false);
        emit opToClick(false);
    }
    if(!riciclaOp && !waitingOperand && !running) emit startOp(true);
}

void KalkRpg::confirmOpToClickState() {
    emit objToClick(false);
    emit opToClick(false);
    emit confirmOpToClick(true);
    emit backspaceToClick(true);
    emit eraseToClick(true);
}

void KalkRpg::doneState() {
    emit objToClick(false);
    emit opToClick(false);
    emit confirmOpToClick(false);
    emit backspaceToClick(false);
    emit eraseToClick(true);
}

void KalkRpg::cristalloInMemory(bool flag) {
    cristalloObj=flag;
}

void KalkRpg::unguentoInMemory(bool flag) {
    unguentoObj=flag;
}

void KalkRpg::amuletoInMemory(bool flag) {
    amuletoObj=flag;
}
