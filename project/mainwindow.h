#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum SimulationMode
{
    MODE_KEYTOGAMEPAD,
    MODE_KEYTOKEY,
    MODE_COMBINE,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetCloseEvent(void (*f)());

protected:
    controller::Controller* GetController();

signals:
    void AppendText(const QString& text);

public slots:
    void DoAppendText(const QString& text);

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow* ui;
    controller::Controller* c;
    SimulationMode mode;
    QPushButton* activeButton[2];
};
#endif // MAINWINDOW_H
