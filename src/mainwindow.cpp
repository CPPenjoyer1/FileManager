#include "mainwindow.h"
#include <QSplitter>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    central(new QWidget(this)),
    pathEdit(new QLineEdit(this)),
    treeView(new QTreeView(this)),
    listView(new QListView(this)),
    btnUp(new QPushButton("Back", this)),
    manager(new FileManager(this))
{
    setCentralWidget(central);

    initUI();

    // Подключаем модели
    treeView->setModel(manager->dirModel());
    listView->setModel(manager->fileModel());

    initConnections();

    openPath(QDir::homePath());
}

// ------------------------
// UI
// ------------------------
void MainWindow::initUI()
{
    auto *topButtons = new QHBoxLayout;
    topButtons->addWidget(btnUp);
    topButtons->addStretch();

    auto *splitter = new QSplitter(this);
    splitter->addWidget(treeView);
    splitter->addWidget(listView);
    splitter->setStretchFactor(1, 1);

    auto *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(topButtons);
    mainLayout->addWidget(pathEdit);
    mainLayout->addWidget(splitter);

    treeView->setHeaderHidden(true);
}

// ------------------------
// SIGNALS
// ------------------------
void MainWindow::initConnections()
{
    connect(treeView, &QTreeView::clicked, this, &MainWindow::onDirClicked);

    connect(listView, &QListView::doubleClicked, this, &MainWindow::onFileClicked);

    connect(btnUp, &QPushButton::clicked, this, &MainWindow::goUp);
}

// ------------------------
// LOGIC
// ------------------------
void MainWindow::openPath(const QString &path)
{
    QModelIndex idx = manager->setCurrentPath(path);
    pathEdit->setText(path);
    listView->setRootIndex(idx);
}

void MainWindow::onDirClicked(const QModelIndex &index)
{
    QString path = manager->dirModel()->filePath(index);
    openPath(path);
}

void MainWindow::onFileClicked(const QModelIndex &index)
{
    QFileInfo info = manager->fileInfo(index);

    if (info.isDir())
    {
        openPath(info.absoluteFilePath());
    }
    else
    {
        manager->openFile(info.absoluteFilePath());
    }
}

void MainWindow::goUp()
{
    QString parent = manager->parentPath(pathEdit->text());
    openPath(parent);
}
