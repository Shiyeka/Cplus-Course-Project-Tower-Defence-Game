#include "player.h"
#include <QPainter>
#include <QPixmap>

player::player(int pos_x, int pos_y)
{
    _pos_x=pos_x;
    _pos_y=pos_y;
    m_sprite.load(":/pic/picture/player.png");
    step=10;//设置player移动步长
}

void player::draw(QPainter *painter)
{
    painter->drawPixmap(_pos_x, _pos_y, m_sprite);
}

void player::move(int direction)
{
    switch (direction) {
    case 1://上
        if(_pos_y-step>=0)
        _pos_y=_pos_y-step;
        else _pos_y=0;
        break;
    case 2://下
        if(_pos_y+step<=840)
        _pos_y=_pos_y+step;
        else _pos_y=840;
        break;
    case 3://左
        if(_pos_x-step>=0)
        _pos_x=_pos_x-step;
        else _pos_x=0;
        break;
    case 4://右
        if(_pos_x+step<=1140)
        _pos_x=_pos_x+step;
        else _pos_x=1140;
        break;
    default:
        break;
    }
    setPos(_pos_x,_pos_y);
}

void player::setPos(int pos_x, int pos_y)
{
    m_pos.setX(pos_x);
    m_pos.setY(pos_y);
}

