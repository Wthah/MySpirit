#include "food.h"
#include "ui_food.h"

food::food(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::food)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
    QPalette PAllbackground;
    QImage ImgAllbackground("://store/beijing.png");
    QImage fitimgpic=ImgAllbackground.scaled(978,325, Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}

food::~food()
{
    delete ui;
}

void food::set()
{
    //读取数据
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec1 = query.record();
    while(query.next()){
    rec1 = query.record();
    int number1 = rec1.indexOf("riceBall");
    riceBall= query.value(number1).toInt();
    int number2 = rec1.indexOf("spunSugar");
    spunSugar= query.value(number2).toInt();
    int number3 = rec1.indexOf("juice");
    juice= query.value(number3).toInt();
    int number4 = rec1.indexOf("apple");
    apple= query.value(number4).toInt();
    int number5 = rec1.indexOf("fuHuo");
    fuHuo = query.value(number5).toInt();

    //读入数据
    ui->rNum->setText("×"+QString::number(riceBall, 10));
    ui->jNum->setText("×"+QString::number(juice, 10));
    ui->aNum->setText("×"+QString::number(apple, 10));
    ui->sNum->setText("×"+QString::number(spunSugar, 10));
    ui->fNum->setText("×"+QString::number(fuHuo, 10));

    //将输入框设为只读
    ui-> rNum->setReadOnly(true);
    ui->jNum->setReadOnly(true);
    ui->aNum->setReadOnly(true);
    ui->sNum->setReadOnly(true);
    ui->fNum->setReadOnly(true);

    //设为无边框透明
    ui->rNum->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->jNum->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->aNum->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->sNum->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->fNum->setStyleSheet("background:transparent;border-width:0;border-style:outset");
}
}

//棉花糖
void food::on_sButton_clicked()
{
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec1 = query.record();
    while(query.next()){
    rec1 = query.record();
    int number1 = rec1.indexOf("hungrySensitivity");
    hungrySensitivity= query.value(number1).toInt();
    int number2 = rec1.indexOf("goodSensitivity");
    goodSensitivity= query.value(number2).toInt();
    int number3 = rec1.indexOf("spunSugar");
    spunSugar= query.value(number3).toInt();
    }
    if(spunSugar>=1){
    if(hungrySensitivity>=60)
    {

        query.prepare("update spirit1 set eating = :eating , goodSensitivity = :goodSensitivity , hungrySensitivity = :hungrySensitivity, spunSugar = :spunSugar where number = :number");
        if(shFlag==false){

        query.bindValue(":eating","://gongneng/shengqi.gif" );
        shFlag=true;
        sFlag=false;
        aFlag=false;
        aFlag=false;
        rFlag=false;
        }

        else
        {
            query.bindValue(":eating","://gongneng/shengqi.gif1" );
            shFlag=false;
        }
        if(goodSensitivity>=2)
        {
            qDebug()<<"wozai";
            query.bindValue(":goodSensitivity",goodSensitivity-2);
            query.bindValue(":number",NUM);
            if(hungrySensitivity<=90)
            query.bindValue(":hungrySensitivity",hungrySensitivity+10);
            else
            query.bindValue(":hungrySensitivity",100);

        }
        else
        {
            query.bindValue(":goodSensitivity",0);
            query.bindValue(":number",NUM);
            if(hungrySensitivity<=90)
            query.bindValue(":hungrySensitivity",hungrySensitivity+10);
            else
            query.bindValue(":hungrySensitivity",100);
        }
        query.bindValue(":spunSugar",spunSugar-1);

        query.exec();
        ui->sNum->setText("×"+QString::number(spunSugar-1, 10));
        this->close();
    }
    else
    {
        query.prepare("update spirit1 set eating = :eating , goodSensitivity = :goodSensitivity , hungrySensitivity = :hungrySensitivity ,spunSugar = :spunSugar where number = :number");
        if(sFlag==false){
        query.bindValue(":eating","://gongneng/spunSugar.gif" );
        sFlag=true;
        aFlag=false;
        shFlag=false;
        rFlag=false;
        jFlag=false;
        }
        else
        {
            query.bindValue(":eating","://gongneng/spunSugar.gif1" );
            sFlag=false;
        }
        if(goodSensitivity<=98)
        query.bindValue(":goodSensitivity",goodSensitivity+2);
        else
        query.bindValue(":goodSensitivity",100);
        query.bindValue(":number",NUM);
        if(hungrySensitivity<=90)
        query.bindValue(":hungrySensitivity",hungrySensitivity+10);
        else
        query.bindValue(":hungrySensitivity",100);
        query.bindValue(":spunSugar",spunSugar-1);
        query.exec();
        ui->sNum->setText("×"+QString::number(spunSugar-1, 10));
        this->close();
    }
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("道具不足，请去商店购买"));
    }
}

//饭团
void food::on_pushButton_2_clicked()
{
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec1 = query.record();
    while(query.next()){
    rec1 = query.record();
    int number1 = rec1.indexOf("hungrySensitivity");
    hungrySensitivity= query.value(number1).toInt();
    int number2 = rec1.indexOf("goodSensitivity");
    goodSensitivity= query.value(number2).toInt();
    int number3 = rec1.indexOf("riceBall");
    riceBall= query.value(number3).toInt();
    }
    if(riceBall>=1){
    if(hungrySensitivity>=60)
    {
        query.prepare("update spirit1 set eating = :eating , goodSensitivity = :goodSensitivity , hungrySensitivity = :hungrySensitivity ,riceBall = :riceBall where number = :number");
        if(shFlag==false){
        query.bindValue(":eating","://gongneng/shengqi.gif" );
        shFlag=true;
        sFlag=false;
        aFlag=false;
        aFlag=false;
        rFlag=false;
        }
        else
        {
            query.bindValue(":eating","://gongneng/shengqi.gif1" );
            shFlag=false;
        }
        if(goodSensitivity>=2)
        {
            query.bindValue(":goodSensitivity",goodSensitivity-2);
            query.bindValue(":number",NUM);
            if(hungrySensitivity<=70)
            query.bindValue(":hungrySensitivity",hungrySensitivity+30);
            else
            query.bindValue(":hungrySensitivity",100);
        }
        else
        {
            query.bindValue(":goodSensitivity",0);
            query.bindValue(":number",NUM);
            if(hungrySensitivity<=70)
            query.bindValue(":hungrySensitivity",hungrySensitivity+30);
            else
            query.bindValue(":hungrySensitivity",100);
        }
        query.bindValue("riceBall",riceBall-1);
        query.exec();
        ui->rNum->setText("×"+QString::number(riceBall-1, 10));
        this->close();
    }
    else
    {
        query.prepare("update spirit1 set eating = :eating , goodSensitivity = :goodSensitivity , hungrySensitivity = :hungrySensitivity ,riceBall = :riceBall where number = :number");
        if(rFlag==false){
        query.bindValue(":eating","://gongneng/riceBall.gif" );
        rFlag=true;
        aFlag=false;
        shFlag=false;
        sFlag=false;
        jFlag=false;
        }
        else
        {
            query.bindValue(":eating","://gongneng/riceBall.gif1" );
            rFlag=false;
        }

        if(goodSensitivity<=98)
        query.bindValue(":goodSensitivity",goodSensitivity+2);
        else
        query.bindValue(":goodSensitivity",100);
        query.bindValue(":number",NUM);
        if(hungrySensitivity<=70)
        query.bindValue(":hungrySensitivity",hungrySensitivity+30);
        else
        query.bindValue(":hungrySensitivity",100);
        query.bindValue("riceBall",riceBall-1);
        query.exec();
        ui->rNum->setText("×"+QString::number(riceBall-1, 10));
        this->close();
    }
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("道具不足，请去商店购买"));
        this->close();
    }
}

//饮料
void food::on_jButton_clicked()
{
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec1 = query.record();
    while(query.next()){
    rec1 = query.record();
    int number1 = rec1.indexOf("hungrySensitivity");
    hungrySensitivity= query.value(number1).toInt();
    int number2 = rec1.indexOf("goodSensitivity");
    goodSensitivity= query.value(number2).toInt();
    int number3 = rec1.indexOf("juice");
    juice= query.value(number3).toInt();
    }
    if(juice>=1){

    if(hungrySensitivity>=60)
    {
        query.prepare("update spirit1 set eating = :eating , goodSensitivity = :goodSensitivity , hungrySensitivity = :hungrySensitivity , juice = :juice where number = :number");
        if(shFlag==false){
        query.bindValue(":eating","://gongneng/shengqi.gif" );
        shFlag=true;
        sFlag=false;
        aFlag=false;
        aFlag=false;
        rFlag=false;
        }
        else
        {
            query.bindValue(":eating","://gongneng/shengqi.gif1" );
            shFlag=false;
        }
        if(goodSensitivity>=2)
        {
            query.bindValue(":goodSensitivity",goodSensitivity-2);
            query.bindValue(":number",NUM);
            if(hungrySensitivity<=80)
            query.bindValue(":hungrySensitivity",hungrySensitivity+20);
            else
            query.bindValue(":hungrySensitivity",100);
        }
        else
        {
            query.bindValue(":goodSensitivity",0);
            query.bindValue(":number",NUM);
            if(hungrySensitivity<=80)
            query.bindValue(":hungrySensitivity",hungrySensitivity+20);
            else
            query.bindValue(":hungrySensitivity",100);
        }
        query.bindValue(":juice",juice-1);
        query.exec();
        ui->jNum->setText("×"+QString::number(juice-1, 10));
        this->close();
    }
    else
    {
        query.prepare("update spirit1 set eating = :eating , goodSensitivity = :goodSensitivity , hungrySensitivity = :hungrySensitivity , juice = :juice where number = :number");
        if(jFlag==false){
        query.bindValue(":eating","://gongneng/juice.gif" );
        jFlag=true;
        aFlag=false;
        shFlag=false;
        rFlag=false;
        sFlag=false;
        }
        else
        {
            query.bindValue(":eating","://gongneng/juice.gif1" );
            jFlag=false;
        }

        if(goodSensitivity<=98)
        query.bindValue(":goodSensitivity",goodSensitivity+2);
        else
        query.bindValue(":goodSensitivity",100);
        query.bindValue(":number",NUM);
        if(hungrySensitivity<=80)
        query.bindValue(":hungrySensitivity",hungrySensitivity+20);
        else
        query.bindValue(":hungrySensitivity",100);
        query.bindValue(":juice",juice-1);
        query.exec();
        ui->jNum->setText("×"+QString::number(juice-1, 10));
        this->close();
    }
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("道具不足，请去商店购买"));
        this->close();
    }
}

//苹果
void food::on_aButton_clicked()
{
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec1 = query.record();
    while(query.next()){
    rec1 = query.record();
    int number1 = rec1.indexOf("hungrySensitivity");
    hungrySensitivity= query.value(number1).toInt();
    int number2 = rec1.indexOf("goodSensitivity");
    goodSensitivity= query.value(number2).toInt();
    int number3 = rec1.indexOf("apple");
    apple= query.value(number3).toInt();
    }
    if(apple>=1){
    if(hungrySensitivity>=60)
    {
        query.prepare("update spirit1 set eating = :eating , goodSensitivity = :goodSensitivity , hungrySensitivity = :hungrySensitivity ,apple = :apple where number = :number");
        if(shFlag==false){
        query.bindValue(":eating","://gongneng/shengqi.gif" );
        shFlag=true;
        sFlag=false;
        aFlag=false;
        aFlag=false;
        rFlag=false;
        }
        else
        {
            query.bindValue(":eating","://gongneng/shengqi.gif1" );
            shFlag=false;
        }
        if(goodSensitivity>=2)
        {
            query.bindValue(":goodSensitivity",goodSensitivity-2);
            query.bindValue(":number",NUM);
            if(hungrySensitivity<=80)
            query.bindValue(":hungrySensitivity",hungrySensitivity+20);
            else
            query.bindValue(":hungrySensitivity",100);
        }
        else
        {
            query.bindValue(":goodSensitivity",0);
            query.bindValue(":number",NUM);
            if(hungrySensitivity<=80)
            query.bindValue(":hungrySensitivity",hungrySensitivity+20);
            else
            query.bindValue(":hungrySensitivity",100);
        }
        query.bindValue(":apple",apple-1);
        query.exec();
        ui->aNum->setText("×"+QString::number(apple-1, 10));
        this->close();
    }
    else
    {
        query.prepare("update spirit1 set eating = :eating , goodSensitivity = :goodSensitivity , hungrySensitivity = :hungrySensitivity ,apple = :apple where number = :number");
        if(aFlag==false){
        query.bindValue(":eating","://gongneng/aplle.gif" );
        aFlag=true;
        sFlag=false;
        shFlag=false;
        rFlag=false;
        jFlag=false;
        }
        else
        {
            query.bindValue(":eating","://gongneng/aplle.gif1" );
            aFlag=false;
        }

        if(goodSensitivity<=98)
        query.bindValue(":goodSensitivity",goodSensitivity+2);
        else
        query.bindValue(":goodSensitivity",100);
        query.bindValue(":number",NUM);
        if(hungrySensitivity<=80)
        query.bindValue(":hungrySensitivity",hungrySensitivity+20);
        else
        query.bindValue(":hungrySensitivity",100);
        query.bindValue(":apple",apple-1);
        query.exec();
        ui->aNum->setText("×"+QString::number(apple-1, 10));
        this->close();
    }
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("道具不足，请去商店购买"));
        this->close();
    }
}

//复活道具
void food::on_fButton_clicked()
{
    QMessageBox::information(this,tr("提示"),tr("请使用复活按钮来使用道具"));
    this->close();
}

void food::setNum(QString NUM)
{
    this->NUM=NUM;
}
