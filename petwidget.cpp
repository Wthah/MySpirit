#include "petwidget.h"
#include "ui_petwidget.h"

petWidget::petWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::petWidget)
{
    ui->setupUi(this);

}

petWidget::~petWidget()
{
    delete this;
    delete hungryTime;
    delete ageTime;
    delete weightTime;
    delete healthyTime;
    delete moneyTime ;
    delete moneyTime1 ;
    delete pathTime ;
    delete goodSensitivityTime;
    delete  hungryTime1;
    delete jiankongTime ;
    delete gifTime;
    delete eatingTime ;
    delete ui;
}

void petWidget::set(){
    //读取数据
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec1 = query.record();
    while(query.next()){
    rec1 = query.record();
    int number2 = rec1.indexOf("goodSensitivity");
    goodSensitivity1= query.value(number2).toInt();
    int number3 = rec1.indexOf("hungrySensitivity");
    hungrySensitivity1= query.value(number3).toInt();
    int number4 = rec1.indexOf("age");
    age1= query.value(number4).toInt();
    int number5 = rec1.indexOf("weight");
    weight1= query.value(number5).toInt();
    int number6 = rec1.indexOf("healthy");
    healthy1= query.value(number6).toInt();
    int number7 = rec1.indexOf("name");
    name1= query.value(number7).toString();
    int number8 = rec1.indexOf("money");
    money1 = query.value(number8).toInt();
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
    int number14 = rec1.indexOf("eating");
    eating = query.value(number14).toString();

}

    //读入数据到输入框
    ui->gsEdit->setText(QString::number(goodSensitivity1, 10));
    ui->hsEdit->setText(QString::number(hungrySensitivity1, 10));
    ui->aEdit->setText(QString::number(age1, 10));
    ui->wEdit->setText(QString::number(weight1, 10));
    ui->hEdit->setText(QString::number(healthy1, 10));
    ui->mEdit->setText(QString::number(money1,10));
    ui->mEdit_2->setText(name1);

    //将输入框设为只读
    ui-> gsEdit->setReadOnly(true);
    ui->hsEdit->setReadOnly(true);
    ui->aEdit->setReadOnly(true);
    ui->wEdit->setReadOnly(true);
    ui->hEdit->setReadOnly(true);
    ui->mEdit_2->setReadOnly(true);
    ui->mEdit->setReadOnly(true);

    //宠物图片添加
     my_label = new MyQLabel("",this);
     my_label->setGeometry(QRect(390,280,281,211));
     my_label->setNum(NUM);
     putImage(my_label);

    //设置按钮可用性
    upMode();
    upButton();
    //设置定时器
    hungryTime=new QTimer(this);         //每15秒降1饥饿度
    ageTime=new QTimer(this);              //每1分钟加一岁
    weightTime=new QTimer(this);         //每1分钟加一kg
    healthyTime=new QTimer(this);        //每15秒抽一次
    moneyTime = new  QTimer(this);       //每10秒一金币
    moneyTime1 = new QTimer(this);      //每0.1秒读取一次数据库（由于商店和治疗花销为了同步）
    pathTime = new QTimer(this);          //点击换场后每0.1秒读取一次背景图路径，路径不同则换背景，换场关闭close
    goodSensitivityTime = new QTimer(this);    //每0.1秒读取一次好感度（由于图片和好感度体现需要）
    hungryTime1 = new QTimer(this);     //点击喂食后每0.1秒读取一次数据库
    jiankongTime = new QTimer(this);    //每0.1秒读取一次状态，状态发生改变则换图片
    gifTime = new QTimer(this);            //暂时的gif图调用显示4秒然后恢复
    eatingTime = new QTimer(this);       //点击喂食后调用每0.1秒读取一次，图片路径不同则调用同时关闭jiankongTime，结束后关闭这个定时器开启jiankongTime
    lengqueTime = new QTimer(this);     //点击fun后运行30秒防止无赖刷好感度
    healthyTime1 = new QTimer(this);

    hungryTime->start(15000);
    ageTime->start(60000);
    weightTime->start(60000);
    healthyTime->start(15000);
    moneyTime->start(10000);
    goodSensitivityTime->start(100);
    jiankongTime ->start(100);
    hungryTime1 ->start(10);
    healthyTime1->start(10);


    //定时器槽
    connect(hungryTime,SIGNAL(timeout()),this,SLOT(upHungry()));
    connect(ageTime,SIGNAL(timeout()),this,SLOT(upAge()));
    connect(weightTime,SIGNAL(timeout()),this,SLOT(upWeight()));
    connect(healthyTime,SIGNAL(timeout()),this,SLOT(upHealthy()));
    connect(moneyTime,SIGNAL(timeout()),this,SLOT(upMoney()));
    connect(moneyTime1,SIGNAL(timeout()),this,SLOT(upMoney1()));
    connect(pathTime,SIGNAL(timeout()),this,SLOT(upPath()));
    connect(hungryTime1,SIGNAL(timeout()),this,SLOT(upHungry1()));
    connect(goodSensitivityTime,SIGNAL(timeout()),this,SLOT(upgoodSensitivity()));
    connect(jiankongTime,SIGNAL(timeout()),this,SLOT(jiankong()));
    connect(gifTime,SIGNAL(timeout()),this,SLOT(restore()));
    connect(eatingTime,SIGNAL(timeout()),this,SLOT(eat()));
    connect(lengqueTime,SIGNAL(timeout()),this,SLOT(lengque()));
    connect(healthyTime1,SIGNAL(timeout()),this,SLOT(upHealthy1()));

    //设置最初背景图
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int path1 = rec.indexOf("path");
    path = query.value(path1).toString();
    }
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                         QBrush(QPixmap(path).scaled( // 缩放背景图.
                                 this->size(),
                                Qt::IgnoreAspectRatio,
                                Qt::SmoothTransformation))); // 使用平滑的缩放方式
    this->setPalette(palette); // 至此, 已给widget加上了背景图.

    //设置背景音乐
//    QSound *startsound=new QSound(":/qss/backgroundmusic.wav",this);
//    startsound->play();//
//    startsound->setLoops(-1);

}
//商店
void petWidget::on_storeButton_clicked()
{
    storeWidget *StoreWidget = new storeWidget;
    StoreWidget->setWindowTitle("My Store");
    StoreWidget->setNum(NUM);
    //商店基本设置
    StoreWidget->storeWidget::set();
    StoreWidget->show();
    //开始读取主页面实时显示金币数目
    moneyTime1->start(10);
}
//嬉戏
void petWidget::on_Fun_clicked()
{
    //判断当前状态
    upMode();
    //普通状态加好感度
    if(isLenque==false){
    if(currentMode=="UsualMode")
    {
        query.prepare("update spirit1 set goodSensitivity = :goodSensitivity where number = :number");
        if(goodSensitivity1<100){
        query.bindValue(":goodSensitivity", goodSensitivity1+1);
        query.bindValue(":number",NUM);
        query.exec();
        goodSensitivity1 = goodSensitivity1 +1;
        }
        else
        {
            //分满了不做任何操作
        }

        //不同好感度不同的反应分为三个阶段
        //阶段一
        if(goodSensitivity1<=60){
         QMovie *movie = new QMovie("://gongneng/fun1.gif");
         QSize si (224,120);
         movie->setScaledSize(si);
         my_label->setMovie(movie);
         movie->start();
         jiankongTime->stop();
         gifTime->start(4000);
         isLenque=true;
         lengqueTime->start(30000);
        }
        //阶段2
        else if(goodSensitivity1<=90){
         QMovie *movie = new QMovie("://gongneng/fun2.gif");
         QSize si (245,200);
         movie->setScaledSize(si);
         my_label->setMovie(movie);
         movie->start();
         jiankongTime->stop();
         gifTime->start(4000);
         isLenque=true;
         lengqueTime->start(30000);
        }
        //阶段三
        else{
            QMovie *movie = new QMovie("://gongneng/fun3.gif");
            QSize si (270,152);
            movie->setScaledSize(si);
            my_label->setMovie(movie);
            movie->start();
            jiankongTime->stop();
            gifTime->start(4000);
            isLenque=true;
            lengqueTime->start(30000);
        }
    }

    //处于生病或饥饿状态不想进行玩乐
    else
    {
        //还敢动我扣你分
        query.prepare("update spirit1 set goodSensitivity = :goodSensitivity where number = :number");
        if(goodSensitivity1>=2){
        query.bindValue(":goodSensitivity", goodSensitivity1-2);
        query.bindValue(":number",NUM);
        query.exec();
        goodSensitivity1 = goodSensitivity1 -2;
    }
        QMovie *movie = new QMovie("://gongneng/shengqi.gif");
        QSize si (300,171);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
        isLenque=true;
        lengqueTime->start(30000);
}
}
    else
    {
        QMessageBox::information(this,tr("提示"),("禁止无赖刷好感度，每次刷好感度请间隔30秒"));
    }
}
//喂食
void petWidget::on_Food_clicked()
{
    foodWidget->setNum(NUM);
    foodWidget->food::set();
    foodWidget->setWindowTitle("My Food");
    foodWidget->show();
    eatingTime->start(10);
}
//复活
void petWidget::on_Resurrection_clicked()
{
    int ret = QMessageBox::warning(this,"提示","是否花费一个复活道具复活你的宠物（亲密度减20，健康值、饥饿度恢复为80，体重，年龄不变）?", QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
        //获取复活道具个数
        query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
        query.bindValue(":number",NUM);
        query.exec();
        QSqlRecord rec = query.record();
        while(query.next()){
        rec = query.record();
        int fuHuo1 = rec.indexOf("fuHuo");
        fuHuo = query.value(fuHuo1).toInt();
        }
        //道具足够
        if(fuHuo>=1){
        query.prepare("update spirit1 set fuHuo = :fuHuo, healthy = :healthy, hungrySensitivity= :hungrySensitivity, goodSensitivity = :goodSensitivity where number = :number");
        query.bindValue(":fuHuo",fuHuo-1);
        query.bindValue(":healthy",80);
        query.bindValue(":hungrySensitivity",80);
        //好感度大于20减20
        if(goodSensitivity1>=20)
        {
            query.bindValue(":goodSensitivity",goodSensitivity1-20);
            query.bindValue(":number",NUM);
            query.exec();
            fuHuo=fuHuo-1;
            upHealthy1();
            upHungry1();
        }
        //不足减为0
        else
        {
            query.bindValue(":goodSensitivity",0);
            query.bindValue(":number",NUM);
            query.exec();
            fuHuo=fuHuo-1;
            upHealthy1();
            upHungry1();
        }
       }
        //道具不足
        else
        {
            QMessageBox::information(this,tr("提示"),tr("道具不足，请到商店购买道具"));
        }
    }
}
//治疗
void petWidget::on_Cure_clicked()
{
    int ret = QMessageBox::warning(this,"提示","是否花费100金币治疗你的宠物（健康值加40）?", QMessageBox::Yes | QMessageBox::No);
    //点击yes
    if(ret == QMessageBox::Yes)
    {
        if(money1>=100){
        QMovie *movie = new QMovie("://gongneng/Cure.png");
        QSize si (300,300);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
        query.prepare("update spirit1 set money = :money, healthy = :healthy where number = :number");
        query.bindValue(":money",money1-100);
        query.bindValue(":healthy",healthy1+40);
        query.bindValue(":number",NUM);
        query.exec();
        //进行一次更新
        upMoney1();
        upHealthy1();
        }
        else
        {
            QMessageBox::information(this,tr("提示"),tr("金币不足,可以通过游戏获得."));
        }
    }

}
//换场
void petWidget::on_changeButton_clicked()
{
    ChangeWidget->show();
    ChangeWidget->setNum(NUM);
    pathTime->start(10);
}
//状态
void petWidget::upMode()
{
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int number1 = rec.indexOf("healthy");
    healthy1= query.value(number1).toInt();
    int number2 = rec.indexOf("goodSensitivity");
    goodSensitivity1= query.value(number2).toInt();
    int number3 = rec.indexOf("hungrySensitivity");
    hungrySensitivity1= query.value(number3).toInt();

    //实现类似于好感度槽饥饿度槽健康度槽的Label显示与隐藏
    if(goodSensitivity1==0){
        ui->gsLabel1->close();
        ui->gsLabel2->close();
        ui->gsLabel3->close();
        ui->gsLabel4->close();
        ui->gsLabel5->close();
      }
     else if(goodSensitivity1<=20){
        ui->gsLabel1->show();
        ui->gsLabel2->close();
        ui->gsLabel3->close();
        ui->gsLabel4->close();
        ui->gsLabel5->close();
      }
     else if(goodSensitivity1<=40){
        ui->gsLabel1->show();
        ui->gsLabel2->show();
        ui->gsLabel3->close();
        ui->gsLabel4->close();
        ui->gsLabel5->close();
      }
     else if(goodSensitivity1<=60){
        ui->gsLabel1->show();
        ui->gsLabel2->show();
        ui->gsLabel3->show();
        ui->gsLabel4->close();
        ui->gsLabel5->close();
      }
     else if(goodSensitivity1<=80){
        ui->gsLabel1->show();
        ui->gsLabel2->show();
        ui->gsLabel3->show();
        ui->gsLabel4->show();
        ui->gsLabel5->close();
      }
     else if(goodSensitivity1<=100){
        ui->gsLabel1->show();
        ui->gsLabel2->show();
        ui->gsLabel3->show();
        ui->gsLabel4->show();
        ui->gsLabel5->show();
      }

    if(hungrySensitivity1==0){
        ui->hsLabel1->close();
        ui->hsLabel2->close();
        ui->hsLabel3->close();
        ui->hsLabel4->close();
        ui->hsLabel5->close();
     }
     else if(hungrySensitivity1<=20){
        ui->hsLabel1->show();
        ui->hsLabel2->close();
        ui->hsLabel3->close();
        ui->hsLabel4->close();
        ui->hsLabel5->close();
    }
    else if(hungrySensitivity1<=40){
        ui->hsLabel1->show();
        ui->hsLabel2->show();
        ui->hsLabel3->close();
        ui->hsLabel4->close();
        ui->hsLabel5->close();
    }
    else if(hungrySensitivity1<=60){
        ui->hsLabel1->show();
        ui->hsLabel2->show();
        ui->hsLabel3->show();
        ui->hsLabel4->close();
        ui->hsLabel5->close();
    }
    else if(hungrySensitivity1<=80){
        ui->hsLabel1->show();
        ui->hsLabel2->show();
        ui->hsLabel3->show();
        ui->hsLabel4->show();
        ui->hsLabel5->close();
    }
    else if(hungrySensitivity1<=100){
        ui->hsLabel1->show();
        ui->hsLabel2->show();
        ui->hsLabel3->show();
        ui->hsLabel4->show();
        ui->hsLabel5->show();
    }

    if(healthy1==0){
        ui->hLabel1->close();
        ui->hLabel2->close();
        ui->hLabel3->close();
        ui->hLabel4->close();
        ui->hLabel5->close();
     }
     else if(healthy1<=20){
        ui->hLabel1->show();
        ui->hLabel2->close();
        ui->hLabel3->close();
        ui->hLabel4->close();
        ui->hLabel5->close();
     }
     else if(healthy1<=40){
        ui->hLabel1->show();
        ui->hLabel2->show();
        ui->hLabel3->close();
        ui->hLabel4->close();
        ui->hLabel5->close();
     }
     else if(healthy1<=60){
        ui->hLabel1->show();
        ui->hLabel2->show();
        ui->hLabel3->show();
        ui->hLabel4->close();
        ui->hLabel5->close();
    }
    else if(healthy1<=80){
        ui->hLabel1->show();
        ui->hLabel2->show();
        ui->hLabel3->show();
        ui->hLabel4->show();
        ui->hLabel5->close();
     }
     else if(healthy1<=100){
        ui->hLabel1->show();
        ui->hLabel2->show();
        ui->hLabel3->show();
        ui->hLabel4->show();
        ui->hLabel5->show();
    }
    }

    //判断当前状态
    if(healthy1==0||hungrySensitivity1==0)
    {
        currentMode="DeadMode";
    }
    else if(healthy1<60)
    {
        currentMode="SickMode";
    }
    else if(hungrySensitivity1<60)
    {
        currentMode="HungryMode";
    }
    else
    {
        currentMode="UsualMode";
    }

}
//按钮可用性设置在每个与健康和饥饿的地方出现
void petWidget::upButton()
{
    if(currentMode=="DeadMode")
    {
        ui->Cure->setEnabled(false);
        ui->Resurrection->setEnabled(true);
        ui->Food->setEnabled(false);
        ui->Fun->setEnabled(false);
    }

    else if(currentMode=="SickMode")
    {
        ui->Cure->setEnabled(true);
        ui-> Resurrection->setEnabled(false);
        ui->Food->setEnabled(true);
        ui->Fun->setEnabled(true);
    }

    else if(currentMode=="HungryMode")
    {
        ui->Cure->setEnabled(false);
        ui->Resurrection->setEnabled(false);
        ui->Food->setEnabled(true);
        ui->Fun->setEnabled(true);
    }

    else
    {
        ui->Cure->setEnabled(false);
        ui->Resurrection->setEnabled(false);
        ui->Food->setEnabled(true);
        ui->Fun->setEnabled(true);
    }
}
//更新饥饿值-1
void petWidget::upHungry(){
    //读取原本的饥饿度
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int hungrySensitivity2 = rec.indexOf("hungrySensitivity");
    hungrySensitivity1 = query.value(hungrySensitivity2).toInt();
    }
    if(hungrySensitivity1>0&&currentMode!="DeadMode"){
    query.prepare("update spirit1 set hungrySensitivity = :hungrySensitivity where number = :number");
    query.bindValue(":hungrySensitivity",hungrySensitivity1-1);
    query.bindValue(":number",NUM);
    query.exec();
    ui->hsEdit->setText(QString::number(hungrySensitivity1-1, 10));
    }
}
//更新年龄+1
void petWidget::upAge(){
    //读取原本的年龄
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int age2 = rec.indexOf("age");
    age1 = query.value(age2).toInt();
    }
    if(currentMode!="DeadMode")
    query.prepare("update spirit1 set age = :age where number = :number");
    query.bindValue(":age", age1+1);
    query.bindValue(":number",NUM);
    query.exec();
    ui->aEdit->setText(QString::number(age1+1, 10));

}
//定时更新健康值-1
void petWidget::upHealthy(){
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int healthy2 = rec.indexOf("healthy");
    healthy1 = query.value(healthy2).toInt();
    }
    if(currentMode!="DeadMode"&&healthy1>0){
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        //概率事件
        if((qrand()%10)%2==0){
            query.prepare("update spirit1 set healthy = :healthy where number = :number");
            query.bindValue(":healthy", healthy1-1);
            query.bindValue(":number",NUM);
            query.exec();
            ui->hEdit->setText(QString::number(healthy1-1, 10));
        }
    }
}
//定时更新体重+1
void petWidget::upWeight(){
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int weight2 = rec.indexOf("weight");
    weight1 = query.value(weight2).toInt();
    }
    if(currentMode!="DeadMode"){
    query.prepare("update spirit1 set weight = :weight where number = :number");
    query.bindValue(":weight", weight1+1);
    query.bindValue(":number",NUM);
    query.exec();
    upButton();
    ui->wEdit->setText(QString::number(weight1+1, 10));
    }
}
//直接调用为了把新金币上到lineEidt（商店、治疗）
void petWidget::upMoney1(){
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int money2 = rec.indexOf("money");
    money1 = query.value(money2).toInt();
    }

    query.prepare("update spirit1 set money = :money where number = :number");
    query.bindValue(":money", money1);
    query.bindValue(":number",NUM);
    query.exec();
    upButton();
    ui->mEdit->setText(QString::number(money1, 10));
}
//定时更新金币+1
void petWidget::upMoney(){
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int money2 = rec.indexOf("money");
    money1 = query.value(money2).toInt();
    }
    if(currentMode!="DeadMode"){
    query.prepare("update spirit1 set money = :money where number = :number");
    query.bindValue(":money", money1+1);
    query.bindValue(":number",NUM);
    query.exec();
    upButton();
    ui->mEdit->setText(QString::number(money1+1, 10));
    }
}
//从点击change就运行0.1s一次只要不同就换（转场）
void petWidget::upPath(){

    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int path1 = rec.indexOf("path");
    //两次路径不同
    if(path!=query.value(path1).toString()){
    path = query.value(path1).toString();
    //停止pathtime
    pathTime->stop();
    }
    }

    query.prepare("update spirit1 set path = :path where number = :number");
    query.bindValue(":path", path);
    query.bindValue(":number",NUM);
    query.exec();

    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                         QBrush(QPixmap(path).scaled( // 缩放背景图.
                                 this->size(),
                                Qt::IgnoreAspectRatio,
                                Qt::SmoothTransformation))); // 使用平滑的缩放方式
    this->setPalette(palette); // 至此, 已给widget加上了背景图.

}
//直接调用解决饥饿变化（复活、喂食）
void petWidget::upHungry1(){
    //读取原本的饥饿度
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int hungrySensitivity2 = rec.indexOf("hungrySensitivity");
    hungrySensitivity1 = query.value(hungrySensitivity2).toInt();
    }
    ui->hsEdit->setText(QString::number(hungrySensitivity1, 10));
}
//从开始0.1s调用一次（为了区域点击、挑逗、复活、喂食）
void petWidget::upgoodSensitivity(){

    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int goodSensitivity2 = rec.indexOf("goodSensitivity");
    goodSensitivity1 = query.value(goodSensitivity2).toInt();
    }

    query.prepare("update spirit1 set goodSensitivity = :goodSensitivity where number = :number");
    query.bindValue(":goodSensitivity",goodSensitivity1);
    query.bindValue(":number",NUM);
    query.exec();
    ui->gsEdit->setText(QString::number(goodSensitivity1, 10));
    }
//初始第一次进入设置Label宠物图片，恢复图片
void petWidget::putImage(MyQLabel * label){
    upMode();
    if(currentMode=="DeadMode")
    {
        QMovie *movie = new QMovie("://zhuangtai/siwang1.png");
        QSize si (224,168);
        movie->setScaledSize(si);
        label->setMovie(movie);
        movie->start();
    }
    else if (currentMode=="SickMode")
    {
        if(goodSensitivity1<=50)
        {
            QMovie *movie = new QMovie("://zhuangtai/ill1.gif");
            QSize si (168,177);
            movie->setScaledSize(si);
            label->setMovie(movie);
            movie->start();
        }
        else
        {
            QMovie *movie = new QMovie("://zhuangtai/ill2.gif");
            QSize si (200,200);
            movie->setScaledSize(si);
            label->setMovie(movie);
            movie->start();
        }
    }
    else if(currentMode=="HungryMode")
    {
        if(goodSensitivity1<=50)
        {
            QMovie *movie = new QMovie("://zhuangtai/jie1.gif");
            QSize si (250,140);
            movie->setScaledSize(si);
            label->setMovie(movie);
            movie->start();
        }
        else
        {
            QMovie *movie = new QMovie("://zhuangtai/jie2.gif");
            QSize si (200,200);
            movie->setScaledSize(si);
            label->setMovie(movie);
            movie->start();
        }
    }
    else if (currentMode=="UsualMode")
    {
        if(goodSensitivity1<=60)
        {
            QMovie *movie = new QMovie("://zhuangtai/zhengchang1.gif");
            QSize si (200,150);
            movie->setScaledSize(si);
            label->setMovie(movie);
            movie->start();
        }
        else if(goodSensitivity1<=90)
        {
            QMovie *movie = new QMovie("://zhuangtai/zhengchang2.gif");
            QSize si (240,135);
            movie->setScaledSize(si);
            label->setMovie(movie);
            movie->start();
        }
        else
        {
            QMovie *movie = new QMovie("://zhuangtai/zhengchang3.gif");
            QSize si (200,135);
            movie->setScaledSize(si);
            label->setMovie(movie);
            movie->start();
        }
    }
}
//0.1s一次监控状态并且调用putImage设置对应的宠物图片
void petWidget::jiankong()
{
        QString Mode1 =currentMode;
        upMode();
        upButton();
        //如果mode不同调用换图
        if(Mode1!=currentMode)
        putImage(my_label);
}
//直接调用（复活、治疗）
void petWidget::upHealthy1()
{
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int healthy2 = rec.indexOf("healthy");
    healthy1 = query.value(healthy2).toInt();
    }
    upButton();
    ui->hEdit->setText(QString::number(healthy1, 10));
}
//fun、cure、food后的恢复 label图换定时器运作结束恢复jiankongtime
void petWidget::restore()
{
    upMode();
    if(currentMode=="DeadMode")
    {

        gifTime->stop();
        QMovie *movie = new QMovie("://zhuangtai/siwang1.png");
        QSize si (224,168);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
    }
    else if (currentMode=="SickMode")
    {
        if(goodSensitivity1<=50)
        {
            gifTime->stop();
            QMovie *movie = new QMovie("://zhuangtai/ill1.gif");
            QSize si (168,177);
            movie->setScaledSize(si);
            my_label->setMovie(movie);
            movie->start();
        }
        else
        {
            gifTime->stop();
            QMovie *movie = new QMovie("://zhuangtai/ill2.gif");
            QSize si (200,200);
            movie->setScaledSize(si);
            my_label->setMovie(movie);
            movie->start();
        }
    }
    else if(currentMode=="HungryMode")
    {
        if(goodSensitivity1<=50)
        {
            gifTime->stop();
            QMovie *movie = new QMovie("://zhuangtai/jie1.gif");
            QSize si (250,140);
            movie->setScaledSize(si);
            my_label->setMovie(movie);
            movie->start();
        }
        else
        {
            gifTime->stop();
            QMovie *movie = new QMovie("://zhuangtai/jie2.gif");
            QSize si (200,200);
            movie->setScaledSize(si);
            my_label->setMovie(movie);
            movie->start();
        }
    }
    else if (currentMode=="UsualMode")
    {
        if(goodSensitivity1<=60)
        {
            gifTime->stop();
            QMovie *movie = new QMovie("://zhuangtai/zhengchang1.gif");
            QSize si (200,150);
            movie->setScaledSize(si);
            my_label->setMovie(movie);
            movie->start();
        }
        else if(goodSensitivity1<=90)
        {
            gifTime->stop();
            QMovie *movie = new QMovie("://zhuangtai/zhengchang2.gif");
            QSize si (240,135);
            movie->setScaledSize(si);
            my_label->setMovie(movie);
            movie->start();
        }
        else
        {
            gifTime->stop();
            QMovie *movie = new QMovie("://zhuangtai/zhengchang3.gif");
            QSize si (200,125);
            movie->setScaledSize(si);
            my_label->setMovie(movie);
            movie->start();
        }
    }
    jiankongTime->start(100);
}
//从点击food开始每0.1秒调用一次如果eating改变调用
void petWidget::eat(){
    QString eating1 = eating;
    //获取当前图片路径
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int eat1 = rec.indexOf("eating");
    //路径不同
    if(eating1!=query.value(eat1).toString()){
    eating = query.value(eat1).toString();
    eatingTime->stop();
    //加图
    if(eating=="://gongneng/shengqi.gif"){
    QMovie *movie = new QMovie(eating);
    QSize si (300,171);
    movie->setScaledSize(si);
    my_label->setMovie(movie);
    movie->start();
    jiankongTime->stop();
    gifTime->start(4000);
    }
    //不同路径不同图
    else if(eating=="://gongneng/shengqi.gif1")
    {
        QMovie *movie = new QMovie("://gongneng/shengqi.gif");
        QSize si (300,171);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
    }
    else if(eating=="://gongneng/aplle.gif")
    {
        QMovie *movie = new QMovie(eating);
        QSize si (207,140);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
    }
    else if(eating=="://gongneng/aplle.gif1")
    {
        eating="://gongneng/apple.gif";
        QMovie *movie = new QMovie(eating);
        QSize si (207,140);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
    }
    else if(eating=="://gongneng/riceBall.gif")
    {
        QMovie *movie = new QMovie(eating);
        QSize si (220,165);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
    }
    else if(eating=="://gongneng/riceBall.gif1")
    {
        eating="://gongneng/riceBall.gif";
        QMovie *movie = new QMovie(eating);
        QSize si (220,165);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
    }
    else if(eating == "://gongneng/juice.gif")
    {
        QMovie *movie = new QMovie(eating);
        QSize si (214,160);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
    }
    else if(eating == "://gongneng/juice.gif1")
    {
        eating == "://gongneng/juice.gif";
        QMovie *movie = new QMovie(eating);
        QSize si (214,160);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
    }
    else if(eating == "://gongneng/spunSugar.gif")
    {
        QMovie *movie = new QMovie(eating);
        QSize si (216,132);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
    }
    else
    {
        eating=="://gongneng/spunSuage.gif";
        QMovie *movie = new QMovie(eating);
        QSize si (216,132);
        movie->setScaledSize(si);
        my_label->setMovie(movie);
        movie->start();
        jiankongTime->stop();
        gifTime->start(4000);
    }
    }
    }
}
//游戏按钮
void petWidget::on_pushButton_clicked()
{
    GameWindow *gamewindow = new GameWindow;
    gamewindow->setWindowTitle("My Game");
    moneyTime1->start(100);
    gamewindow->setNum(NUM);
    gamewindow->show();
}
//设置账号
void petWidget::setNum(QString NUM)
{
    this->NUM=NUM;
}
//冷却
void petWidget::lengque()
{
    lengqueTime->stop();
    isLenque=false;
}

