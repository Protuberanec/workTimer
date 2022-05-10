#include "bd_task.h"

void Bd_task::createBd()
{
    QSqlQuery query;
    bool ok = query.exec("create table if not exists tasks (id integer primary key autoincrement, task varchar(64));");
    qDebug() << query.lastError();
    ok = query.exec("create table if not exists underTask (id integer primary key autoincrement, id_mainTask integer, underTask varchar(64),"
                                        "foreign key(id_mainTask) references tasks(id));");

    ok = query.exec("create table if not exists durations (id integer primary key autoincrement, duration integer, "
                                        "id_task integer, foreign key(id_task) references tasks(id));");

}

Bd_task::Bd_task(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("task.bd");
    bool ok = db.open();
    createBd();
}

Bd_task::~Bd_task()
{
    db.close();
}

void Bd_task::slot_addTask(const QString &taskName)
{
    addTask(taskName);
}

void Bd_task::slot_deleteTask(const QString &taskName)
{
    QSqlQuery query;
    bool ok = query.exec(QString("delete from tasks where task like %1").arg(taskName));
    assert(ok == true);
}

void Bd_task::slot_addDuration(const QString &taskName, int time)
{
    addDuration(taskName, time);
}

int Bd_task::selectIdTask(const QString &taskName)
{
    int id = 0;
    QSqlQuery query;
    query.exec(QString("select * from tasks where task like '%1';").arg(taskName));
    while(query.next()) {
        qDebug() << query.value("id").toUInt() << " : " << query.value("task").toString();
        id = query.value("id").toUInt();
    }
    return id;
}

int Bd_task::addTask(const QString &taskName)
{
    int id = selectIdTask(taskName);
    if (id == 0) {
        QSqlQuery query;
        bool ok = query.exec(QString("insert into tasks(task) values ('%1');").arg(taskName));
        qDebug() << query.lastError();
        id = query.lastInsertId().toUInt();
    }
    return id;
}

int Bd_task::addDuration(const QString &taskName, int dur)
{
    int id_task = selectIdTask(taskName);
    if (id_task == 0) {
        //error!!
        return -1;
    }

    QSqlQuery query;
    bool ok = query.exec(QString("insert into durations(id_task, duration) values (%1,%2);").arg(id_task).arg(dur));

    return query.lastInsertId().toUInt();
}

