#include "mainwindow.h"
#include <QApplication>
#include "controller.h"

controller::Controller* c = nullptr;

struct Initializer
{
    Initializer() { }
    ~Initializer()
    {
        if (c != nullptr)
        {
            c->Stop();
            delete c;
        }
    }
} init;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    c = new controller::MapKeyToKey();
    c->Start();
    return a.exec();
}
