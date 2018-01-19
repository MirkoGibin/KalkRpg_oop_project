#ifndef BUTTON_H
#define BUTTON_H
#include <QSize>
#include <QIcon>
#include <QWidget>
#include <QToolButton>
#include <QObject>

class Button : public QToolButton {
private:
    const char* path_;
    Q_OBJECT

private:
    const QString testo;
    const QIcon icona;
public:
    explicit Button(const char *path, const QString &testo, QWidget *parent = 0) : QToolButton(parent) {
        path_ = path;
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        setIcon(QIcon(path));
        setText(testo);
        setObjectName(testo);
    }
    QSize sizeHint() const override {
        QSize size = QToolButton::sizeHint();
        size.rheight() += 20;
        size.rwidth() = qMax(size.width(), size.height());
        return size;
    }
    const char* getPath() const {
        return path_;
    }
    ~Button() {
        //delete[] path_;
    }
    QString getTesto() const {return testo;}
    QIcon getIcona() const {return icona;}
public slots:
    void setEnabled() {
        this->QToolButton::setEnabled(true);
    void setDisabled() {
    }
        this->QToolButton::setDisabled(true);
    }

signals:
};

#endif // BUTTON_H

