#include "one.h"
#include "ui_one.h"
#include "mainwindow.h"
#include "mainwindow2.h"
#include "start.h"
#include <QDialog>

one::one(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::one)
{
    ui->setupUi(this);
}

one::~one()
{
    delete ui;
}
void one::on_pushButton_clicked()
{
    MainWindow *win = new MainWindow;
        win->show();
        //this->close();
        delete this;
}

void one::on_pushButton_2_clicked()
{
    MainWindow2 *win2 = new MainWindow2;
    win2->show();
    //this->close();
    delete this;
}

void one::on_pushButton_3_clicked()
{
    start *back1 =new start;
    back1->show();
    //this->close();
    delete this;
}

void one::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/picture/background.jpg");
    painter.drawPixmap(0, 0, 800, 600, pix);
}
