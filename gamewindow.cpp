
#include "gamewindow.h"
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLabel>
#include <QPalette>
#include <QImage>


GameWindow::GameWindow()
{
    isRunning = false;
    //创建game为中心窗口
    game = new Game( this );
    setCentralWidget( game );
    //菜单栏工具栏
    createMenu();
    createToolBar();
    //接受信号
    connect( game, SIGNAL( finished() ), this, SLOT( on_finished() ) );
    connect( game, SIGNAL( scoreChanged( int ) ), this, SLOT( on_changeScore( int ) ) );
    //加背景图
    setFixedSize(1221,710);
    setAutoFillBackground(true);
    QPalette PAllbackground;
    QImage ImgAllbackground("://petjiemian/youxibeijing.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}

//创建Menu功能
void GameWindow::createMenu()
{
    newGame = new QAction( tr( "New Game" ), this );
    exitGame = new QAction( tr( "Exit" ), this );
    startGame = new QAction( tr( "Start" ), this );
    stopGame = new QAction( tr( "Stop" ), this );
    changeColor = new QAction(  tr( "Change Color" ), this );
    aboutAction = new QAction(  tr( "about" ), this );
    gameOne = new QAction( tr( "Game One" ), this );
    gameTwo = new QAction(  tr( "Game Two" ), this );
    gameThree = new QAction( tr( "Game Three" ), this );

    //添加菜单
    QMenu *optionMenu = menuBar()->addMenu( tr( "Option" ) );
    QMenu *controlMenu = menuBar()->addMenu( tr( "Control" ) );
    QMenu *setMenu = menuBar()->addMenu( tr( "Set" ) );
    QMenu *gameMenu = menuBar()->addMenu( tr( "Game" ) );
    QMenu *helpMenu = menuBar()->addMenu( tr( "Help" ) );
    //添加动作
    optionMenu->addAction( newGame );
    optionMenu->addAction( exitGame );
    controlMenu->addAction( startGame );
    controlMenu->addAction( stopGame );
    setMenu->addAction( changeColor );
    gameMenu->addAction( gameOne );
    gameMenu->addAction( gameTwo );
    gameMenu->addAction( gameThree );
    helpMenu->addAction( aboutAction );
    //创建信号与槽的关联
    connect( startGame, SIGNAL( triggered() ), this, SLOT( on_startGame() ) );
    connect( exitGame, SIGNAL( triggered() ), this, SLOT( close() ) );
    connect( changeColor, SIGNAL( triggered() ), this, SLOT( on_changeColor() ) );
    connect( stopGame, SIGNAL( triggered() ), this, SLOT( on_stopGame() ) );
    connect( newGame, SIGNAL( triggered() ), this, SLOT( on_newGame() ) );
    connect( aboutAction, SIGNAL( triggered() ), this, SLOT( on_about() ) );
    connect( gameOne, SIGNAL( triggered() ), this, SLOT( on_gameOne() ) );
    connect( gameTwo, SIGNAL( triggered() ), this, SLOT( on_gameTwo() ) );
    connect( gameThree, SIGNAL( triggered() ), this, SLOT( on_gameThree() ) );

    updateActions();
}

//创建工具栏
void GameWindow::createToolBar()
{
    QToolBar *controlToolBar = addToolBar( tr( "Control" ) );

    controlToolBar->addAction( newGame );
    controlToolBar->addAction( startGame );
    controlToolBar->addAction( stopGame );
    controlToolBar->addAction( changeColor );
    controlToolBar->addSeparator();
    //加上分数
    gameLabel = new QLabel( tr( "<h3><font color=blue>Game One</font></h3>" ), this );
    scoreLabel = new QLabel( tr( "<h3><font color=green>Score: 0</font></h3>" ), this );
    controlToolBar->addWidget( gameLabel );
    controlToolBar->addSeparator();
    controlToolBar->addWidget( scoreLabel );
}

//结束
void GameWindow::on_finished()
{
    stopGame->setEnabled( false );
    startGame->setEnabled( false );
    changeColor->setEnabled( false );
}

//接受目前分数设置分数
void GameWindow::on_changeScore( int score )
{
    scoreLabel->setText( tr( "<h3><font color=blue>Score: %1</font></h3>" ).arg( score ) );
    query.prepare("SELECT  * FROM spirit1 WHERE number = :number") ;
    query.bindValue(":number",NUM);
    query.exec();
    QSqlRecord rec = query.record();
    while(query.next()){
    rec = query.record();
    int money2 = rec.indexOf("money");
    money = query.value(money2).toInt();
    }
    query.prepare("update spirit1 set money = :money where number = :number");
    query.bindValue(":money", money+1);
    query.bindValue(":number",NUM);
    query.exec();
}


void GameWindow::on_newGame()
{
    createNewGame( 1 );
}

void GameWindow::createNewGame( int gameNum )
{
    if( gameNum == 1 )
    gameLabel->setText( tr( "<h3><font color=blue>Game One</font></h3>" ) );
    else if( gameNum == 2 )
    gameLabel->setText( tr( "<h3><font color=blue>Game Two</font></h3>" ) );
    else if( gameNum == 3 )
    gameLabel->setText( tr( "<h3><font color=blue>Game Three</font></h3>" ) );
    on_changeScore( 0 );

    game->deleteLater();
    game = new Game( this );
    setCentralWidget( game );
    //设置相应速度和步长
    game->setBallSpeed( gameNum );
    game->setPaddleStep( gameNum * 10.0 );
    connect( game, SIGNAL( finished() ), this, SLOT( on_finished() ) );
    connect( game, SIGNAL( scoreChanged( int ) ), this, SLOT( on_changeScore( int ) ) );
    isRunning = false;
    changeColor->setEnabled( true );
    updateActions();
}

void GameWindow::on_gameOne()
{
    createNewGame( 1 );
}

void GameWindow::on_gameTwo()
{
    createNewGame( 2 );
}


void GameWindow::on_gameThree()
{
    createNewGame( 3 );
}

void GameWindow::on_changeColor(){

}

//介绍
void GameWindow::on_about()
{
    QMessageBox::about( this, tr( "About" ), tr( "This is a small game developed by SenLin." ) );
}

//更新按钮能力
void GameWindow::updateActions()
{
    startGame->setEnabled( !isRunning );
    stopGame->setEnabled( isRunning );
}


void GameWindow::on_startGame()
{
    game->startGame();
    isRunning = true;
    updateActions();
}

void GameWindow::on_stopGame()
{
    game->stopGame();
    isRunning = false;
    updateActions();
}


void GameWindow::keyPressEvent( QKeyEvent *event )
{
    switch( event->key() )
    {
        case Qt::Key_Left:
        game->movePaddleLeft();
        break;

        case Qt::Key_Right:
        game->movePaddleRight();
        break;
    }
}

void GameWindow::setNum(QString NUM)
{
    this->NUM=NUM;
}



