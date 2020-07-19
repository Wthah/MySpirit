#ifndef _BALL_H_
#define _BALL_H_

#include <QRect>
#include <QColor>

class Ball
{
public:
    Ball( qreal, qreal, qreal, QColor = Qt::green ); //real相当于double
    ~Ball();

    void move();
    QRectF rect() const;

    //设置小球的位置 大小
    void setShape( const QRectF & );
    void setColor( const QColor & );
    //改变方向
    void setDirX( qreal );
    void setDirY( qreal );
    void setSpeed( qreal );

    QRectF getShape() const;
    QColor getColor() const;
    qreal getDirX() const;
    qreal getDirY() const;
    qreal getSpeed() const;

private:
    QRectF *shape;
    QColor color;
    //xy方向
    qreal dirX;
    qreal dirY;
    qreal speed;
};

#endif
