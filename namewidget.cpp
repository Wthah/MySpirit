#include "namewidget.h"
#include "ui_namewidget.h"

nameWidget::nameWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nameWidget)
{
    ui->setupUi(this);

    this->setWindowTitle("取名");
    //设置输入框
    ui->lineEdit->setPlaceholderText(" 1-8个字符");
    ui->lineEdit->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
    setAutoFillBackground(true);
    //设置背景图
    QPalette PAllbackground;
    QImage ImgAllbackground("://beijing/nameBeijing.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(362,512, Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}

nameWidget::~nameWidget()
{
    delete ui;
    delete this;
}
//开始游戏按钮
void nameWidget::on_start_clicked()
{
    //昵称不符合要求
    if(testName(ui->lineEdit->text())==-1)
    {
        QMessageBox::information(this,tr("error"),tr("Please enter a name with 1 to 8 characters"));
        return;
    }
    //否则导入数据库
    query.prepare("update spirit1 set name = :name where number = :number");
    query.bindValue(":name",ui->lineEdit->text());
    query.bindValue(":number",NUM);
    query.exec();
    //打开宠物界面，完成宠物界面布局
    petWidget *PetWidget = new petWidget;
    PetWidget->setWindowTitle("My Spirit");
    PetWidget->setNum(NUM);
    PetWidget->petWidget::set();
    PetWidget->show();
    this->close();
}
//检测名字是否符合标准
int nameWidget::testName(QString Name)
{
    QByteArray ba = Name.toLatin1();
    const char*s = ba.data();
    int i=0;
    while(*s)
    {
        s++;
        i++;
    }
    if(i>8||i<1)
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

void nameWidget::setNum(QString NUM){
    this->NUM=NUM;
}



