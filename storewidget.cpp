#include "storewidget.h"
#include "ui_storewidget.h"
#include "petwidget.h"

storeWidget::storeWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::storeWidget)
{
    ui->setupUi(this);
    moneyTime1 = new QTimer(this);
    connect(moneyTime1,SIGNAL(timeout()),this,SLOT(upMoney1()));

    //设置背景图
    setAutoFillBackground(true);
    QPalette PAllbackground;
    QImage ImgAllbackground("://store/beijing.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(868,576, Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}
//空间释放
storeWidget::~storeWidget()
{
    delete ui;
    delete moneyTime1;
    delete this;
}
//苹果购买
void storeWidget::on_aPushButton_clicked()
{
    if(money>=10)
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买成功."));
        query.prepare("update spirit1 set money = :money, apple = :apple where number = :number");
        query.bindValue(":money",money-10);
        moneyTime1->start(10);
        query.bindValue(":apple",apple+1);
        query.bindValue(":number",NUM);
        query.exec();
        apple=apple+1;
    }
    else
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买失败，金币不足可以通过游戏获得."));
    }
}
//饮料购买
void storeWidget::on_jPushButton_clicked()
{
    if(money>=10)
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买成功."));
        query.prepare("update spirit1 set money = :money, juice = :juice where number = :number");
        query.bindValue(":money",money-10);
        moneyTime1->start(10);
        query.bindValue(":juice",juice+1);
        query.bindValue(":number",NUM);
        query.exec();
        juice=juice+1;
    }
    else
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买失败，金币不足可以通过游戏获得."));
    }
}
//棉花糖购买
void storeWidget::on_sPushButton_clicked()
{
    if(money>=5)
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买成功."));
        query.prepare("update spirit1 set money = :money, spunSugar = :spunSugar where number = :number");
        query.bindValue(":money",money-5);
        moneyTime1->start(10);
        query.bindValue(":spunSugar",spunSugar+1);
        query.bindValue(":number",NUM);
        query.exec();
        spunSugar=spunSugar+1;
    }
    else
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买失败，金币不足可以通过游戏获得."));
    }
}
//饭团购买
void storeWidget::on_rPushButton_clicked()
{
    if(money>=15)
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买成功."));
        query.prepare("update spirit1 set money = :money, riceBall = :riceBall where number = :number");
        query.bindValue(":money",money-15);
        moneyTime1->start(10);
        query.bindValue(":riceBall",riceBall+1);
        query.bindValue(":number",NUM);
        query.exec();
        riceBall=riceBall+1;
    }
    else
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买失败，金币不足可以通过游戏获得."));
    }
}
//复活道具购买
void storeWidget::on_pushButton_5_clicked()
{
    if(money>=200)
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买成功."));
        query.prepare("update spirit1 set money = :money, fuHuo = :fuHuo where number = :number");
        query.bindValue(":money",money-200);
        moneyTime1->start(10);
        query.bindValue(":fuHuo",fuHuo+1);
        query.bindValue(":number",NUM);
        query.exec();
        fuHuo=fuHuo+1;
    }
    else
    {
        QMessageBox::information(this, tr("My Store"),
        tr("购买失败，金币不足可以通过游戏获得."));
    }
}
//基本设置
void storeWidget::set()
{
        //读取数据
        query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
        query.bindValue(":number",NUM);
        query.exec();
        QSqlRecord rec1 = query.record();
        while(query.next()){
        int number8 = rec1.indexOf("money");
        money = query.value(number8).toInt();
        int number9 = rec1.indexOf("apple");
        apple = query.value(number9).toInt();
        int number10 = rec1.indexOf("spunSugar");
        spunSugar = query.value(number10).toInt();
        int number11 = rec1.indexOf("riceBall");
        riceBall = query.value(number11).toInt();
        int number12 = rec1.indexOf("juice");
        juice = query.value(number12).toInt();
        int number13 = rec1.indexOf("fuHuo");
        fuHuo = query.value(number13).toInt();
}
}
//每0.1秒读取一次金币，保证不会数据错误
void storeWidget::upMoney1(){
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int money2 = rec.indexOf("money");
    money = query.value(money2).toInt();
    }
}

void storeWidget::setNum(QString NUM)
{
    this->NUM=NUM;
}
