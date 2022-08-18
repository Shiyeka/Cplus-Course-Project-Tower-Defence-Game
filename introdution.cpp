#include "introdution.h"
#include "ui_introdution.h"
#include "start.h"
#include <QPainter>
#include <QPixmap>

introdution::introdution(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::introdution)
{
    ui->setupUi(this);
}

introdution::~introdution()
{
    delete ui;
}

void introdution::on_pushButton_clicked()
{
    start *back1 =new start;
    back1->show();
    delete this;
}

void introdution::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/picture/introduction.jpg");
    painter.drawPixmap(0, 0, 1300, 758, pix);
}
