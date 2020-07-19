#include "registerwidget.h"
#include "ui_registerwidget.h"

registerWidget::registerWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    //窗口大小限定
    this->setWindowTitle("注册");
    this->setMaximumSize(413,624);
    this->setMinimumSize(413,624);
    //输入框处理
    ui->rNumText->setPlaceholderText(" 请输入注册账号(10位数字)");
    ui->rPasstext->setPlaceholderText(" 请输入密码(6-14位字符)");
    ui->rAgainpasstext->setPlaceholderText(" 请再次输入密码");
    ui->rNumText->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
    ui->rPasstext->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
    ui->rAgainpasstext->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
    //背景设置
    setAutoFillBackground(true);
    QPalette PAllbackground;
    QImage ImgAllbackground("://jiemian/zhuce.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(413,624, Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}

registerWidget::~registerWidget()
{
    delete this;
    delete ui;
}

void registerWidget::on_confirm_clicked()
{
    NUM = ui->rNumText->text();
    PASS=ui->rPasstext->text();
    PASS1=ui->rAgainpasstext->text();
    //账号不符合要求
    if(testNumber(NUM)==-1)
    {
        QMessageBox::information(this, tr("Error"),
        tr("Please enter a ten-digit account number."));
        return;
    }
    //密码不符合要求
    if(testPass(PASS)==-1)
    {
        QMessageBox::information(this, tr("Error"),
        tr("Please enter a password with 6 to 14 characters."));
        return;
    }
    //两次密码不相同
    if(PASS!=PASS1)
    {
        QMessageBox::information(this, tr("Error"),
        tr("Please enter the same password."));
    }
    else
    {
        //如果表不存在则创建表
        if(IsTableExist(query,"spirit1")==false)
        {

            bool success = query.exec("create table spirit1 (number varchar primary key,PASS varchar,name varchar,type varchar,healthy int,goodSensitivity int,hungrySensitivity int,age int,weight int,money int,apple int,spunSugar int,riceBall int,juice int,fuHuo int,path varchar,eating varchar)");
            if(success){
                query.prepare("INSERT INTO  SPIRIT1(number, PASS, name, type,healthy,goodSensitivity,hungrySensitivity,age,weight,money,apple,spunSugar,riceBall,juice,fuHuo,eating) VALUES (:number, :PASS, :name, :type,:healthy,:goodSensitivity,:hungrySensitivity,:age,:weight,:money,:apple,:spunSugar,:riceBall,:juice,:fuHuo,:path,:eating)");
                query.bindValue(":number", "");	//给每个插入值标识符设定具体值
                query.bindValue(":PASS", "");
                query.bindValue(":name", "");
                query.bindValue(":type", "pika");
                query.bindValue(":healthy", 1);
                query.bindValue(":goodSensitivity", 0);
                query.bindValue(":hungrySensitivity", 0);
                query.bindValue(":age", 1);
                query.bindValue(":weight",1);
                query.bindValue(":money",0);
                query.bindValue(":apple",0);
                query.bindValue(":spunSugar",0);
                query.bindValue(":riceBall",0);
                query.bindValue(":juice",0);
                query.bindValue(":fuHuo",0);
                query.bindValue(":path","://beijing/beijing2.png");
                query.bindValue("eating","");
                query.exec();
           }
            else
            {
                qDebug() << "创建表失败";
            }
        }

        query.prepare("SELECT  * FROM spirit WHERE number = :number") ;
        query.bindValue(":number",NUM);
        query.exec();
        QSqlRecord rec = query.record();
        while(query.next()){
        rec = query.record();
        int number2 = rec.indexOf("number");
        num= query.value(number2).toString();
        }
        //判断账号是否已经注册
        if(num==NUM)
        {
            QMessageBox::information(this, tr("Error"),
            tr("The number has been register."));
        }
        if(num!=NUM)
         {
            QMessageBox::information(this, tr("Register Successful"),
            tr("\"%1\" Register Successful.").arg(NUM));
         //未注册导入数据库
                query.prepare("INSERT INTO  spirit1(number, PASS, name, type,healthy,goodSensitivity,hungrySensitivity,age,weight,money,apple,spunSugar,riceBall,juice,fuHuo,path,eating)" "VALUES (:number, :PASS, :name, :type,:healthy,:goodSensitivity,:hungrySensitivity,:age,:weight,:money,:apple,:spunSugar,:riceBall,:juice,:fuHuo,:path,:eating)");
                query.bindValue(":number", NUM);	//给每个插入值标识符设定具体值
                query.bindValue(":PASS", PASS);
                query.bindValue(":name", "");
                query.bindValue(":type", "pika");
                query.bindValue(":healthy", 100);
                query.bindValue(":goodSensitivity", 0);
                query.bindValue(":hungrySensitivity", 100);
                query.bindValue(":age", 1);
                query.bindValue(":weight",1);
                query.bindValue(":money",0);
                query.bindValue(":apple",0);
                query.bindValue(":spunSugar",0);
                query.bindValue(":riceBall",0);
                query.bindValue(":juice",0);
                query.bindValue(":fuHuo",0);
                query.bindValue(":path","://beijing/beijing2.png");
                query.bindValue(":eating","");
                query.exec();
                this->close();

            }
        }
    }
//表是否存在
bool registerWidget::IsTableExist(QSqlQuery &query,QString table)
{
   QString sql = QString("select * from sqlite_master where name='%1'").arg(table);
   query.exec(sql);
   return query.next();
}
//判断密码
int registerWidget::testPass(QString pass)
{
    QByteArray ba = pass.toLatin1();
    const char*s = ba.data();
    int i=0;

    while(*s)
    {
        s++;
        i++;
    }
    if(i<6||i>14)
    {
        //不符合要求
        return -1;
    }
    else
        {
        //纯数字且符合要求
        return 0;
    }
}
//判断账号
int registerWidget::testNumber(QString number)
{
    QByteArray ba = number.toLatin1();
    const char*s = ba.data();
    int i=0;

    while(*s&&*s>='0'&&*s<='9')
    {
        s++;
        i++;
    }

    if(*s||i!=10)
    {
        //不符合要求
        return -1;
    }
    else
        {
        //符合要求
        return 0;
    }
}
