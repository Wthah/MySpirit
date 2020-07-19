#ifndef STOREWIDGET_H
#define STOREWIDGET_H

#include <QDialog>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <petwidget.h>
#include <QTimer>
#include <QTime>
#include <QPalette>
#include <QImage>
#include <QString>

namespace Ui {
class storeWidget;
}

class storeWidget : public QDialog
{
    Q_OBJECT

public:
    explicit storeWidget(QWidget *parent = 0);
    ~storeWidget();
    void set();
    void setNum(QString NUM);
    //传递
    void file();

private slots:
    void on_aPushButton_clicked();

    void on_jPushButton_clicked();

    void on_sPushButton_clicked();

    void on_rPushButton_clicked();

    void on_pushButton_5_clicked();

    void upMoney1();

private:
    Ui::storeWidget *ui;
    //商店货物
    int apple;
    int spunSugar;
    int riceBall;
    int juice;
    int fuHuo;

    int money;

    QSqlQuery query;

    QTimer * moneyTime1;

    QString NUM;
};

#endif // STOREWIDGET_H
