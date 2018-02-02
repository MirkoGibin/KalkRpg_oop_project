#ifndef DISPLAYANDSLIDER_H
#define DISPLAYANDSLIDER_H
#include<QWidget>
#include<QLCDNumber>
#include<QSlider>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QGridLayout>
#include<QLineEdit>
#include<QIntValidator>
#include<QLabel>

class DisplayAndSlider : public QWidget {
Q_OBJECT
private:
    QSlider* slider;
    QLabel* descrizione;
    QLineEdit* valore;

public:
        DisplayAndSlider(QWidget*parent =0, const QString& descrizione_ =0, bool forMana =false) :
        QWidget(parent), slider(new QSlider(Qt::Horizontal)), descrizione(new QLabel(descrizione_)), valore(new QLineEdit()) {

        descrizione->setAlignment(Qt::AlignCenter);

        QVBoxLayout* displayandslider=new QVBoxLayout;
        slider->setValue(1);

        if(descrizione->text()=="Livello" || descrizione->text()=="Rarità") {
            valore->setText(QString::number(1));
            slider->setRange(1,10);
            valore->setValidator(new QIntValidator(1,10));
        }
        else if(forMana) {
            valore->setText(QString::number(1));
            slider->setRange(1,6000);
            valore->setValidator(new QIntValidator(1,6000));
        }
        else {
            slider->setRange(1,150);
            valore->setText(QString::number(1));
            valore->setValidator(new QIntValidator(1,150));
        }
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(display(int)));
        connect(valore, SIGNAL(textChanged(QString)), this, SLOT(updateSlider(QString)));
        connect(this, SIGNAL(fromDisplay(int)), slider, SLOT(setValue(int)));
        connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));


        displayandslider->addWidget(valore);
        displayandslider->addWidget(slider);
        displayandslider->addWidget(descrizione);
        setLayout(displayandslider);
    }
    ~DisplayAndSlider() {
        delete slider;
    }

    QSlider* getSlider() const {
        return slider;
    }

public slots:

    void display(int n) {
        QString numero = QString::number(n);
        valore->setText(numero);
    }
    int value() const {
        return slider->value();
    }
    void setValue(int value) {
        slider->setValue(value);
    }

    void updateSlider(QString s) {
        slider->setValue(s.toInt());
    }


signals:
    void valueChanged(int newValue);
    void fromDisplay(int);
};

#endif // DISPLAYANDSLIDER_H
