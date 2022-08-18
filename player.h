#ifndef PLAYER_H
#define PLAYER_H
#include <QPixmap>
#include <QPoint>

class player
{
public:
    player(int pos_x,int pos_y);
    int getx(){return _pos_x;}
    int gety(){return _pos_y;}
    void move(int direction);
    void draw(QPainter *painter);
    void setPos(int pos_x, int pos_y);
    QPoint getPos() {return m_pos;}

private:
    int _pos_x,_pos_y;
    QPixmap m_sprite;
    int step;
    QPoint m_pos;
};

#endif // PLAYER_H
