#ifndef BD_TASK_H
#define BD_TASK_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

class Bd_task : public QObject
{
    Q_OBJECT
private :
    QSqlDatabase db;

    void createBd();

    int selectIdTask(const QString& taskName);
    int addTask(const QString& taskName);
    int addDuration(const QString& taskName, int dur);
public:
    explicit Bd_task(QObject *parent = nullptr);
    ~Bd_task();


signals:

public slots :
    void slot_addTask(const QString& taskName);
    void slot_deleteTask(const QString& taskName);
    void slot_addDuration(const QString& taskName, int time);
};

#endif // BD_TASK_H
