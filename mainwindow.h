#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define PB_START_START  "Start"
#define PB_START_STOP  "Stop"


class MainWindow : public QMainWindow
{
    Q_OBJECT
private :
    QTimer* timWork;
    void initTimWork();
    void initSlotsSig();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots :
    void slot_StartStopTimer();
    void slot_AddOneSec();

signals:
    void sig_AddNewTask(const QString& taskName);
    void sig_AddDur(const QString& taskName, int dur);

};
#endif // MAINWINDOW_H
