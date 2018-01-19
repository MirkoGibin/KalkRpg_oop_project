#include <QApplication>
#include "kalkrpg.h"
#include"model.h"
#include"controller.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Controller*controller=new Controller();
    KalkRpg* kalk=new KalkRpg(0, controller);
    kalk->show();
    return app.exec();
}
