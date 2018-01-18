#ifndef KALKRPG_H
#define KALKRPG_H
#include <QGridLayout>
#include <QMap>
#include "button.h"

class KalkRpg : public QWidget {
    Q_OBJECT
private:
    QGridLayout* mainLayout;
    Button* createButton(const char *path, const QString &testo, const char* member);
    void abortOperation();
    bool esegui();

public:
    KalkRpg(QWidget *parent = 0);
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
    void aggiungiMerda();

    //eventi relativi alla gestione
    /*void confermaClicked();
    void indietroClicked();
    void esciClicked();
    void clearDisplayClicked();*/
};

#endif // KALKRPG_H
