#ifndef MYSPIRIT_H
#define MYSPIRIT_H
#include <QWidget>
#include <QMainWindow>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <registerwidget.h>
#include <namewidget.h>
#include <petwidget.h>
#include <QTimer>
#include <QTime>
#include <QIcon>
#include <QPalette>
#include <QImage>
#include <QBrush>

namespace Ui {
class MySpirit;
}

class MySpirit : public QMainWindow
{
    Q_OBJECT

public:
    explicit MySpirit(QWidget *parent = 0);
    ~MySpirit();
    bool IsTableExist(QSqlQuery &query,QString table);
    //注册窗口
    registerWidget *RegisterWidget = new registerWidget;
    //命名窗口
    nameWidget *NameWidget = new nameWidget;

private slots:
    //注册按钮
    void on_Register_clicked();
   //登录按钮
    void on_logIn_clicked();

private:
    //基本属性值
    QString name;
    QString NUM;
    QString num;//登录验证
    QString PASS;
    QString pass;//登录验证
    QSqlQuery query;

private:
    Ui::MySpirit *ui;
};

#endif // MYSPIRIT_H
