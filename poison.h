#ifndef POISON_H
#define POISON_H

#include <QPoint>
#include <QPixmap>
#include <QObject>

#include "enemy.h"

class MainWindow;
class MainWindow2;

class Poison :public QObject
{
    Q_OBJECT
    Q_PROPERTY(int m_currentRadius
               READ currentRadius
               WRITE setCurrentRadius)
public:

    Poison();
    Poison(QPoint position, int targetRadius, int damage, MainWindow *game);
    Poison(QPoint position, int targetRadius, int damage, MainWindow2 *game);

    int currentRadius() { return m_currentRadius; }
    void setCurrentRadius( int radius ) { m_currentRadius = radius; }
    void move();
    void draw( QPainter *painter );

    QPoint getPos(){return m_pos;}
    int getTargetRadius(){return m_targetRadius;}
    int getDamage(){return m_damage;}

public slots:

    void hitTarget();

private:
    MainWindow *m_game;
    MainWindow2 *m_game2;
    int m_damage;
    QPoint m_pos;
    const int m_targetRadius;
    int m_currentRadius;
};

#endif // POISON_H
