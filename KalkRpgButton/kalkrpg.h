#ifndef KALKRPG_H
#define KALKRPG_H
#include <QGridLayout>
#include <QMap>
#include "button.h"

class KalkRpg : public QWidget {
    Q_OBJECT
private:
    QGridLayout* mainLayout;
    Button* createButton(const char *path, const QString &testo, const char* member) {
        Button *button = new Button(path, testo);
        connect(button, SIGNAL(clicked()), this, member);
        //if()
        connect(button,SIGNAL(clicked()),this,SLOT(aggiungiMerda()));
        return button;
    }
    void abortOperation();
    bool esegui();

public:
    KalkRpg(QWidget *parent = 0) : QWidget(parent) {

        setWindowTitle("KalkRPG");

        //creazione pulsanti oggetti
        Button* erbaButton = createButton(":/icons/erba.png", tr("Erba"), SLOT(erbaClicked()));
        Button* unguentoButton = createButton(":/icons/unguento.png", tr("Unguento"), SLOT(unguentoClicked()));
        Button* pietraButton = createButton(":/icons/pietra.png", tr("Pietra"), SLOT(pietraClicked()));
        Button* cristalloButton = createButton(":/icons/cristallo.png", tr("Cristallo"), SLOT(cristalloClicked()));
        Button* ossoButton = createButton(":/icons/osso.png", tr("Osso"), SLOT(ossoClicked()));
        Button* amuletoButton = createButton(":/icons/amuleto.png", tr("Amuleto"), SLOT(amuletoClicked()));

        //creazione pulsanti operazioni
        Button* creaButton = createButton(":/icons/crea.png", tr("Crea"), SLOT(creaClicked()));
        Button* riciclaButton = createButton(":/icons/ricicla.png", tr("Ricicla"), SLOT(riciclaClicked()));
        Button* combinaButton = createButton(":/icons/combina.png", tr("Combina"), SLOT(combinaClicked()));
        Button* estraiButton = createButton(":/icons/estrai.png", tr("Estrai"), SLOT(estraiClicked()));
        Button* potenziaButton = createButton(":/icons/potenzia.png", tr("Potenzia"), SLOT(potenziaClicked()));
        Button* trasformaButton = createButton(":/icons/trasforma.png", tr("Trasforma"), SLOT(trasformaClicked()));
        Button* distribuisciButton = createButton(":/icons/distribuisci.png", tr("Distribuisci"), SLOT(distribuisciClicked()));;
        Button* aumentaProbabilitaButton = createButton(":/icons/aumentaProbabilita.png", tr("Aumenta Probabilita"), SLOT(aumentaProbabilitaClicked()));;
        Button* curaOggettoButton = createButton(":/icons/ripara.png", tr("Cura Oggetto"), SLOT(curaOggettoClicked()));;

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
        operationLayout->addWidget(curaOggettoButton, 2, 2);

        mainLayout->addLayout(objectLayout, 0, 0);
        mainLayout->addLayout(operationLayout, 0, 2);
        mainLayout->addWidget(display, 0, 1);

        setLayout(mainLayout); //this->setLayout(mainLayout), dove this è kalk del main, tipo KalkRpg, derivato da QWidget

    }
    ~KalkRpg();

private slots:
    //eventi relativi agli oggetti
    void erbaClicked();
    void unguentoClicked();
    void pietraClicked();
    void cristalloClicked();
    void ossoClicked();
    void amuletoClicked();

    //eventi relativi alle operazioni
    void creaClicked();
    void riciclaClicked();
    void combinaClicked();
    void estraiClicked();
    void potenziaClicked();
    void trasformaClicked();
    void distribuisciClicked();
    void aumentaProbabilitaClicked();
    void curaOggettoClicked();

    //eventi di display
    void aggiungiMerda() {
        QString nome = sender()->objectName();
        Button* button = findChild<Button*>(nome);
        QTextEdit* display = findChild<QTextEdit*>();
        QTextCursor cursor = display->textCursor();
        QTextTable* table = cursor.insertTable(1,3);
        table->cellAt(0, 0).firstCursorPosition().insertImage(QImage(button->getPath()));
        for(int j=1; j<3; j++) {
            table->cellAt(0, j).firstCursorPosition().insertText("Attacco \n 120");
        }

    }

    //eventi relativi alla gestione
    /*void confermaClicked();
    void indietroClicked();
    void esciClicked();
    void clearDisplayClicked();*/
};

#endif // KALKRPG_H
