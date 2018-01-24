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
    Display(QWidget* parent =0) : QTextEdit(parent) {
        setReadOnly(true);
        setMinimumSize(600,100);
    }

    void show(const QImage* image, QList<QString>* parametri) {

        QTextCursor cursor = textCursor();

        QTextTableFormat tabFormat;
        tabFormat.setBorder(0);
        tabFormat.setAlignment(Qt::AlignCenter);

        QVector<QTextLength> cellWidth;
        for(int i = 0; i < parametri->length(); i++)
            cellWidth.push_back(QTextLength(QTextLength::FixedLength, 70));
        tabFormat.setColumnWidthConstraints(cellWidth);

        QTextTable* table = cursor.insertTable(1,parametri->length()+1, tabFormat);

        history.push_back(cursor.position());

        table->cellAt(0, 0).firstCursorPosition().insertImage(*image);

        int j=1;
        while(!(parametri->isEmpty())) {
            QTextCursor tabCursor = table->cellAt(0, j).firstCursorPosition();
            QTextBlockFormat align;
            align.setAlignment(Qt::AlignHCenter);
            tabCursor.setBlockFormat(align);
            tabCursor.insertText(parametri->takeFirst());
            j++;
        }
        delete parametri;
        moveCursor(QTextCursor::End);
        ensureCursorVisible();
    }

    void show(const char* path) {
        QTextCursor cursor = textCursor();

        QTextBlockFormat format = cursor.blockFormat();
        format.setAlignment(Qt::AlignCenter);
        cursor.mergeBlockFormat(format);

        QImage image(path);

        cursor.insertImage(image);
        history.push_back(cursor.position());
        cursor.insertText("\n");

        moveCursor(QTextCursor::End);
    }

    void back() {
        if(!(history.empty())) {
            QTextCursor cursor = textCursor();
            cursor.setPosition(history.takeLast());

            if(cursor.currentTable() != nullptr)
                cursor.currentTable()->removeRows(0,1);
            else {
               cursor.select(QTextCursor::LineUnderCursor);
                cursor.removeSelectedText();
            }

            moveCursor(QTextCursor::End);
      }
    }
};

#endif // DISPLAY_H
