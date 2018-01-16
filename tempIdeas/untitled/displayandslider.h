#ifndef DISPLAYANDSLIDER_H
#define DISPLAYANDSLIDER_H
#include<QWidget>
#include<QLCDNumber>
#include<QSlider>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QGridLayout>

class DisplayAndSlider : public QWidget {
Q_OBJECT
private:
    QSlider* slider;
    const QString descrizione;

public:
    DisplayAndSlider(QWidget*parent =0,const QString& descrizione_ =0) :
        QWidget(parent), descrizione(descrizione_), slider(new QSlider(Qt::Horizontal)) {
        QLCDNumber *lcd=new QLCDNumber(3);
        lcd->setSegmentStyle(QLCDNumber::Filled);
        slider->setRange(0,99); slider->setValue(0);
        QLineEdit* descr=new QLineEdit(descrizione);
        QVBoxLayout* displayandslider=new QVBoxLayout;
        connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
        connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
        displayandslider->addWidget(lcd);
        displayandslider->addWidget(slider);
        displayandslider->addWidget(descr);
        setLayout(displayandslider);
        //grigliaP->addLayout(displayandslider,0,0);
    }
    int value() const {
        return slider->value();
    }
public slots:
    void setValue(int value) {
        slider->setValue(value);
    }

signals:
    void valueChanged(int newValue);
};

#endif // DISPLAYANDSLIDER_H
