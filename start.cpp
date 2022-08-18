#include "start.h"
#include "ui_start.h"
#include "one.h"
#include "introdution.h"

start::start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
}

start::~start()
{
    delete ui;
}

void start::on_pushButton_clicked()
{
    one * select_background =new one;
    select_background->show();
    //this->close();
    delete this;
}

void start::on_pushButton_2_clicked()
{
    this->close();
    exit(0);
}

void start::on_pushButton_3_clicked()
{
    introdution * intro= new introdution;
    intro->show();
    delete this;
}

void start::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/picture/_background.jpg");
    painter.drawPixmap(0, 0, 800, 600, pix);
}


