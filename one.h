#ifndef ONE_H
#define ONE_H

#include <QDialog>
#include "mainwindow.h"
#include "mainwindow2.h"

namespace Ui {
class one;
}

class one : public QDialog
{
    Q_OBJECT

public:
    explicit one(QWidget *parent = 0);
    ~one();
    bool getbutton(){return button;}
    void paintEvent(QPaintEvent *);

public slots:
     void on_pushButton_clicked();
     void on_pushButton_2_clicked();
     void on_pushButton_3_clicked();

private:
    Ui::one *ui;
    bool button=false;
};

#endif // ONE_H

