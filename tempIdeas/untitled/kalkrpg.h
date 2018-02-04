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

    bool riciclaOp;
    bool potenziaOp;
    bool creaOp;
    bool trasformaOp;

    bool cristalloObj;
    bool unguentoObj;
    bool amuletoObj;

    Button* createObjButton(const char*, const QString&, const char*);
    Button* createOpButton(const char*, const QString&, const char*);

    void removeSettingPanel();
    void showResult(int =0, int =0);
    void showResult(QString);

    //SETTING OBJECTS
    void showToSet(Button*);

    //METODI DI SERVIZIO
    void setChildVariables();
    void setChildMethods();

public:
    KalkRpg(QWidget* =0, Controller* =0);

    ~KalkRpg();

private slots: //BISOGNA VALUTARE CHI MANDARE IN PRIVATE SLOTS
    //SLOT DI SERVIZIO
    void commonTasksForObject();

    //SELECTING OBJECTS
    void erbaClicked();
    void unguentoClicked();
    void pietraClicked();
    void cristalloClicked();
    void ossoClicked();
    void amuletoClicked();

    void objectClicked();

    //CONFIRM OBJECT
    void confirmObjClicked();

    //OPERATION CLICKED
    void creaClicked();
    void riciclaClicked();
    void combinaClicked();
    void estraiClicked();
    void potenziaClicked();
    void trasformaClicked();
    void distribuisciClicked();
    void duplicaClicked();
    void riparaClicked();

    void operationClicked();

    //GENERALS & MEMORY MANAGEMENT.
    void confirmOpClicked();

/*BackSpace ha un comportamento predefinito, che viene poi modificato a seconda dello stato, dell'operazione e dell'oggetto che si ha in memoria.
 * In particolare, possiamo notare tre stati, distinguibili a seconda del valore di settingObj, waitingOperando e running:
 * 1)   settingObj==true;
 *          Questo stato avviene quando si stanno settando le statistiche di un oggetto. L'oggetto e' gia' stato creato a default nella memoria, quindi si rende necessario
 *          doverlo eliminare e riportare settingObj a false. In questo comportamento standard si inseriscono anche:
 *              a. cristallo, unguento, amuleto: per rendere non disponibili alcune operazioni relative a solo questi oggetti, si utilizza il setChildVariables;
 *              b. potenziaOp, creaOp, che hanno bisogno di questo stato per settare i loro parametri.
 * 2)   !waitingOperand && running
 *          Questo stato avviene nel momento subito precedente alla conferma dell'operazione. Pigiare backspace in questo momento equivale al voler eliminare l'oggetto appena settato per
 *          settarne un altro, oppure cancellare l'operazione appena settata. Per questo motivo c'e' un particolare comportamento in caso di potenziaOp.
 * 3)   waitingOperand && running
 *          In questo stato ho appena scelto l'operazione che voglio eseguire. Pigiare backspace qui vuol dire cambiare idea riguardo l'operazione da effettuare, quindi non ci saranno
 *          delete in memoria, ma solo una gestione delle variabili interne alla view.
 */

    void backspaceClicked();
    void eraseClicked();

//AUTOMA STATES: --------------------------------------------------------------
    void settingObjState();
    void objIsCreatedState();
    void confirmOpToClickState();
    void doneState();

//
    void cristalloInMemory(bool);
    void unguentoInMemory(bool);
    void amuletoInMemory(bool);

signals:
    void confirmObjToClick(bool);
    void confirmOpToClick(bool);
    void opToClick(bool);
    void objToClick(bool);
    void backspaceToClick(bool);
    void eraseToClick(bool);

    void startOp(bool);

    void distribuisciToClick(bool);
    void riparaToClick(bool);
    void duplicaToClick(bool);
    void unaryOp(bool);
};

#endif // KALKRPG_H
