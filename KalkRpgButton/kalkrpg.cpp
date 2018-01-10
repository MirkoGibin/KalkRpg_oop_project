#include<QGridLayout>
#include "kalkrpg.h"

KalkRpg::KalkRpg(QWidget *parent) : QWidget(parent) {
    //creazione pulsanti
    Button* erbaButton = createButton(QIcon(":/icons/erba.png"), tr("Erba"), SLOT(erbaClicked()));
    Button* unguentoButton = createButton(QIcon(":/icons/erba.png"), tr("Unguento"), SLOT(unguentoClicked()));
    Button* pietraButton = createButton(QIcon(":/icons/erba.png"), tr("Pietra"), SLOT(pietraClicked()));
    Button* cristalloButton = createButton(QIcon(":/icons/erba.png"), tr("Cristallo"), SLOT(cristalloClicked()));
    Button* ossoButton = createButton(QIcon(":/icons/erba.png"), tr("Osso"), SLOT(ossoClicked()));
    Button* amuletoButton = createButton(QIcon(":/icons/erba.png"), tr("Amuleto"), SLOT(amuletoClicked()));

    //creazione display
    //display->setMaxLength(15);

    //creazione del layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(erbaButton, 0, 0);
    mainLayout->addWidget(unguentoButton, 0, 1);
    mainLayout->addWidget(pietraButton, 1, 0);
    mainLayout->addWidget(cristalloButton, 1, 1);
    mainLayout->addWidget(ossoButton, 2, 0);
    mainLayout->addWidget(amuletoButton, 2, 1);

    setLayout(mainLayout);
    setWindowTitle("KalkRPG");
}

Button* KalkRpg::createButton(const QIcon &icona, const QString &testo, const char *member) {
    Button *button = new Button(icona, testo);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
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
void KalkRpg::distribuzioneClicked(){
    return;
}
void KalkRpg::aumentaProbabilitaClicked(){
    return;
}
void KalkRpg::curaOggettoClicked(){
    return;
}


