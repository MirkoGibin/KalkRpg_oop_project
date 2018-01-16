#include<QGridLayout>
#include "kalkrpg.h"
#include<map>
using std::map;

KalkRpg::KalkRpg(QWidget *parent) : QWidget(parent) {
    //creazione pulsanti oggetti
    Button* erbaButton = createButton(QIcon(":/icons/erba.png"), tr("Erba"), SLOT(erbaClicked()));
    Button* unguentoButton = createButton(QIcon(":/icons/unguento.png"), tr("Unguento"), SLOT(unguentoClicked()));
    Button* pietraButton = createButton(QIcon(":/icons/pietra.png"), tr("Pietra"), SLOT(pietraClicked()));
    Button* cristalloButton = createButton(QIcon(":/icons/cristallo.png"), tr("Cristallo"), SLOT(cristalloClicked()));
    Button* ossoButton = createButton(QIcon(":/icons/osso.png"), tr("Osso"), SLOT(ossoClicked()));
    Button* amuletoButton = createButton(QIcon(":/icons/amuleto.png"), tr("Amuleto"), SLOT(amuletoClicked()));

    //creazione pulsanti operazioni
    Button* creaButton = createButton(QIcon(":/icons/crea.png"), tr("Crea"), SLOT(creaClicked()));
    Button* riciclaButton = createButton(QIcon(":/icons/ricicla.png"), tr("Ricicla"), SLOT(riciclaClicked()));
    Button* combinaButton = createButton(QIcon(":/icons/combina.png"), tr("Combina"), SLOT(combinaClicked()));
    Button* estraiButton = createButton(QIcon(":/icons/estrai.png"), tr("Estrai"), SLOT(estraiClicked()));
    Button* potenziaButton = createButton(QIcon(":/icons/potenzia.png"), tr("Potenzia"), SLOT(potenziaClicked()));
    Button* trasformaButton = createButton(QIcon(":/icons/trasforma.png"), tr("Trasforma"), SLOT(trasformaClicked()));
    Button* distribuisciButton = createButton(QIcon(":/icons/distribuisci.png"), tr("Distribuisci"), SLOT(distribuisciClicked()));;
    Button* aumentaProbabilitaButton = createButton(QIcon(":/icons/aumentaProbabilita.png"), tr("Aumenta Probabilita"), SLOT(aumentaProbabilitaClicked()));;
    Button* curaOggettoButton = createButton(QIcon(":/icons/curaOggetto.png"), tr("Cura Oggetto"), SLOT(curaOggettoClicked()));;

    //creazione display
    //display->setMaxLength(15);

    //creazione del layout
    QGridLayout *objectLayout = new QGridLayout;
    QGridLayout *operationLayout = new QGridLayout;
    mainLayout = new QGridLayout;

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


    setLayout(mainLayout);
    setWindowTitle("KalkRPG");
}

Button* KalkRpg::createButton(const QIcon &icona, const QString &testo, const char *member) {
    Button *button = new Button(icona, testo);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void KalkRpg::erbaClicked() {

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


