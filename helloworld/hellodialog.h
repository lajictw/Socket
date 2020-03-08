#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class hellodialog; }
QT_END_NAMESPACE

class hellodialog : public QDialog
{
    Q_OBJECT

public:
    hellodialog(QWidget *parent = nullptr);
    ~hellodialog();

public slots:
    //定义槽函数用来接受消息
    void getMessage(const QString &message);

private slots:
    void on_startbtn_clicked();

    void on_endbtn_clicked();

private:
    Ui::hellodialog *ui;
};
#endif // HELLODIALOG_H
