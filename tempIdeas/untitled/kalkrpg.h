#ifndef KALKRPG_H
#define KALKRPG_H
#include<QGridLayout>
#include "button.h"
#include"controller.h"

class KalkRpg : public QWidget {
    Q_OBJECT
private:
    Button* createButton(const QIcon &icona, const QString &testo, const char* member);
    void abortOperation();
    bool esegui();
    QGridLayout *mainLayout;
    Controller* controller;
    bool waitingForOperand;

public:
    KalkRpg(QWidget *parent = 0, Controller* controller =0);

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
    void riparaClicked();

    //eventi relativi alla gestione
    /*void confermaClicked();
    void indietroClicked();
    void esciClicked();
    void clearDisplayClicked();*/

};

#endif // KALKRPG_H
