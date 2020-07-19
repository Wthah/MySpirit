
#include "game.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <cstdlib>
#include <ctime>

Game::Game( QWidget *parent )
    :QWidget( parent )
{
    isWin = false;
    isFailure = false;
    //初始界面大小
    frameWidth = 800;
    frameHeight = 500;

    score = 0;
    rows = 5;
    columns = 10;

    //创建对象
    createBricks();
    createPaddle();
    createBall();

    //动球连贯
    timer = new QTimer( this );
    timer->setInterval( 10 );
    connect( timer, SIGNAL( timeout() ), this, SLOT( moveBall() ) );

    changeColor();
}
//上颜色
void Game::changeColor()
{
    srand( (int) time( NULL ) );

    foreach( Brick *brick, bricks )
    brick->setColor( randomColor() );

    ball->setColor( randomColor() );
    paddle->setColor( randomColor() );
}
//随机色
QColor Game::randomColor()
{
    return QColor( randomInt( 255 ), randomInt( 255 ), randomInt( 255 ) );
}
//随机数
int Game::randomInt( int high )
{
    double d = (double)rand() / ( (double)RAND_MAX + 1 );
    int k = (int) (d * ( high  + 1 ));

    return k;
}
//创建List
void Game::createBricks()
{
    qreal gap = 5.0;
    qreal brickWidth = frameWidth / ( columns + 1 ) - gap;
    qreal brickHeight = frameHeight / 4 / ( rows + 1 ) - gap;

    for( int r = 0; r < rows; ++r )
    for( int c = 0; c < columns; ++c )
    {
        Brick *brick = new Brick(  brickWidth / 2 + c * ( brickWidth + gap ),
                       brickHeight / 2 + r * ( brickHeight + gap ),
                       brickWidth, brickHeight );
        bricks.append( brick );
    }
}
//创建paddle
void Game::createPaddle()
{
    qreal paddleWidth = frameWidth / 10;
    qreal paddleHeight = paddleWidth / 5;

    paddle = new Paddle( frameWidth / 2 - paddleWidth / 2 ,
             frameHeight - paddleHeight * 2,
             paddleWidth, paddleHeight );
}
//创建Ball
void Game::createBall()
{
    qreal ballSide = paddle->getShape().height();
    ball = new Ball( frameWidth / 2 - ballSide / 2, paddle->getShape().top() - ballSide, ballSide );
}

//窗口大小改变时变化
void Game::resizeEvent( QResizeEvent * )
{
    //变化因子
    qreal scaleWidth = rect().width() / frameWidth;
    qreal scaleHeight = rect().height() / frameHeight;

    //每个砖QRectf变化
    foreach( Brick *brick, bricks )
    {
    QRectF shape = brick->getShape();
    brick->setShape( adjustShape( shape, scaleWidth, scaleHeight ) );
    }

    QRectF ballShape = ball->getShape();
    ball->setShape( adjustShape( ballShape, scaleWidth, scaleHeight ) );
    ball->setSpeed( ball->getSpeed() * scaleWidth );

    QRectF paddleShape = paddle->getShape();
    paddle->setShape( adjustShape( paddleShape, scaleWidth, scaleHeight ) );
    paddle->setStep( paddle->getStep() * scaleWidth );

    frameWidth = rect().width();
    frameHeight = rect().height();
}

//根据因子改变大小
QRectF Game::adjustShape( QRectF shape, qreal scaleWidth, qreal scaleHeight )
{
    QRectF newShape( shape.left() * scaleWidth, shape.top() * scaleHeight,
            shape.width() * scaleWidth, shape.height() * scaleHeight );
    return newShape;
}

Game::~Game()
{
    delete ball;
    delete paddle;

    while( !bricks.isEmpty() )
    delete bricks.takeFirst();
}

void Game::paintEvent( QPaintEvent * )
{
    QPainter painter( this );
    //没赢
    if( isWin  || isFailure )
    {
    QFont font( "Courier", 20, QFont::DemiBold );
    QFontMetrics fm( font );

    painter.setFont( font );
    painter.translate( QPoint( width() / 2, height() / 2 ) );
    //赢
    if( isWin )
    {
        int textWidth = fm.width( "You are winner!" );
        painter.setPen( Qt::blue );
        painter.drawText( -textWidth / 2, 0, tr( "You are the winner!" ) );
    }
    //输
    else
    {
        int textWidth = fm.width( "You are loser!" );
        painter.setPen( Qt::red );
        painter.drawText( -textWidth / 2, 0, tr( "You are the loser!" ) );
    }
    //停止绘图 发出finished
    timer->stop();
    emit finished();
    return;
    }

    //设置画笔
    painter.setPen( Qt::NoPen );
    painter.setBrush( ball->getColor() );
    //画图
    painter.drawEllipse( ball->getShape() );
    painter.fillRect( paddle->getShape(), paddle->getColor() );
    foreach( Brick *brick, bricks )
    painter.fillRect( brick->getShape(), brick->getColor() );
}
//移动向左
void Game::movePaddleLeft()
{
    if( paddle->getLeft() > rect().left() )
    {
    paddle->moveLeft();
    update();
    }
}
//向右
void Game::movePaddleRight()
{
    if( paddle->getRight() < rect().right() )
    {
    paddle->moveRight();
    update();
    }
}
//开始游戏
void Game::startGame()
{
    timer->start();
}
//停止游戏
void Game::stopGame()
{
    timer->stop();
}
//移动球
void Game::moveBall()
{
    //获得当前ball的shape
    ball->move();
    //获得基本属性
    QRectF ballShape = ball->getShape();
    QRectF paddleShape = paddle->getShape();
    qreal ballLeft = ballShape.left();
    qreal ballRight = ballShape.right();
    qreal ballBottom = ballShape.bottom();
    qreal ballTop = ballShape.top();
    qreal ballCenterX = ( ballShape.left() + ballShape.right() ) / 2;
    qreal paddleCenterX = ( paddleShape.left() + paddleShape.right() ) / 2;
    //撞左右边
    if( ballLeft < rect().left() || ballRight > rect().right()  )
    ball->setDirX( -ball->getDirX() );
    //如果ballBottom>=top
    if( ballBottom >= paddleShape.top() )
    {
        //有重合回弹
     if( paddleShape.intersects( ballShape ) )
     {
         if( ballCenterX < paddleCenterX )
         ball->setDirX( -ball->getDirX() );
         ball->setDirY( -ball->getDirY() );
     }
     //无重合输
     else
     {
         isFailure = true;
         update();
         return;
     }
    }
    //与上边界碰撞
    if( ballTop < rect().top() )
    ball->setDirY( -ball->getDirY() );
    else
    {
    //遍历所有的砖，如果有重合则改变y且分数加100发送信号，删除该砖
    for( int i = 0; i < bricks.size(); ++i )
    {
        Brick *brick = bricks.at( i );
        QRectF brickShape = brick->getShape();
        if( brickShape.intersects( ball->getShape() ) )
        {
        ball->setDirY( -ball->getDirY() );
        Brick *temp = bricks.takeAt( i );
        delete temp;
        score += 100;
        emit scoreChanged( score );
        }
    }
    //如果没砖获胜
    if( bricks.size() == 0 )
    isWin = true;
    }

    update();
}



void Game::setBallSpeed( qreal speed )
{
    ball->setSpeed( speed );
}

void Game::setPaddleStep( qreal step )
{
    paddle->setStep( step );
}





