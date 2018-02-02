#ifndef DISPLAY_H
#define DISPLAY_H

#include<QWidget>
#include<QTextEdit>
#include<QList>
#include<QTextTable>
#include<QTextCursor>
#include<QScrollBar>


class Display : public QTextEdit {
private:
    QList<int> history;
public:
    Display(QWidget* =0);

    void clear();
    void show(const QImage*, QList<QString>);
    void show(const char*);
    void show(const QString);
    void back();
};

#endif // DISPLAY_H
