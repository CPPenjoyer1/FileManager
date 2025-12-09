#ifndef TEST_HPP
#define TEST_HPP

#include <QObject>

class TestMainWindow : public QObject
{
    Q_OBJECT
public:
    TestMainWindow();
    ~TestMainWindow();

private slots:
    void testOpenPath();
    void testGoUp();
    void testDirClick();
    void testFileClick();
};

#endif // TEST_HPP
