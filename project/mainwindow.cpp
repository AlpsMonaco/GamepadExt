#include <Windows.h>
#include <WinUser.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#pragma comment(lib, "User32.lib")

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(AppendText()), this, SLOT(DoAppendText()));
    this->OnClose = []() -> void {};
}

void MainWindow::SetCloseEvent(void (*f)()) { this->OnClose = f; }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DoAppendText()
{
    qDebug() << QString("Start");
    this->ui->plainTextEdit->appendPlainText("asd");
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    this->OnClose();
}
