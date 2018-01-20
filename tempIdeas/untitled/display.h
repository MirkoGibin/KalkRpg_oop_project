#ifndef DISPLAY_H
#define DISPLAY_H

#include<QWidget>
#include<QTextEdit>


class Display : public QTextEdit {
private:
public:
    Display(QWidget* parent =0) : QTextEdit(parent) {
        setReadOnly(true);
        setMinimumSize(600,100);
    }

    void show(const QImage* image, QList<QString>* parametri) {

        QTextCursor cursor = textCursor();
        cursor.setPosition(0);

        QTextTableFormat format;
        format.setBorder(0);

        QVector<QTextLength> cellWidth;
        for(int i = 0; i < parametri->length(); i++)
            cellWidth.push_back(QTextLength(QTextLength::FixedLength, 70));
        format.setColumnWidthConstraints(cellWidth);

        QTextTable* table = cursor.insertTable(1,parametri->length()+1, format);

        table->cellAt(0, 0).firstCursorPosition().insertImage(*image);

        int j=1;
        while(!(parametri->isEmpty())) {
            table->cellAt(0, j).
                    firstCursorPosition().
                    insertText(parametri->takeFirst());
            j++;
        }

        delete parametri;
    }
};

#endif // DISPLAY_H
