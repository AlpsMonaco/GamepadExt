#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(AppendText()),this,SLOT(DoAppendText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DoAppendText(){
    qDebug()<<QString("Start");
    this->ui->plainTextEdit->appendPlainText("asd");
    this->ui->plainTextEdit->repaint();
}
