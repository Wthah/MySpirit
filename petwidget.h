#ifndef PETWIDGET_H
#define PETWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlError>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QLineEdit>
#include <QLabel>
#include <changewidget.h>
#include <QPixmap>
#include <QBrush>
#include <QPalette>
#include <QMovie>
#include <QSize>
#include <myqlabel.h>
#include <storewidget.h>
#include <food.h>
#include <gamewindow.h>
//#include <QSound>


class MyQLabel;

namespace Ui {
class petWidget;
}

class petWidget : public QWidget
{
    Q_OBJECT

public:
    explicit petWidget(QWidget *parent = 0);
    ~petWidget();
    void upMode();
    void upButton();
    void upHealthy1();
    void set();
    void putImage(MyQLabel *label);
    QString getNum();
    void setNum(QString NUM);
private:

    QString NUM;
    //当前状态
    enum Mode{UsualMode,HungryMode,SickMode,DeadMode};
    //定时器设置
    QTimer *goodSensitivityTime;
    QTimer *hungryTime ;
    QTimer *hungryTime1;
    QTimer *healthyTime ;
    QTimer *ageTime ;
    QTimer *weightTime;
    QTimer *moneyTime;
    QTimer *moneyTime1;
    QSqlQuery query;
    QString currentMode;
    QTimer *pathTime;
    QTimer *jiankongTime;
    QTimer *gifTime;
    QTimer *eatingTime;
    QTimer *lengqueTime;
    QTimer *healthyTime1;

    //基本属性
    int hungrySensitivity1;
    int age1;
    int weight1;
    int healthy1;
    int goodSensitivity1;
    QString name1;
    //商店货物
    int money1;
    int apple;
    int spunSugar;
    int riceBall;
    int juice;
    int fuHuo;
    //图片路径
    QString path;
    QString eating;
    //点击事件Label
    MyQLabel* my_label;
    //换场景界面
    changeWidget* ChangeWidget = new changeWidget;
    //喂食界面
    food* foodWidget = new food;
    //防止无赖刷好感度
    bool isLenque=false;

private slots:

    void on_storeButton_clicked();

    void on_Fun_clicked();

    void on_Food_clicked();

    void on_Resurrection_clicked();

    void on_Cure_clicked();

    void on_changeButton_clicked();

    void lengque();

    //定时改变四个属性
    void upHungry();
    void upHealthy();
    void upAge();
    void upWeight();
    void upMoney();
    void upMoney1();
    void upPath();
    void upgoodSensitivity();
    void upHungry1();
    void jiankong();
    void restore();
    void eat();
    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

//    void on_start_clicked();

private:
    Ui::petWidget *ui;
};

#endif // PETWIDGET_H
