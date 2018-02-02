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
        setMinimumSize(600,250);
    }
    void clear() {
        QTextEdit::clear();
        history.clear();
    }

    void show(const QImage* image, QList<QString> parametri) { //scelta di non passare per riferimento perche' viene usato takefirst sulla copia di parametri

        QTextCursor cursor = textCursor();

        QTextTableFormat tabFormat;
        tabFormat.setBorder(1);
        tabFormat.setAlignment(Qt::AlignCenter);

        QVector<QTextLength> cellWidth;
        for(int i = 0; i < parametri.length(); i++)
            cellWidth.push_back(QTextLength(QTextLength::FixedLength, 70));
        tabFormat.setColumnWidthConstraints(cellWidth);


        QTextTable* table = cursor.insertTable(1,parametri.length()+1, tabFormat);
        history.push_back(cursor.position());
        table->cellAt(0, 0).firstCursorPosition().insertImage(*image);

        int j=1;
        while(!(parametri.isEmpty())) {
            QTextCursor tabCursor = table->cellAt(0, j).firstCursorPosition();
            QTextBlockFormat align;
            align.setAlignment(Qt::AlignHCenter);
            tabCursor.setBlockFormat(align);
            tabCursor.insertText(parametri.takeFirst());
            j++;
        }

        moveCursor(cursor.EndOfBlock);
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

        setTextCursor(cursor);
    }

    void show(const QString num) {
        QTextCursor cursor = textCursor();

        QTextBlockFormat format = cursor.blockFormat();
        format.setAlignment(Qt::AlignCenter);
        cursor.mergeBlockFormat(format);

        cursor.insertText(num);

        //cursor.insertImage(num);
        history.push_back(cursor.position());
        cursor.insertText("\n");

        moveCursor(QTextCursor::End);
    }



    void back() {
        if(!(history.isEmpty())) {
            QTextCursor cursor = textCursor();
            cursor.setPosition(history.takeLast());

            if(cursor.currentTable() != nullptr)
                cursor.currentTable()->removeRows(0,1);
            else {
               cursor.select(QTextCursor::LineUnderCursor);
                cursor.removeSelectedText();
            }

            setTextCursor(cursor);
      }
    }
};

#endif // DISPLAY_H
