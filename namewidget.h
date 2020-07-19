#ifndef NAMEWIDGET_H
#define NAMEWIDGET_H

#include <QDialog>
#include <QString>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlError>
#include <petwidget.h>
#include <QMessageBox>
#include <QByteArray>

namespace Ui {
class nameWidget;
}

class nameWidget : public QDialog
{
    Q_OBJECT

public:
    explicit nameWidget(QWidget *parent = 0);
    ~nameWidget();
     int testName(QString Name);
    //宠物窗口

public:
    void setNum(QString NUM);

private slots:
    void on_start_clicked();

private:
    Ui::nameWidget *ui;
    QSqlQuery query;
    QString NUM;
};

#endif // NAMEWIDGET_H
