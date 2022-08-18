#include "gold.h"

#include <QPainter>
#include <QPixmap>

gold::gold(int x,int y)
{
    pic = QPixmap(":/pic/picture/jewel_money.png");
    _x=x;_y=y;

}
void gold::draw(QPainter *painter)
{
    painter->drawPixmap(_x, _y, pic);
}

bool gold::eatable(int player_x,int player_y)
{

    if(player_x<=_x+55 && player_x>=_x+5 && player_y>=_y+5 && player_y<=_y+55)
    {
        return true;
    }
    return false;
}

