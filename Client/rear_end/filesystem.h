/*
 * ============================
 * filesystem.h
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 FileSystem 类
 * 声明 FileSystem 类的成员函数
 * ============================
 *
*/

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

    QMap<QString,QString> getSavedAccount();
    ~FileSystem();



signals:
    void setCoreKeyValue(QString key, QVariant value); // 作用：通知core将参数key（比如serverIP）改为value

public slots:
    void makeBasic();
    void toSaveKeyValue(QString key, QVariant value);
    void toReadKeyValue(QString key);

private:
    QDir *basicFolder, *commonFolder;
    QFile *informationFile;
    QMap<QString, QVariant> basicInfo;
    /*
     * basicInfo: 存储一些基本参数
     * 包括但不限于：
     * "serverIP"：服务器IP
     * "savedOID"：保存的账户的OID、
     * "savedPassword"：保存的账户密码
    */
};

#endif // FILESYSTEM_H
