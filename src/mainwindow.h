#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "filemanager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;
    FileManager* getFileManager() {return manager;}
    void openPath(const QString &path);

public slots:
    void onDirClicked(const QModelIndex &index);
    void onFileClicked(const QModelIndex &index);
    void goUp();

private:
    void initUI();
    void initConnections();


    QWidget *central;
    QLineEdit *pathEdit;
    QTreeView *treeView;
    QListView *listView;
    QPushButton *btnUp;

    // Логика (новый класс)
    FileManager *manager;
};

#endif // MAINWINDOW_H
