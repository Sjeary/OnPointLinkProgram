#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>

class FileSystem : public QObject
{
    Q_OBJECT
public:
    explicit FileSystem(QObject *parent = nullptr);

    void makeBasicFolder();

signals:

};

#endif // FILESYSTEM_H
