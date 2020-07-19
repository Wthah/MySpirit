#ifndef CHANGEWIDGET_H
#define CHANGEWIDGET_H

#include <QDialog>
#include <QString>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlError>
#include <QPalette>
#include <QImage>

namespace Ui {
class changeWidget;
}

class changeWidget : public QDialog
{
    Q_OBJECT

public:
    explicit changeWidget(QWidget *parent = 0);
    ~changeWidget();
    void setNum(QString NUM);

private slots:
    void on_imageButton_clicked();

    void on_imageButton1_clicked();

    void on_imageButton1_4_clicked();

    void on_imageButton1_5_clicked();

    void on_imageButton1_2_clicked();

    void on_imageButton1_3_clicked();

    void on_imageButton1_6_clicked();

    void on_imageButton1_7_clicked();

    void on_imageButton1_8_clicked();

private:
    Ui::changeWidget *ui;
    QSqlQuery query;
    QString NUM;
};

#endif // CHANGEWIDGET_H
