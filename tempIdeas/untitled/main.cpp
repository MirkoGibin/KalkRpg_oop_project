#include <QApplication>
#include "kalkrpg.h"
#include"model.h"
#include"controller.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Model*model=new Model();
    Controller*controller=new Controller(model);
    KalkRpg* kalk=new KalkRpg(0, controller);
    kalk->show();
    return app.exec();
}
