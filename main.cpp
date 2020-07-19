#include "myspirit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("spirit-1");
    db.setDatabaseName("spirit1.db");
    db.setUserName("xingzhe");
    db.setPassword("zzx010728");
    db.open();
    if(db.open()==false)
    {
        qDebug() << "database is not open";
    }
    MySpirit w;

    w.setMaximumSize(580,335);
    w.setMinimumSize(580,335);
    w.show();

    return a.exec();
}
