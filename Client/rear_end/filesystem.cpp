#include "filesystem.h"

#include <QDir>
#include <QThread>

FileSystem::FileSystem(QObject *parent)
    : QObject{parent}
{}


void FileSystem::makeBasicFolder()
{
    QDir basicFolder("./basicFolder");
    if(not basicFolder.exists())
    {
        basicFolder.mkpath(".");
    }
}
