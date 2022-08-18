#ifndef REPLAY_H
#define REPLAY_H

#include <QDialog>

class MainWindow;

namespace Ui {
class replay;
}

class replay : public QDialog
{
    Q_OBJECT

public:
    explicit replay(QWidget *parent = 0);
    ~replay();
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::replay *ui;
};

#endif // REPLAY_H
