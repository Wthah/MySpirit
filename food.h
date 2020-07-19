#ifndef FOOD_H
#define FOOD_H

#include <QWidget>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QPalette>
#include <QImage>


namespace Ui {
class food;
}

class food : public QWidget
{
    Q_OBJECT

public:
    explicit food(QWidget *parent = 0);
    ~food();
    void set();
    void setNum(QString NUM);
    QSqlQuery query;

private slots:
    void on_sButton_clicked();

    void on_pushButton_2_clicked();

    void on_jButton_clicked();

    void on_aButton_clicked();

    void on_fButton_clicked();

private:
    Ui::food *ui;
    int apple;
    int spunSugar;
    int riceBall;
    int fuHuo;
    int juice;
    //其它给我设成false，若调用本人设为true下次返回加一
    bool aFlag=false;
    bool sFlag=false;
    bool rFlag=false;
    bool jFlag=false;
    bool shFlag=false;
    int goodSensitivity;
    int hungrySensitivity;

    QString NUM;
};

#endif // FOOD_H
