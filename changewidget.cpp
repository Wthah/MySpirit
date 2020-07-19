#include "changewidget.h"
#include "ui_changewidget.h"

changeWidget::changeWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeWidget)
{
    this->setWindowTitle("Change");
    //设置背景图片
    setAutoFillBackground(true);
    QPalette PAllbackground;
    QImage ImgAllbackground("://beijing/beijing.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(1188,815, Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);

    ui->setupUi(this);
    //按钮图片展示
    QIcon button_ico("://beijing/beijing1.jpg");
    ui->imageButton->setIcon(button_ico);
    ui->imageButton->setIconSize(QSize(321,211));

    QIcon button_ico2("://beijing/beijing2.png");
    ui->imageButton1->setIcon(button_ico2);
    ui->imageButton1->setIconSize(QSize(321,211));

    QIcon button_ico3("://beijing/beijing3.jpg");
    ui->imageButton1_2->setIcon(button_ico3);
    ui->imageButton1_2->setIconSize(QSize(321,211));

    QIcon button_ico4("://beijing/beijing4.jpg");
    ui->imageButton1_3->setIcon(button_ico4);
    ui->imageButton1_3->setIconSize(QSize(321,211));

    QIcon button_ico5("://beijing/beijing5.jpg");
    ui->imageButton1_4->setIcon(button_ico5);
    ui->imageButton1_4->setIconSize(QSize(321,211));

    QIcon button_ico6("://beijing/beijing6.jpg");
    ui->imageButton1_5->setIcon(button_ico6);
    ui->imageButton1_5->setIconSize(QSize(321,211));

    QIcon button_ico7("://beijing/beijing7.png");
    ui->imageButton1_6->setIcon(button_ico7);
    ui->imageButton1_6->setIconSize(QSize(321,211));

    QIcon button_ico8("://beijing/beijing8.jpg");
    ui->imageButton1_7->setIcon(button_ico8);
    ui->imageButton1_7->setIconSize(QSize(321,211));

    QIcon button_ico9("://beijing/beijing9.jpg");
    ui->imageButton1_8->setIcon(button_ico9);
    ui->imageButton1_8->setIconSize(QSize(321,211));

}

changeWidget::~changeWidget()
{
    delete ui;
    delete this;
}

void changeWidget::on_imageButton_clicked()
{
    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path","://beijing/beijing1.jpg" );
    query.bindValue(":number",NUM);
    query.exec();
    this->close();
}

void changeWidget::on_imageButton1_clicked()
{
    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path","://beijing/beijing2.png" );
    query.bindValue(":number",NUM);
    query.exec();
    this->close();
}

void changeWidget::on_imageButton1_4_clicked()
{
    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path","://beijing/beijing5.jpg" );
    query.bindValue(":number",NUM);
    query.exec();
    this->close();
}

void changeWidget::on_imageButton1_5_clicked()
{
    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path","://beijing/beijing6.jpg" );
    query.bindValue(":number",NUM);
    query.exec();
    this->close();
}

void changeWidget::on_imageButton1_2_clicked()
{
    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path","://beijing/beijing3.jpg" );
    query.bindValue(":number",NUM);
    query.exec();
    this->close();
}

void changeWidget::on_imageButton1_3_clicked()
{
    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path","://beijing/beijing4.jpg" );
    query.bindValue(":number",NUM);
    query.exec();
    this->close();
}

void changeWidget::on_imageButton1_6_clicked()
{
    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path","://beijing/beijing7.png" );
    query.bindValue(":number",NUM);
    query.exec();
    this->close();
}

void changeWidget::on_imageButton1_7_clicked()
{
    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path","://beijing/beijing8.jpg" );
    query.bindValue(":number",NUM);
    query.exec();
    this->close();
}

void changeWidget::on_imageButton1_8_clicked()
{
    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path","://beijing/beijing9.jpg" );
    query.bindValue(":number",NUM);
    query.exec();
    this->close();
}

void changeWidget::setNum(QString NUM)
{
    this->NUM=NUM;
}
