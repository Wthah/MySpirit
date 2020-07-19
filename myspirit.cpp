#include "myspirit.h"
#include "ui_myspirit.h"

MySpirit::MySpirit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MySpirit)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":myIco/mySpirit.ico")); //图标
    ui->passwordText->setEchoMode(QLineEdit::Password); //设置密码
    //限定窗口大小
    ui->centralWidget->setMaximumSize(580,335);
    ui->centralWidget->setMinimumSize(580,335);
    ui->Register->setFlat(true);
    //对界面处理
    ui->numberText->setPlaceholderText(" 请输入账号");
    ui->passwordText->setPlaceholderText(" 请输入密码");
    ui->numberText->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
    ui->passwordText->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
    ui->logIn->setStyleSheet("border:2px groove rgb(163, 221, 137);border-radius:10px;padding:2px 4px;color:black;font: 75 11pt setBold");
    //设置背景图片
    setAutoFillBackground(true);
    QPalette PAllbackground;
    QImage ImgAllbackground("://jiemian/denglu.png");
    QImage fitimgpic=ImgAllbackground.scaled(580,335, Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}

MySpirit::~MySpirit()
{
    delete ui;
    delete this;
}


void MySpirit::on_Register_clicked()
{
     RegisterWidget->setWindowTitle("注册");
     RegisterWidget->show();
}

void MySpirit::on_logIn_clicked()
{

    //登录验证
    NUM=ui->numberText->text();
    PASS=ui->passwordText->text();
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int name1 = rec.indexOf("name");
    int number2 = rec.indexOf("number");
    int number1 = rec.indexOf("PASS");
    pass = query.value(number1).toString();
    num= query.value(number2).toString();
    name = query.value(name1).toString();
    }
    //账号不存在
    if(num!=NUM)
    {
        QMessageBox::information(this, tr("Error"),
        tr("The number hasn't been register."));
    }
    else if(num==NUM)
    {
        //密码不对
        if(pass!=PASS)
        {
            QMessageBox::information(this, tr("Error"),
            tr("Password error."));

        }
        else
        {
            //取名界面
            if(name==""){
              NameWidget->setWindowTitle("欢迎进入MySpirit");
              NameWidget->show();
              NameWidget->setNum(NUM);
              this->close();
            }
            else{
                //宠物窗口
                petWidget *PetWidget = new petWidget;
                PetWidget->setWindowTitle("My Spirit");
                PetWidget->setNum(NUM);
                PetWidget->petWidget::set();
                PetWidget->show();
                this->close();
            }
        }
    }
}





