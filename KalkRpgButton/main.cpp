#include <QApplication>>
#include "kalkrpg.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    KalkRpg kalk;
    kalk.show();
    return app.exec();
}
