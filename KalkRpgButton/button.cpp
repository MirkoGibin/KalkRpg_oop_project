#include "button.h"

Button::Button(const QIcon &icona, const QString &testo, QWidget *parent) : QToolButton(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setIcon(QIcon(":/icons/erba.png"));
    setText(testo);
}

QSize Button::sizeHint() const {
    QSize size = QToolButton::sizeHint();
    size.rheight() += 200;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
