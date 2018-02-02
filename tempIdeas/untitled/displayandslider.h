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
    DisplayAndSlider(QWidget* =0, const QString& =0, bool =false);
    ~DisplayAndSlider();

    QSlider* getSlider() const;

private slots:
    void updateSlider(QString);
    void display(int);
    void setValue(int);

public slots:
    int value() const;

signals:
    void valueChanged(int);
    void fromDisplay(int);
};

#endif // DISPLAYANDSLIDER_H
