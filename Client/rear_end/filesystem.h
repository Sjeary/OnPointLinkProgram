#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include <QMap>
#include <QVariant>


class QDir;
class QFile;

class FileSystem : public QObject
{
    Q_OBJECT
public:
    explicit FileSystem(QObject *parent = nullptr);
    ~FileSystem();



signals:
    void getKeyValue(QString key, QVariant value);


public slots:
    void makeBasic();
    void toSaveKeyValue(QString key, QVariant value);
    void toReadKeyValue(QString key);

private:
    QDir *basicFolder, *commonFolder;
    QFile *informationFile;
    QMap<QString, QVariant> basicInfo;
};

#endif // FILESYSTEM_H
