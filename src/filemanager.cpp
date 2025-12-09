#include "filemanager.h"
#include <QProcess>
#include <QDir>

FileManager::FileManager(QObject *parent) : QObject(parent),
    m_dirModel(new QFileSystemModel(this)),
    m_fileModel(new QFileSystemModel(this))
{
    m_dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    m_dirModel->setRootPath(QDir::rootPath());

    m_fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    m_fileModel->setRootPath(QDir::rootPath());
}

QString FileManager::normalizePath(const QString &path)
{
    return QDir(path).absolutePath();
}

QString FileManager::parentPath(const QString &path)
{
    return QFileInfo(path).dir().absolutePath();
}

QModelIndex FileManager::setCurrentPath(const QString &path)
{
    m_currentPath = normalizePath(path);
    return m_fileModel->setRootPath(m_currentPath);
}

bool FileManager::isDir(const QModelIndex &index)
{
    return m_fileModel->isDir(index);
}

QFileInfo FileManager::fileInfo(const QModelIndex &index)
{
    return m_fileModel->fileInfo(index);
}

void FileManager::openFile(const QString &path)
{
    QProcess::startDetached(path);
}
