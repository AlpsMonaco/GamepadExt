#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AppendText()
{
    qDebug()<<QString("Start Append text");
}

void MainWindow::DoAppendText(){
    this->ui->plainTextEdit->appendPlainText("asd");
}
