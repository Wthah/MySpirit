#include "myqlabel.h"

MyQLabel::MyQLabel(const QString &Titter, QWidget *parent)
    :QLabel(parent)
{
     gifTime1 = new QTimer(this);
     lengqueTime = new QTimer(this);
     this->setText(Titter);
     connect(lengqueTime,SIGNAL(timeout()),this,SLOT(lengque()));
     connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
     connect(gifTime1,SIGNAL(timeout()),this,SLOT(Restore1()));
}

MyQLabel::~MyQLabel()
{
    delete gifTime1;
}
void MyQLabel::slotClicked()
{
    upMode();
    //点击事件
    if(Islengque==false){
    if(currentMode=="DeadMode")
    {
        QMessageBox::information(this, tr("提示"),
        tr("你的宠物已死亡"));
    }
    //普通状态
    else if(currentMode=="UsualMode"){
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec1 = query.record();
    while(query.next()){
    int number = rec1.indexOf("goodSensitivity");
    goodSensitivity = query.value(number).toInt();
    }
    query.prepare("update spirit1 set goodSensitivity = :goodSensitivity where number = :number");
    if(goodSensitivity<100){
    query.bindValue(":goodSensitivity", goodSensitivity+1);
    query.bindValue(":number",NUM);
    query.exec();
    goodSensitivity = goodSensitivity +1;
    }
    else
    {
        //不做任何操作
    }
    //阶段一
    if(goodSensitivity<=60){
     QMovie *movie = new QMovie("://quyudianji/quyudianji1.gif");
     QSize si (240,135);
     movie->setScaledSize(si);
     this->setMovie(movie);
     movie->start();
     gifTime1->start(4000);
     lengqueTime->start(30000);
     Islengque=true;
    }
    //阶段二
    else if(goodSensitivity<=90){
     QMovie *movie = new QMovie("://quyudianji/quyudianji2.gif");
     QSize si (240,180);
     movie->setScaledSize(si);
     this->setMovie(movie);
     movie->start();
     gifTime1->start(4000);
     lengqueTime->start(30000);
     Islengque=true;
    }
    //阶段三
    else{
        QMovie *movie = new QMovie("://quyudianji/quyudianji3.gif");
        QSize si (200,115);
        movie->setScaledSize(si);
        this->setMovie(movie);
        movie->start();
        gifTime1->start(4000);
        lengqueTime->start(30000);
        Islengque=true;
    }
    }
    //生病或是饥饿
    else
    {
        //还敢动我扣你分
        query.prepare("update spirit1 set goodSensitivity = :goodSensitivity where number = :number");
        if(goodSensitivity>=2){
        query.bindValue(":goodSensitivity", goodSensitivity-2);
        query.bindValue(":number",NUM);
        query.exec();
        goodSensitivity = goodSensitivity -2;

    }
        QMovie *movie = new QMovie("://gongneng/shengqi.gif");
        QSize si (300,171);
        movie->setScaledSize(si);
        this->setMovie(movie);
        movie->start();
        gifTime1->start(4000);
        lengqueTime->start(30000);
        Islengque=true;
}
}
    else
    {
        QMessageBox::information(this,tr("提示"),tr("禁止无赖刷好感度，每次刷好感度请间隔30s"));
    }
}

void MyQLabel::mousePressEvent(QMouseEvent*)
{
    emit clicked();
}

void MyQLabel::upMode()
{
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int number1 = rec.indexOf("healthy");
    healthy= query.value(number1).toInt();
    int number2 = rec.indexOf("goodSensitivity");
    goodSensitivity= query.value(number2).toInt();
    int number3 = rec.indexOf("hungrySensitivity");
    hungrySensitivity= query.value(number3).toInt();
    }

    if(healthy==0||hungrySensitivity==0)
    {
        currentMode="DeadMode";
    }
    else if(healthy<60)
    {
        currentMode="SickMode";
    }
    else if(hungrySensitivity<60)
    {
        currentMode="HungryMode";
    }
    else
    {
        currentMode="UsualMode";
    }
}

void MyQLabel::Restore1(){
    upMode();
    if(currentMode=="DeadMode")
    {

        gifTime1->stop();
        QMovie *movie = new QMovie("://zhuangtai/siwang1.png");
        QSize si (224,168);
        movie->setScaledSize(si);
        this->setMovie(movie);
        movie->start();
    }
    else if (currentMode=="SickMode")
    {
        if(goodSensitivity<=50)
        {
            gifTime1->stop();
            QMovie *movie = new QMovie("://zhuangtai/ill1.gif");
            QSize si (168,177);
            movie->setScaledSize(si);
            this->setMovie(movie);
            movie->start();
        }
        else
        {
            gifTime1->stop();
            QMovie *movie = new QMovie("://zhuangtai/ill2.gif");
            QSize si (200,200);
            movie->setScaledSize(si);
            this->setMovie(movie);
            movie->start();
        }
    }
    else if(currentMode=="HungryMode")
    {
        if(goodSensitivity<=50)
        {
            gifTime1->stop();
            QMovie *movie = new QMovie("://zhuangtai/jie1.gif");
            QSize si (250,140);
            movie->setScaledSize(si);
            this->setMovie(movie);
            movie->start();
        }
        else
        {
            gifTime1->stop();
            QMovie *movie = new QMovie("://zhuangtai/jie2.gif");
            QSize si (200,200);
            movie->setScaledSize(si);
            this->setMovie(movie);
            movie->start();
        }
    }
    else if (currentMode=="UsualMode")
    {
        if(goodSensitivity<=60)
        {
            gifTime1->stop();
            QMovie *movie = new QMovie("://zhuangtai/zhengchang1.gif");
            QSize si (200,150);
            movie->setScaledSize(si);
            this->setMovie(movie);
            movie->start();
        }
        else if(goodSensitivity<=90)
        {
            gifTime1->stop();
            QMovie *movie = new QMovie("://zhuangtai/zhengchang2.gif");
            QSize si (240,135);
            movie->setScaledSize(si);
            this->setMovie(movie);
            movie->start();
        }
        else
        {
            gifTime1->stop();
            QMovie *movie = new QMovie("://zhuangtai/zhengchang3.gif");
            QSize si (200,125);
            movie->setScaledSize(si);
            this->setMovie(movie);
            movie->start();
        }
    }
}

void MyQLabel::setNum(QString NUM)
{
    this->NUM=NUM;
}

void MyQLabel::lengque(){
    Islengque=false;
}
