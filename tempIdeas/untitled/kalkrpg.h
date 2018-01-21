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
    QPushButton* confirm;
    Display* display;

    Button* createObjButton(const char *path, const QString &testo, const char* member) {
        Button *button = new Button(testo, path);
        connect(button, SIGNAL(clicked()), this, member);
        connect(button, SIGNAL(clicked(bool)), this,SLOT(objectClicked()));
        connect(this, SIGNAL(objToClick(bool)),button, SLOT(setEnabled(bool)));
        return button;
    }

    Button* createBinButton(const char *path, const QString &testo, const char* member) {
        Button *button = new Button(testo, path);
        connect(button, SIGNAL(clicked()), this, member);
        button->setDisabled();
        connect(button, SIGNAL(clicked(bool)), this,SLOT(unaOpClicked()));
        connect(this, SIGNAL(binToClick(bool)),button, SLOT(setEnabled(bool)));
        return button;
    }
    Button* createUnaButton(const char *path, const QString &testo, const char* member) {
        Button *button = new Button(testo, path);
        connect(button, SIGNAL(clicked()), this, member);
        connect(button, SIGNAL(clicked(bool)), this,SLOT(binOpClicked()));
        connect(this, SIGNAL(unaToClick(bool)),button, SLOT(setEnabled(bool)));
        return button;
    }


public:
    KalkRpg(QWidget *parent = 0, Controller* controller_ =0 ) : QWidget(parent), mainLayout(new QGridLayout), controller(controller_), display(new Display) {

        setWindowTitle("KalkRPG");

        //creazione pulsanti oggetti
        Button* erbaButton = createObjButton(":/icons/erba.png", tr("Erba"), SLOT(erbaClicked()));
        Button* unguentoButton = createObjButton(":/icons/unguento.png", tr("Unguento"), SLOT(unguentoClicked()));
        Button* pietraButton = createObjButton(":/icons/pietra.png", tr("Pietra"), SLOT(pietraClicked()));
        Button* cristalloButton = createObjButton(":/icons/cristallo.png", tr("Cristallo"), SLOT(cristalloClicked()));
        Button* ossoButton = createObjButton(":/icons/osso.png", tr("Osso"), SLOT(ossoClicked()));
        Button* amuletoButton = createObjButton(":/icons/amuleto.png", tr("Amuleto"), SLOT(amuletoClicked()));

        //creazione pulsanti operazioni unarie
        Button* creaButton = createUnaButton(":/icons/crea.png", tr("Crea"), SLOT(creaClicked()));
        Button* riciclaButton = createUnaButton(":/icons/ricicla.png", tr("Ricicla"), SLOT(riciclaClicked()));
        Button* potenziaButton = createUnaButton(":/icons/potenzia.png", tr("Potenzia"), SLOT(potenziaClicked()));

        //creazione pulsanti operazioni binarie
        Button* combinaButton = createBinButton(":/icons/combina.png", tr("Combina"), SLOT(combinaClicked()));
        Button* estraiButton = createBinButton(":/icons/estrai.png", tr("Estrai"), SLOT(estraiClicked()));
        Button* trasformaButton = createBinButton(":/icons/trasforma.png", tr("Trasforma"), SLOT(trasformaClicked()));
        Button* distribuisciButton = createBinButton(":/icons/distribuisci.png", tr("Distribuisci"), SLOT(distribuisciClicked()));;
        Button* aumentaProbabilitaButton = createBinButton(":/icons/aumentaProbabilita.png", tr("Aumenta Probabilita"), SLOT(aumentaProbabilitaClicked()));;
        Button* riparaButton = createBinButton(":/icons/ripara.png", tr("Ripara"), SLOT(riparaClicked()));;

        //creazione pulsanti gestione memoria
        Button*backspaceButton=new Button(tr("Backspace"), ":/icons/backspace.png");
        connect(backspaceButton, SIGNAL(clicked()), this, SLOT(backspaceClicked()));
        connect(this, SIGNAL(backspaceToClick(bool)), backspaceButton, SLOT(setEnabled(bool)));

        Button*eraseButton=new Button(tr("Cancella\nMemoria"),":/icons/cancella.png");
        connect(eraseButton, SIGNAL(clicked()), this, SLOT(eraseClicked()));
        connect(this, SIGNAL(eraseToClick(bool)), eraseButton, SLOT(setEnabled(bool)));

        backspaceButton->setDisabled();
        eraseButton->setDisabled();

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

        mainLayout->addLayout(objectLayout, 0, 0);
        mainLayout->addLayout(operationLayout, 0, 2);
        mainLayout->addLayout(memoryLayout, 0, 3);
        mainLayout->addWidget(display, 0, 1);

        setLayout(mainLayout); //this->setLayout(mainLayout), dove this è kalk del main, tipo KalkRpg, derivato da QWidget

    }

    ~KalkRpg() {
        delete child;
        delete mainLayout;
        delete controller;
        delete expansionAndSetGrid;
        delete display;
        delete confirm;
    }
private slots:
    void showToSet(Button* pressedButton) {

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
        confirm=new QPushButton(tr("Conferma"), child);
        confirm->setFixedSize(200,50);

        expansionAndSetGrid->addWidget(confirm, expansionAndSetGrid->rowCount(), 0, 1, expansionAndSetGrid->columnCount(), Qt::AlignCenter);

       // connect(confirm, SIGNAL(confirmedParameters(Button*)), this, SLOT(confirmClicked(Button* )));
        connect(confirm, SIGNAL(clicked()), this, SLOT(confirmClicked()));

    }

    void confirmClicked(/*Button* pressedButton*/) {

        display->show(controller->getImage(), controller->getParametri());

        controller->setStatsOnObj();

        expansionAndSetGrid->parentWidget()->hide();

        this->adjustSize();

        expansionAndSetGrid->deleteLater();
        child->deleteLater();
        confirm->deleteLater();

        controller->flushControllerMemory();
        emit unaToClick(true);

    }

    //eventi relativi agli oggetti
    void erbaClicked() {
        emit unaToClick(false);
        controller->newErba();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void unguentoClicked(){
        emit unaToClick(false);
        controller->newUnguento();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void pietraClicked(){
        emit unaToClick(false);
        controller->newPietra();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void cristalloClicked() {
        emit unaToClick(false);
        controller->newCristallo();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void ossoClicked() {
        emit unaToClick(false);
        controller->newOsso();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void amuletoClicked() {
        emit unaToClick(false);
        controller->newAmuleto();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }

    //eventi relativi alle operazioni
    void creaClicked() {return;}


    void riciclaClicked() {
        return;
    }
    void combinaClicked() {
        return;
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

    //SLOTS FOR MEMORY MANAGEMENT
    void objectClicked() {
        emit objToClick(false);
    }
    void unaOpClicked() {
        emit unaToClick(false);
        emit objToClick(true);
    }
    void binOpClicked() {
        emit unaToClick(false);
        emit objToClick(true);
    }
    void backspaceClicked() {
        return;
    }
    void eraseClicked() {
        return;
    }



signals:
    void unaToClick(bool);
    void binToClick(bool);
    void objToClick(bool);
    void backspaceToClick(bool);
    void eraseToClick(bool);

    //eventi di display


    //eventi relativi alla gestione
    /*void confermaClicked();
    void indietroClicked();
    void esciClicked();
    void clearDisplayClicked();*/
};

#endif // KALKRPG_H
