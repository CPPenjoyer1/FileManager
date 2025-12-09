#include <QApplication>
#include <QtTest>
#include "test.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TestMainWindow test;
    return QTest::qExec(&test, argc, argv);
}
