#include "replay.h"
#include "ui_replay.h"
#include "mainwindow.h"
#include "start.h"

replay::replay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::replay)
{
    ui->setupUi(this);
}

replay::~replay()
{
    delete ui;
}

void replay::on_pushButton_clicked()
{
    MainWindow *playagain = new MainWindow;
    playagain->show();
    delete this;
}

void replay::on_pushButton_2_clicked()
{
    start *newstart = new start;
    newstart->show();
    delete this;
}
void replay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/picture/background.jpg");
    painter.drawPixmap(0, 0, 800, 600, pix);
}
