#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QFileSystemModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openPath(const QString &path);

private slots:
    void onDirClicked(const QModelIndex &index);
    void onFileClicked(const QModelIndex &index);
    void goUp();

private:
    // Виджеты
    QWidget *central;
    QLineEdit *pathEdit;
    QTreeView *treeView;
    QListView *listView;

    QPushButton *btnUp;

    // Модели
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;


};

#endif // MAINWINDOW_H
