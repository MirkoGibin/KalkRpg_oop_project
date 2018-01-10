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
    explicit Button(const QIcon &icona, const QString &testo, QWidget *parent = 0);

    QSize sizeHint() const override;
};

#endif // BUTTON_H
