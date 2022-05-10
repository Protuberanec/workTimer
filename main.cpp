#include "mainwindow.h"
#include "bd_task.h"


#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Bd_task myTaskBd;

    QObject::connect(&w, &MainWindow::sig_AddNewTask, &myTaskBd, &Bd_task::slot_addTask);
    QObject::connect(&w, &MainWindow::sig_AddDur, &myTaskBd, &Bd_task::slot_addDuration);

    w.show();

    return a.exec();
}
