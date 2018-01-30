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

public:
    explicit Button(const char *path, const QString &testo, QWidget *parent = 0);
    QSize sizeHint() const override;
    const char* getPath() const;
    ~Button();
};

#endif // BUTTON_H

