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
    const QString descrizione;
    QLineEdit* valore;

public:
        DisplayAndSlider(QWidget*parent =0,const QString& descrizione_ =0) :
        QWidget(parent), slider(new QSlider(Qt::Horizontal)), descrizione(descrizione_) {

        //QLCDNumber *lcd=new QLCDNumber(3);
        valore = new QLineEdit();

        //lcd->setSegmentStyle(QLCDNumber::Filled);

        QLabel* descr = new QLabel(descrizione);
        descr->setAlignment(Qt::AlignCenter);

        QVBoxLayout* displayandslider=new QVBoxLayout;
        slider->setValue(0);

        if(descrizione=="Livello" || descrizione=="Rarità") {
            slider->setValue(1);
            slider->setRange(1,10);
            valore->setValidator(new QIntValidator(1,10));
        }
        else {
            slider->setRange(0,199);
            valore->setValidator(new QIntValidator(0,199));
        }
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(display(int)));
        connect(valore, SIGNAL(textChanged(QString)), this, SLOT(updateSlider(QString)));
        connect(this, SIGNAL(fromDisplay(int)), slider, SLOT(setValue(int)));
        connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));


        displayandslider->addWidget(valore);
        displayandslider->addWidget(slider);
        displayandslider->addWidget(descr);
        setLayout(displayandslider);
        //grigliaP->addLayout(displayandslider,0,0);
    }
    ~DisplayAndSlider() {
        delete slider;
    }

    QSlider* getSlider() const {
        return slider;
    }

public slots:

    void display(int n) {
        QString x = QString::number(n);
        valore->setText(x);
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
