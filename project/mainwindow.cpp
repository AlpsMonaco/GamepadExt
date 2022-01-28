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
    connect(this, SIGNAL(AppendText(QString)), this, SLOT(DoAppendText(QString)));
    //    this->OnClose = []() -> void {};
    this->c = nullptr;
    this->mode = MODE_KEYTOGAMEPAD;
    this->activeButton[0] = this->ui->pushButton_2;
    this->activeButton[1] = this->ui->pushButton_5;
}

// void MainWindow::SetCloseEvent(void (*f)()) { this->OnClose = f; }

MainWindow::~MainWindow()
{
    delete ui;
    if (this->c != nullptr)
    {
        this->c->Stop();
        delete this->c;
        this->c = nullptr;
    }
}

void MainWindow::DoAppendText(const QString& text)
{
    this->ui->plainTextEdit->appendPlainText(text);
}

void MainWindow::on_pushButton_3_clicked()
{
    this->ui->pushButton->setDisabled(true);
    this->ui->pushButton_2->setDisabled(true);
    this->ui->pushButton_3->setDisabled(true);
    this->ui->pushButton_4->setEnabled(true);
    emit this->AppendText("Start");
    this->c = this->GetController();
    this->c->Start();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->ui->pushButton_4->setDisabled(true);
    this->ui->pushButton_3->setEnabled(true);
    emit this->AppendText("Stop");
    this->activeButton[0]->setEnabled(true);
    this->activeButton[1]->setEnabled(true);
    this->c->Stop();
    delete this->c;
    this->c = nullptr;
}

void MainWindow::on_pushButton_clicked()
{
    this->mode = MODE_KEYTOGAMEPAD;
    this->ui->pushButton->setDisabled(true);

    this->ui->pushButton_2->setEnabled(true);
    this->ui->pushButton_5->setEnabled(true);
    this->activeButton[0] = this->ui->pushButton_2;
    this->activeButton[1] = this->ui->pushButton_5;
    emit this->AppendText("Set mode:KeyToGamepad");
}

void MainWindow::on_pushButton_2_clicked()
{
    this->mode = MODE_KEYTOKEY;
    this->ui->pushButton_2->setDisabled(true);

    this->ui->pushButton->setEnabled(true);
    this->ui->pushButton_5->setEnabled(true);
    this->activeButton[0] = this->ui->pushButton;
    this->activeButton[1] = this->ui->pushButton_5;
    emit this->AppendText("Set mode:KeyToKey");
}

controller::Controller* MainWindow::GetController()
{
    switch (this->mode)
    {
    case MODE_KEYTOGAMEPAD:
        return new controller::MapKeyToGamepad();
    case MODE_KEYTOKEY:
        return new controller::MapKeyToKey();
    default:
        return new controller::CombineKeyAndGamepad();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    this->mode = MODE_COMBINE;
    this->ui->pushButton_5->setDisabled(true);

    this->ui->pushButton->setEnabled(true);
    this->ui->pushButton_2->setEnabled(true);
    this->activeButton[0] = this->ui->pushButton;
    this->activeButton[1] = this->ui->pushButton_2;

    emit this->AppendText("Set mode:CombineMode");
}
