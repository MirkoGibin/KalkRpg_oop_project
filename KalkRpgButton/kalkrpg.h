#ifndef KALKRPG_H
#define KALKRPG_H
#include "button.h"

class KalkRpg : public QWidget {
    Q_OBJECT

public:
    KalkRpg(QWidget *parent = 0);

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
    void distribuzioneClicked();
    void aumentaProbabilitaClicked();
    void curaOggettoClicked();

    //eventi relativi alla gestione
    /*void confermaClicked();
    void indietroClicked();
    void esciClicked();
    void clearDisplayClicked();*/

private:
    Button* createButton(const QIcon &icona, const QString &testo, const char* member);
    void abortOperation();
    bool esegui();


};

#endif // KALKRPG_H
