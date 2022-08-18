#include "mainwindow.h"
#include "mainwindow2.h"
#include "start.h"

#include <QApplication>

int main(int argc, char *argv[])
{
     QApplication a(argc, argv);
     start begin_game;
     begin_game.show();

    return a.exec();
}
