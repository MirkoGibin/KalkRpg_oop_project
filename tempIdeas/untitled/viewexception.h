#ifndef VIEWEXCEPTION_H
#define VIEWEXCEPTION_H

#include<Qstring>

class ViewException {
private:
    QString err;
public:
  ViewException(QString errore) : err(errore) {}

  QString getErrore() const {
      return err;
  }
};
#endif // VIEWEXCEPTION_H
