#include "mainwindow.h"
#include <QApplication>
#include <thread>


MainWindow* WindowPointer = nullptr;
std::thread t([]()->void{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    WindowPointer->AppendText();
});

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    WindowPointer = &w;
    w.show();
    return a.exec();
}
