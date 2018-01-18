#ifndef BUTTON_H
#define BUTTON_H
#include <QSize>
#include <QIcon>
#include <QWidget>
#include <QToolButton>
#include <QObject>

class Button : public QToolButton {
    Q_OBJECT

private:
    const QString testo;
    const QIcon icona;
public:

    explicit Button(const QIcon &icona_, const QString &testo_ =0, QWidget *parent = 0) : QToolButton(parent), testo(testo_), icona(icona_) {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        setIcon(icona);
        setText(testo);
    }

    QSize sizeHint() const override {
        QSize size = QToolButton::sizeHint();
        size.rheight() += 20;
        size.rwidth() = qMax(size.width(), size.height());
        return size;
    }
    QString getTesto() const {return testo;}
    QIcon getIcona() const {return icona;}
public slots:
    void setEnabled() {
        this->QToolButton::setEnabled(true);
    }
    void setDisabled() {
        this->QToolButton::setDisabled(true);
    }
signals:


};

#endif // BUTTON_H

