#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initTimWork()
{
    timWork = new QTimer();
    timWork->setInterval(1000);
    timWork->setSingleShot(false);
    connect(timWork, &QTimer::timeout, this, &MainWindow::slot_AddOneSec);
}

void MainWindow::initSlotsSig()
{
    connect(ui->PB_Start, &QPushButton::clicked, this, &MainWindow::slot_StartStopTimer);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initTimWork();

    initSlotsSig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_StartStopTimer()
{
    if (ui->PB_Start->text() == PB_START_START) {
        ui->PB_Start->setText(PB_START_STOP);
        ui->TimPanel->display(0);

        emit sig_AddNewTask(ui->LE_TaskName->text());

        timWork->start();
    }
    else {
        ui->PB_Start->setText(PB_START_START);
        timWork->stop();
        emit sig_AddDur(ui->LE_TaskName->text(), ui->TimPanel->value());

    }
}

void MainWindow::slot_AddOneSec()
{
    ui->TimPanel->display(ui->TimPanel->value() + 1);
}

