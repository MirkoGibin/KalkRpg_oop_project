    #ifndef KALKRPG_H
#define KALKRPG_H
#include <QGridLayout>
#include<QPushButton>
#include<QTextEdit>
#include<QTextTable>
#include<QLabel>
#include<QPixmap>
#include"controller.h"
#include "button.h"
#include "display.h"


class KalkRpg : public QWidget {
    Q_OBJECT
private:
    QWidget*child;
    QGridLayout *mainLayout;
    Controller* controller;
    QGridLayout* expansionAndSetGrid;
    QPushButton* confirmObj;
    Display* display;
    Button*opButton;

    bool waitingOperand;
    bool settingObj;
    bool running;
    //bool opHasBeenDone;


    Button* createObjButton(const char *path, const QString &testo, const char* member) {
        Button *button = new Button(testo, path);
        connect(button, SIGNAL(clicked()), this, member);
        connect(button, SIGNAL(clicked(bool)), this,SLOT(objectClicked()));
        connect(this, SIGNAL(objToClick(bool)),button, SLOT(setEnabled(bool)));
        return button;
    }

    Button* createOpButton(const char *path, const QString &testo, const char* member) {
        Button *button = new Button(testo, path);
        connect(button, SIGNAL(clicked()), this, member);
        connect(button, SIGNAL(clicked(bool)), this,SLOT(operationClicked()));
        connect(this, SIGNAL(opToClick(bool)),button, SLOT(setEnabled(bool)));
        button->setDisabled();
        return button;
    }

public:
    KalkRpg(QWidget *parent = 0, Controller* controller_ =0 ) :
        QWidget(parent),
        child(0),
        mainLayout(new QGridLayout),
        controller(controller_),
        expansionAndSetGrid(0),
        confirmObj(0),
        display(new Display),
        waitingOperand(false),
        settingObj(false),
        running(false) {
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
        connect(controller, SIGNAL(somethingChanged(bool)), creaButton, SLOT(setDisabled(bool)));
        Button* riciclaButton = createOpButton(":/icons/ricicla.png", tr("Ricicla"), SLOT(riciclaClicked()));
        Button* potenziaButton = createOpButton(":/icons/potenzia.png", tr("Potenzia"), SLOT(potenziaClicked()));

        //creazione pulsanti operazioni binarie
        Button* combinaButton = createOpButton(":/icons/combina.png", tr("Combina"), SLOT(combinaClicked()));
        Button* estraiButton = createOpButton(":/icons/estrai.png", tr("Estrai"), SLOT(estraiClicked()));
        Button* trasformaButton = createOpButton(":/icons/trasforma.png", tr("Trasforma"), SLOT(trasformaClicked()));
        Button* distribuisciButton = createOpButton(":/icons/distribuisci.png", tr("Distribuisci"), SLOT(distribuisciClicked()));;
        Button* aumentaProbabilitaButton = createOpButton(":/icons/aumentaProbabilita.png", tr("Aumenta\nProbabilita"), SLOT(aumentaProbabilitaClicked()));;
        Button* riparaButton = createOpButton(":/icons/ripara.png", tr("Ripara"), SLOT(riparaClicked()));;

        //creazione pulsanti gestione memoria
        Button*backspaceButton=new Button(tr("Backspace"), ":/icons/backspace.png");
        connect(backspaceButton, SIGNAL(clicked()), this, SLOT(backspaceClicked()));
        connect(this, SIGNAL(backspaceToClick(bool)), backspaceButton, SLOT(setEnabled(bool)));

        Button*eraseButton=new Button(tr("Cancella\nMemoria"),":/icons/cancella.png");
        connect(eraseButton, SIGNAL(clicked()), this, SLOT(eraseClicked()));
        connect(this, SIGNAL(eraseToClick(bool)), eraseButton, SLOT(setEnabled(bool)));

        Button*confermaOpButton=new Button(tr("Conferma\nOperazione"),":/icons/confermaOp.png");
        connect(confermaOpButton, SIGNAL(clicked()), this, SLOT(confirmOpClicked()));
        connect(this, SIGNAL(confirmOpToClick(bool)), confermaOpButton, SLOT(setEnabled(bool)));

        backspaceButton->setDisabled();
        eraseButton->setDisabled();
        confermaOpButton->setDisabled();

        //creazione del layout
        QGridLayout *objectLayout = new QGridLayout;
        QGridLayout *operationLayout = new QGridLayout;
        QGridLayout *memoryLayout = new QGridLayout;

        //display calcolatrice
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
        operationLayout->addWidget(combinaButton, 0, 2);
        operationLayout->addWidget(estraiButton, 1, 0);
        operationLayout->addWidget(potenziaButton, 1, 1);
        operationLayout->addWidget(trasformaButton, 1, 2);
        operationLayout->addWidget(distribuisciButton, 2, 0);
        operationLayout->addWidget(aumentaProbabilitaButton, 2, 1);
        operationLayout->addWidget(riparaButton, 2, 2);

        memoryLayout->addWidget(backspaceButton, 0,0);
        memoryLayout->addWidget(eraseButton,1,0);
        memoryLayout->addWidget(confermaOpButton, 2, 0);

        mainLayout->addLayout(objectLayout, 0, 0);
        mainLayout->addLayout(operationLayout, 0, 2);
        mainLayout->addLayout(memoryLayout, 0, 3);
        mainLayout->addWidget(display, 0, 1);

        setLayout(mainLayout); //this->setLayout(mainLayout), dove this è kalk del main, tipo KalkRpg, derivato da QWidget

        //connects per la gestione dei pulsanti della view
        connect(controller, SIGNAL(nothingToDelete()), eraseButton, SLOT(setDisabled()));
        connect(controller, SIGNAL(nothingToDelete()), backspaceButton, SLOT(setDisabled()));
    }

    ~KalkRpg() {
        delete child;
        delete mainLayout;
        delete controller;
        delete expansionAndSetGrid;
        delete display;
        delete confirmObj;
    }
    void removeSettingPanel() { //nasconde pannello di settaggio. Fa il flush del controller. DA METTERE IN PRIVATE
        expansionAndSetGrid->parentWidget()->hide();
        this->adjustSize();
        expansionAndSetGrid->deleteLater();
        child->deleteLater();
        confirmObj->deleteLater();
        controller->flushControllerMemory();
    }
    void showResult() { //DA METTERE IN PRIVATE
        if(controller->getNumObjInMemory()) {
            display->show(controller->getResultImage(), controller->getResultParametri());
        }
    }

public slots: //BISOGNA VALUTARE CHI MANDARE IN PRIVATE SLOTS
    //SELECTING OBJECTS
    void erbaClicked() {
        controller->newErba();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void unguentoClicked(){

    }
    void pietraClicked(){

    }
    void cristalloClicked() {

    }
    void ossoClicked() {

    }
    void amuletoClicked() {
        controller->newAmuleto();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }

    //SETTING OBJECTS
    void showToSet(Button* pressedButton) {
        settingObj=true;
        settingObjState(); //GOTO

        child=new QWidget(this);
        expansionAndSetGrid=new QGridLayout(child);

        QLabel *image = new QLabel();
        image->setAlignment(Qt::AlignCenter);
        QPixmap *pix = new QPixmap(pressedButton->getPath());
        image->setPixmap(*pix);

        mainLayout->addWidget(child, 1, 0, 1, 3 );

        controller->showSelectedObject(expansionAndSetGrid);
        controller->setImage(new QImage(pressedButton->getPath()));

        expansionAndSetGrid->addWidget(image, 0, 0, 1, expansionAndSetGrid->columnCount());
        confirmObj=new QPushButton(tr("Conferma"), child);
        confirmObj->setFixedSize(200,50);

        expansionAndSetGrid->addWidget(confirmObj, expansionAndSetGrid->rowCount(), 0, 1, expansionAndSetGrid->columnCount(), Qt::AlignCenter);
        connect(confirmObj, SIGNAL(clicked()), this, SLOT(confirmObjClicked()));

    }

    //CONFIRM OBJECT
    void confirmObjClicked(/*Button* pressedButton*/) {
        settingObj=false;
        if(!waitingOperand)
            objIsCreatedState();
        else {
            confirmOpToClickState();
            waitingOperand=false;
        }
        display->show(controller->getImage(), controller->getParametri());
        controller->setStatsOnObj();
        removeSettingPanel();
    }


    //OPERATION CLICKED
    void creaClicked() {
        return;
    }

    void riciclaClicked() {
        return;
    }
    void combinaClicked() {
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
    void estraiClicked() {
        return;
    }
    void potenziaClicked() {
        return;
    }
    void trasformaClicked(){
        return;
    }
    void distribuisciClicked(){
        return;
    }
    void aumentaProbabilitaClicked(){
        return;
    }
    void riparaClicked(){
        return;
    }

    //GENERALS & MEMORY MANAGEMENT.
    void objectClicked() {
    }

    void confirmOpClicked() {
        opButton->setEnabled();
        opButton->animateClick();
        display->show(qobject_cast<Button*>(sender())->getPath());
        //running=false;
        doneState();
    }
    void operationClicked() {
        if(running) {
            opButton=qobject_cast<Button*>(sender());
            display->show(opButton->getPath());
            //opChoosenState();
            objIsCreatedState();
        }
    }
    void backspaceClicked() {
        if(settingObj) { //pressing back in first settingObject
            settingObj=false;
            removeSettingPanel();
            controller->deleteLastObj();
        } else
        if(!waitingOperand && running) { //in CONFIRM STATE
            display->back();
            waitingOperand=true;
            if(controller->getNumObjInMemory()) controller->deleteLastObj();
        } else
        if(waitingOperand && running) { //just choosen op, want to change it
            display->back();
            waitingOperand=false;
            running=false;
        }
        else {
            display->back();
            if(controller->getNumObjInMemory()) controller->deleteLastObj();
        }
        return objIsCreatedState();
    }
    void eraseClicked() {
        if(controller->getNumObjInMemory()) {
            waitingOperand=false;
            running=false;
            if(settingObj) { //se clicco erase mentre sto settando oggetti
                removeSettingPanel();
                settingObj=false;
            }
            controller->clearMemory();
        }
        //opHasBeenDone=false;
        objIsCreatedState();
        display->clear();
    }

//AUTOMA STATES: --------------------------------------------------------------
    void settingObjState() {
        emit objToClick(false);
        emit opToClick(false);
        emit confirmOpToClick(false);
        emit backspaceToClick(true);
        emit eraseToClick(true);
    }
    void objIsCreatedState() {
        emit objToClick(true);
        if(waitingOperand)
            emit opToClick(false);
        else emit opToClick(true);
        emit confirmOpToClick(false);
        emit backspaceToClick(true);
        if(controller->getNumObjInMemory()) emit eraseToClick(true);
        else emit eraseToClick(false);
    }
    void confirmOpToClickState() {
        objToClick(false);
        opToClick(false);
        confirmOpToClick(true);
        backspaceToClick(true);
        eraseToClick(true);
    }

    /*void startState() {
        emit objToClick(true);
        if(opHasBeenDone) {
            emit backspaceToClick(false);
            emit opToClick(true);
        }
        else {
            emit opToClick(false);
            emit backspaceToClick(true);
        }
        emit confirmOpToClick(false);

        if(controller->getNumObjInMemory())
            emit eraseToClick(true);
        else emit eraseToClick(false);
    }*/


    /*void opChoosenState() {
        emit objToClick(true);
        emit opToClick(false);
        emit confirmOpToClick(false);
        emit backspaceToClick(true);
        emit eraseToClick(true);
    }*/
    void doneState() {
        emit objToClick(false);
        emit opToClick(false);
        emit confirmOpToClick(false);
        emit backspaceToClick(false);
        emit eraseToClick(true);
    }


signals:
    void confirmObjToClick(bool);
    void confirmOpToClick(bool);
    void opToClick(bool);
    void objToClick(bool);
    void backspaceToClick(bool);
    void eraseToClick(bool);

    void anotherObjNeeded();


    //eventi di display


    //eventi relativi alla gestione
    /*void confermaClicked();
    void indietroClicked();
    void esciClicked();
    void clearDisplayClicked();*/
};

#endif // KALKRPG_H
