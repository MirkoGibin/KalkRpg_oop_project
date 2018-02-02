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
    explicit Button(const QString&, const char* =0, QWidget* =0);
    QSize sizeHint() const override;
    const char* getPath() const;

    QString getTesto() const;

public slots:
    void setEnabled();

    void setDisabled();
};

#endif // BUTTON_H

