#ifndef VIEWEXCEPTION_H
#define VIEWEXCEPTION_H

#include<QString>

class ViewException {
private:
    QString err;
public:
  ViewException(QString);

  QString getErrore() const;
};
#endif // VIEWEXCEPTION_H
