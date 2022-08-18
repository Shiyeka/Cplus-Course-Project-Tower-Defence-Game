#ifndef START_H
#define START_H

#include <QDialog>

namespace Ui {
class start;
}

class start : public QDialog
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = 0);
    ~start();
    void paintEvent(QPaintEvent *);

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::start *ui;
};

#endif // START_H
