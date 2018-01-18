#include<QGridLayout>
#include "kalkrpg.h"
#include<QTextEdit>
#include <QTextDocumentFragment>
#include<QTextCursor>



KalkRpg::KalkRpg(QWidget *parent) : QWidget(parent) {

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

Button* KalkRpg::createButton(const char *path, const QString &testo, const char *member) {
    Button *button = new Button(path, testo);
    connect(button, SIGNAL(clicked()), this, member);
    connect(button,SIGNAL(clicked()),this,SLOT(aggiungiMerda()));
    return button;
}

void KalkRpg::aggiungiMerda() {
    QString nome = sender()->objectName();
    Button* button = findChild<Button*>(nome);
    QTextEdit* display = findChild<QTextEdit*>();
    QTextCursor cursor = display->textCursor();
    cursor.insertImage(QImage(button->getPath()));
    cursor.insertText("\n"+nome+"\n");
}

void KalkRpg::erbaClicked() {
    return;
}
void KalkRpg::unguentoClicked(){
    return;
}
void KalkRpg::pietraClicked(){
    return;
}
void KalkRpg::cristalloClicked() {
    return;
}
void KalkRpg::ossoClicked() {
    return;
}
void KalkRpg::amuletoClicked() {
    return;
}

//eventi relativi alle operazioni
void KalkRpg::creaClicked() {
    return;
}
void KalkRpg::riciclaClicked() {
    return;
}
void KalkRpg::combinaClicked() {
    return;
}
void KalkRpg::estraiClicked() {
    return;
}
void KalkRpg::potenziaClicked() {
    return;
}
void KalkRpg::trasformaClicked(){
    return;
}
void KalkRpg::distribuisciClicked(){
    return;
}
void KalkRpg::aumentaProbabilitaClicked(){
    return;
}
void KalkRpg::curaOggettoClicked(){
    return;
}


