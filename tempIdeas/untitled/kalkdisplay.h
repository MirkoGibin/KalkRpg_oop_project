#ifndef DISPLAY_H
#define DISPLAY_H

#include<QWidget>
#include<QTextEdit>


class KalkDisplay : public QTextEdit {
private:
public:
    Display(QWidget* parent =0) : QTextEdit(parent) {
        setReadOnly(true);
        setMinimumSize(600,100);
    }
};

#endif // DISPLAY_H
