    #ifndef KALKRPG_H
#define KALKRPG_H
#include<QGridLayout>
#include<QPushButton>
#include "button.h"
#include"controller.h"

class KalkRpg : public QWidget {
    Q_OBJECT
private:
    Button* createButton(const QIcon &icona, const QString &testo, const char* member) {
        Button *button = new Button(icona, testo);
        connect(button, SIGNAL(clicked()), this, member);
        return button;
    }

    QWidget*parent;
    QWidget*child;

    QGridLayout *mainLayout;
    Controller* controller;

    QGridLayout* expansionAndSetGrid;

public:
    KalkRpg(QWidget *parent = 0, Controller* controller_ =0) : QWidget(parent), controller(controller_) {

        mainLayout = new QGridLayout(parent);

        //creazione pulsanti oggetto
        Button* erbaButton = createButton(QIcon(":/icons/erba.png"), tr("Erba"), SLOT(erbaClicked()));

        //creazione pulsanti operazioni
        Button* creaButton = createButton(QIcon(":/icons/crea.png"), tr("Crea"), SLOT(creaClicked()));

        //creazione display
        //display->setMaxLength(15);

        //creazione del layout
        QGridLayout *objectLayout = new QGridLayout(parent);
        QGridLayout *operationLayout = new QGridLayout(parent);

        objectLayout->setSizeConstraint(QLayout::SetFixedSize);
        operationLayout->setSizeConstraint(QLayout::SetFixedSize);

        objectLayout->addWidget(erbaButton, 0, 0);

        operationLayout->addWidget(creaButton, 0, 0);

        mainLayout->addLayout(objectLayout, 0, 0);
        mainLayout->addLayout(operationLayout, 0, 1);

        setLayout(mainLayout);
        setWindowTitle("KalkRPG");
    }

private slots:
    //eventi relativi agli oggetti
    void erbaClicked() {
        controller->newErba();

        Button * pressedButton=qobject_cast<Button*>(sender());
        pressedButton->setDisabled();

        child=new QWidget(this);

        expansionAndSetGrid=new QGridLayout(child);
        //cosa deve fare:
        //-costruire un erba
        //-retrieve stat list
        //-set stats
        //-confirm
        mainLayout->addWidget(child);

        controller->showSelectedObject(expansionAndSetGrid, pressedButton);

        QPushButton*confirm=new QPushButton(tr("Conferma"),child);

        expansionAndSetGrid->addWidget(confirm);

        //Button*button=expansionAndSetGrid->findChild<Button*>("button");

        connect(confirm, SIGNAL(clicked()), pressedButton, SLOT(setEnabled()));
        connect(confirm, SIGNAL(clicked()), this, SLOT(confirmClicked()));


        //mainLayout->removeWidget(confirm);
        //mainLayout->setRowStretch(1,0);

        return;
    }

    //eventi relativi alle operazioni
    void creaClicked() {return;}

    void confirmClicked() {
        //delete expansionAndSetGrid;
        //mainLayout->removeItem(expansionAndSetGrid->itemAtPosition(1,1));
        //mainLayout->removeItem(expansionAndSetGrid);
        controller->setStatsOnObj();
        expansionAndSetGrid->parentWidget()->hide();
        this->adjustSize();
        delete expansionAndSetGrid;
        delete child;
        controller->flushControllerMemory();
    }

};

#endif // KALKRPG_H
