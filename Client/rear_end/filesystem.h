#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include <QMap>


class QDir;
class QFile;

class FileSystem : public QObject
{
    Q_OBJECT
public:
    explicit FileSystem(QObject *parent = nullptr);

    QMap<QString,QString> getSavedAccount();
    ~FileSystem();



signals:
    void setCoreKeyValue(QString key, QString value); // 作用：通知core将参数key（比如serverIP）改为value

public slots:
    void makeBasic();
    void toSaveKeyValue(QString key, QString value);
    void toReadKeyValue(QString key);

private:
    QDir *basicFolder, *commonFolder;
    QFile *informationFile;
    QMap<QString, QString> basicInfo;
    /*
     * baseInfo可能含有的信息：
     * "savedOID": ,保存账户的OID；
     * "savedPassword": ，保存账户的登录密码。
     * "serverIP": ，服务器IP。
    */
};

#endif // FILESYSTEM_H
