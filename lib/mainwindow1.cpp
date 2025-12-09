#include "mainwindow.h"
#include <QSplitter>
#include <QDir>
#include <QFileInfo>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Центральный виджет
    central = new QWidget(this);
    setCentralWidget(central);

    // Поле пути
    pathEdit = new QLineEdit(this);
    pathEdit->setObjectName("pathEdit");

    // Кнопки
    btnUp = new QPushButton("back", this);

    // Вьюхи
    treeView = new QTreeView(this);
    listView = new QListView(this);

    // Модели
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath("/");

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    fileModel->setRootPath("/");

    // Лэйаут кнопок
    QHBoxLayout *topButtons = new QHBoxLayout;
    topButtons->addWidget(btnUp);
    topButtons->addStretch();

    // Разделитель
    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(treeView);
    splitter->addWidget(listView);

    // Главный лэйаут
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(topButtons);
    mainLayout->addWidget(pathEdit);
    mainLayout->addWidget(splitter);

    openPath(QDir::homePath());

    // Сигналы
    connect(treeView, &QTreeView::clicked, this, &MainWindow::onDirClicked);
    connect(listView, &QListView::doubleClicked, this, &MainWindow::onFileClicked);
    connect(btnUp, &QPushButton::clicked, this, &MainWindow::goUp);
}

MainWindow::~MainWindow() {}

void MainWindow::openPath(const QString &path)
{
    pathEdit->setText(path);
    auto rootIndex = fileModel->setRootPath(path);
    listView->setRootIndex(rootIndex);
}

void MainWindow::onDirClicked(const QModelIndex &index)
{
    QString path = dirModel->filePath(index);
    openPath(path);
}

void MainWindow::onFileClicked(const QModelIndex &index)
{
    QFileInfo info = fileModel->fileInfo(index);
    if(info.isDir())
    {
        openPath(info.absoluteFilePath());
    }
    else
    {
        QProcess::execute("cmd", QStringList() << "/c" << info.absoluteFilePath());
    }
}

void MainWindow::goUp()
{
    QString parent = QFileInfo(pathEdit->text()).dir().absolutePath();
    openPath(parent);
}
