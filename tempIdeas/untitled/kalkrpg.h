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

class KalkRpg : public QWidget {
    Q_OBJECT
private:
    Button* createObjButton(const char *path, const QString &testo, const char* member) {
        Button *button = new Button(path, testo);
        connect(button, SIGNAL(clicked()), this, member);
        connect(button,SIGNAL(clicked()),this,SLOT(showOndisplay()));
        connect(button, SIGNAL(clicked(bool)), this,SLOT(objectClicked()));
        connect(this, SIGNAL(objToClick(bool)),button, SLOT(setEnabled(bool)));
        return button;
    }
    Button* createOpButton(const char *path, const QString &testo, const char* member) {
        Button *button = new Button(path, testo);
        connect(button, SIGNAL(clicked()), this, member);
        connect(button, SIGNAL(clicked(bool)), this,SLOT(operationClicked()));
        connect(this, SIGNAL(opToClick(bool)),button, SLOT(setEnabled(bool)));
        return button;
    }

    QWidget*parent;
    QWidget*child;

    QGridLayout *mainLayout;
    Controller* controller;

    QGridLayout* expansionAndSetGrid;
    QPushButton*confirm;

public:
    KalkRpg(QWidget *parent = 0, Controller* controller_ =0) : QWidget(parent), controller(controller_) {

        setWindowTitle("KalkRPG");

        //creazione pulsanti oggetti
        Button* erbaButton = createObjButton(":/icons/erba.png", tr("Erba"), SLOT(erbaClicked()));
        Button* unguentoButton = createObjButton(":/icons/unguento.png", tr("Unguento"), SLOT(unguentoClicked()));
        Button* pietraButton = createObjButton(":/icons/pietra.png", tr("Pietra"), SLOT(pietraClicked()));
        Button* cristalloButton = createObjButton(":/icons/cristallo.png", tr("Cristallo"), SLOT(cristalloClicked()));
        Button* ossoButton = createObjButton(":/icons/osso.png", tr("Osso"), SLOT(ossoClicked()));
        Button* amuletoButton = createObjButton(":/icons/amuleto.png", tr("Amuleto"), SLOT(amuletoClicked()));

        //creazione pulsanti operazioni
        Button* creaButton = createOpButton(":/icons/crea.png", tr("Crea"), SLOT(creaClicked()));
        Button* riciclaButton = createOpButton(":/icons/ricicla.png", tr("Ricicla"), SLOT(riciclaClicked()));
        Button* combinaButton = createOpButton(":/icons/combina.png", tr("Combina"), SLOT(combinaClicked()));
        Button* estraiButton = createOpButton(":/icons/estrai.png", tr("Estrai"), SLOT(estraiClicked()));
        Button* potenziaButton = createOpButton(":/icons/potenzia.png", tr("Potenzia"), SLOT(potenziaClicked()));
        Button* trasformaButton = createOpButton(":/icons/trasforma.png", tr("Trasforma"), SLOT(trasformaClicked()));
        Button* distribuisciButton = createOpButton(":/icons/distribuisci.png", tr("Distribuisci"), SLOT(distribuisciClicked()));;
        Button* aumentaProbabilitaButton = createOpButton(":/icons/aumentaProbabilita.png", tr("Aumenta Probabilita"), SLOT(aumentaProbabilitaClicked()));;
        Button* riparaButton = createOpButton(":/icons/ripara.png", tr("Ripara"), SLOT(riparaClicked()));;

        //creazione del layout
        mainLayout = new QGridLayout(); //è campo privato

        QGridLayout *objectLayout = new QGridLayout;
        QGridLayout *operationLayout = new QGridLayout;

        //display calcolatrice
        QTextEdit* display = new QTextEdit();
        display->setReadOnly(true);

        objectLayout->setSizeConstraint(QLayout::SetFixedSize);
        operationLayout->setSizeConstraint(QLayout::SetFixedSize);

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

        mainLayout->addLayout(objectLayout, 0, 0);
        mainLayout->addLayout(operationLayout, 0, 2);
        mainLayout->addWidget(display, 0, 1);

        setLayout(mainLayout); //this->setLayout(mainLayout), dove this è kalk del main, tipo KalkRpg, derivato da QWidget

    }
private slots:
    void showToSet(Button* pressedButton) {
        pressedButton=qobject_cast<Button*>(sender());

        child=new QWidget(this);
        expansionAndSetGrid=new QGridLayout(child);

        QLabel *image = new QLabel();
        image->setAlignment(Qt::AlignCenter);
        QPixmap *pix = new QPixmap(pressedButton->getPath());
        pix->
        image->setPixmap(*pix);

        mainLayout->addWidget(child, 1, 0, 1, 3 );

        controller->showSelectedObject(expansionAndSetGrid, pressedButton);

        expansionAndSetGrid->addWidget(image, 0, 0, 1, expansionAndSetGrid->columnCount());
        confirm=new QPushButton(tr("Conferma"),child);
        confirm->setFixedSize(200,50);

        expansionAndSetGrid->addWidget(confirm, expansionAndSetGrid->rowCount(), 0, 1, expansionAndSetGrid->columnCount(), Qt::AlignCenter);

        connect(confirm, SIGNAL(clicked()), this, SLOT(confirmClicked()));

    }
    void confirmClicked() {
        //delete expansionAndSetGrid;
        //mainLayout->removeItem(expansionAndSetGrid->itemAtPosition(1,1));
        //mainLayout->removeItem(expansionAndSetGrid);
        //qui bisognerebbe invocare il showToDisplay
        controller->setStatsOnObj();

        expansionAndSetGrid->parentWidget()->hide();
        this->adjustSize();
        //delete expansionAndSetGrid;
        //delete child;
        expansionAndSetGrid->deleteLater();
        child->deleteLater();
        confirm->deleteLater();
        controller->flushControllerMemory();
        emit opToClick(true);
    }

    void objectClicked() {
        emit objToClick(false);
    }
    void operationClicked() {
        emit opToClick(false);
        emit objToClick(true);
    }

    //eventi relativi agli oggetti
    void erbaClicked() {
        emit opToClick(false);
        controller->newErba();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void unguentoClicked(){
        emit opToClick(false);
        controller->newUnguento();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void pietraClicked(){
        emit opToClick(false);
        controller->newPietra();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void cristalloClicked() {
        emit opToClick(false);
        controller->newCristallo();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void ossoClicked() {
        emit opToClick(false);
        controller->newOsso();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }
    void amuletoClicked() {
        emit opToClick(false);
        controller->newAmuleto();
        showToSet(qobject_cast<Button*>(sender()));
        return;
    }

    //eventi relativi alle operazioni
    void creaClicked() {return;}


    void riciclaClicked() {
        child=new QWidget(this);
        expansionAndSetGrid=new QGridLayout(child);
        mainLayout->addWidget(child);
        int mana=controller->ricicla();
        QLCDNumber*risultato=new QLCDNumber(3);
        risultato->display(mana);
        expansionAndSetGrid->addWidget(risultato);
        //return;
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


    void showOndisplay() {
        QString nome = sender()->objectName();
        Button* button = findChild<Button*>(nome);
        QTextEdit* display = findChild<QTextEdit*>();
        QTextCursor cursor = display->textCursor();
        cursor.setPosition(0);
        QTextTable* table = cursor.insertTable(1,3);
        table->cellAt(0, 0).firstCursorPosition().insertImage(QImage(button->getPath()));
        for(int j=1; j<3; j++) {
            table->cellAt(0, j).firstCursorPosition().insertText("Attacco \n 120");
        }

    }

signals:
    void opToClick(bool);
    void objToClick(bool);
    //eventi di display


    //eventi relativi alla gestione
    /*void confermaClicked();
    void indietroClicked();
    void esciClicked();
    void clearDisplayClicked();*/
};

#endif // KALKRPG_H
