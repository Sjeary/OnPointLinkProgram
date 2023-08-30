/*
 * ============================
 * filesystem.cpp
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 FileSystem 类成员函数
 * ============================
 *
*/

#include "filesystem.h"

#include <QDir>
#include <QFile>
#include <QThread>
#include <QDataStream>
#include <QDebug>

FileSystem::FileSystem(QObject *parent)
    : QObject{parent}
{
    basicFolder = new QDir("./basicFolder");
    commonFolder = new QDir("./basicFolder/common");
    informationFile = new QFile("./basicFolder/common/basicInfo");
    makeBasic();
}

FileSystem::~FileSystem()
{
    delete basicFolder;
    delete commonFolder;
    delete informationFile;
}

void FileSystem::makeBasic()
{

    if(not basicFolder->exists())
    {
        basicFolder->mkpath(".");
    }
    if(not commonFolder->exists())
    {
        commonFolder->mkpath(".");
    }
    if(informationFile->open(QFile::OpenModeFlag::ReadOnly))
    {
        QDataStream in(informationFile);
        in>>basicInfo;
    }
    informationFile->close();
}

QMap<QString,QString> FileSystem:: getSavedAccount()
{
    /*
     * getSavedAccount (updated by zwx)。
     * 获取已保存的用户。
     * 返回一个QMap，{"savedOID": ,"savedPassword": }
    */
    QMap<QString,QString> result;
    result["savedOID"] = basicInfo.value("savedOID","").toString();
    result["savedPassword"] = basicInfo.value("savedPassword","").toString();
    return result;
}

void FileSystem::toSaveKeyValue(QString key, QVariant value)
{
    if(not informationFile->open(QIODevice::WriteOnly)){
        qDebug() << "Fail to open informationFile" ;
        return;
    }
    basicInfo[key] = value;
    QDataStream out(informationFile);
    out<<basicInfo;
    informationFile->close();
}

void FileSystem::toReadKeyValue(QString key)
{
    emit setCoreKeyValue(key, basicInfo.value(key,""));
}

QString FileSystem::getSavedServerIP()
/*
 * getSavedServerIP
 * 返回上一次的SererIP
*/
{
    return basicInfo.value("serverIP","").toString();
}
