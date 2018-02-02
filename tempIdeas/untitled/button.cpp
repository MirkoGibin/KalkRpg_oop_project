#include "button.h"

Button::Button(const QString &testo, const char *path, QWidget *parent) : QToolButton(parent), path_(path), testo_(testo) {

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    if(path != 0) {
        setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        setIcon(QIcon(path));
    }
    setText(testo);
    setObjectName(testo);
}

QSize Button::sizeHint() const {
    QSize size = QToolButton::sizeHint();
    size.rwidth() = 83;
    size.rheight() = 60;
    return size;
}

const char *Button::getPath() const {
    return path_;
}

QString Button::getTesto() const {
    return testo_;
}

void Button::setEnabled() {
    QToolButton::setEnabled(true);
}

void Button::setDisabled() {
    QToolButton::setDisabled(true);
}
