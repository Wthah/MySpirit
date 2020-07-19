 #ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QByteArray>

namespace Ui {
class registerWidget;
}

class registerWidget : public QDialog
{
    Q_OBJECT

public:
    explicit registerWidget(QWidget *parent = 0);
    ~registerWidget();
    bool IsTableExist(QSqlQuery &query,QString table);//表是否存在
    int testPass(QString pass); //检验密码是否符合要求
    int testNumber(QString number); //检验账号是否符合要求

private slots:
    void on_confirm_clicked();

private:
    QString NUM;
    QString num;//验证
    QString PASS1;
    QString PASS;
    QSqlQuery query;
    Ui::registerWidget *ui;
};

#endif // REGISTERWIDGET_H
