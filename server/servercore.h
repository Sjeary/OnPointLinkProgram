#ifndef SERVERCORE_H
#define SERVERCORE_H

#include <QObject>

class servercore : public QObject
{
    Q_OBJECT
public:
    explicit servercore(QObject *parent = nullptr);
    ~servercore();

signals:

};

#endif // SERVERCORE_H
