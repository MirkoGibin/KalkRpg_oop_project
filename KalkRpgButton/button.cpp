#include "button.h"

Button::Button(const char *path, const QString &testo, QWidget *parent) : QToolButton(parent) {
    path_ = path;
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setIcon(QIcon(path));
    setText(testo);
    setObjectName(testo);
}

QSize Button::sizeHint() const {
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

const char* Button::getPath() const {
    return path_;
}

Button::~Button() {
    //delete[] path_;
}


