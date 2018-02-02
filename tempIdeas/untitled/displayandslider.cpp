#include "displayandslider.h"

DisplayAndSlider::DisplayAndSlider(QWidget *parent, const QString &descrizione_, bool forMana) :
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

DisplayAndSlider::~DisplayAndSlider() {
    delete slider;
}

QSlider *DisplayAndSlider::getSlider() const {
    return slider;
}

void DisplayAndSlider::updateSlider(QString s) {
    slider->setValue(s.toInt());
}

void DisplayAndSlider::display(int n) {
    QString numero = QString::number(n);
    valore->setText(numero);
}

void DisplayAndSlider::setValue(int value) {
    slider->setValue(value);
}

int DisplayAndSlider::value() const {
    return slider->value();
}
