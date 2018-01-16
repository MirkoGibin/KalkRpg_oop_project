#ifndef BUTTON_H
#define BUTTON_H
#include <QSize>
#include <QIcon>
#include <QWidget>
#include <QToolButton>
#include <QObject>

class Button : public QToolButton {
    Q_OBJECT
public:
    explicit Button(const QIcon &icona, const QString &testo_ =0, QWidget *parent = 0) : QToolButton(parent), testo(testo_) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
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
private:
    const QString testo;
};

#endif // BUTTON_H

