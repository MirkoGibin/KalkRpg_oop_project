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
    const char* path_;
    const QString testo_;

public:
    explicit Button(const QString &testo, const char *path =0, QWidget *parent = 0) : QToolButton(parent), path_(path), testo_(testo) {

        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        if(path != 0) {
            setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            setIcon(QIcon(path));
        }
        setText(testo);
        setObjectName(testo);
    } 
    QSize sizeHint() const override {
        QSize size = QToolButton::sizeHint();
        size.rheight() += 5;
        size.rwidth() = qMax(size.width(), size.height());
        return size;
    }
    const char* getPath() const {
        return path_;
    }

    QString getTesto() const {
        return testo_;
    }

public slots:
    void setEnabled() {
        QToolButton::setEnabled(true);
    }

    void setDisabled() {
        QToolButton::setDisabled(true);
    }
};

#endif // BUTTON_H

