#include "filesystem.h"

#include <QDir>
#include <QFile>
#include <QThread>
#include <QDataStream>

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

void FileSystem::toSaveKeyValue(QString key, QString value)
{
    if(not informationFile->open(QFile::OpenModeFlag::WriteOnly))
        return;
    basicInfo[key] = value;
    QDataStream out(informationFile);
    out<<basicInfo;
    informationFile->close();
}

void FileSystem::toReadKeyValue(QString key)
{
    emit getKeyValue(key, basicInfo.value(key,""));
}
