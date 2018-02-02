#include "viewexception.h"

QString ViewException::getErrore() const {
    return err;
}
ViewException::ViewException(QString errore) : err(errore) {}

