#ifndef MYQLABEL_H
#define MYQLABEL_H

#include <QObject>
#include <QLabel>
#include <QMessageBox>
#include <QSize>
#include <QMovie>
#include <QTimer>
#include <QTime>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlError>
#include <QString>
#include <petwidget.h>
#include <QMessageBox>

class MyQLabel : public QLabel
{
    Q_OBJECT
public:
    MyQLabel(const QString &Titter,QWidget *parent=0);
    ~MyQLabel();
    void upMode();
    void setNum(QString NUM);

signals:
    //点击信号
    void clicked();

public slots:
    //点击信号响应槽
    void slotClicked();

    void Restore1();
    void lengque();
protected:
    //鼠标按下事件
    void mousePressEvent(QMouseEvent*/* event*/);

private:
    QTimer *gifTime1;
    QTimer *lengqueTime;

    QSqlQuery query;

    QString currentMode;

    int goodSensitivity;
    int hungrySensitivity;
    int healthy;

    QString NUM;
    bool Islengque=false;
};

#endif // MYQLABEL_H
