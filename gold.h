#ifndef GOLD_H
#define GOLD_H

#include <QPixmap>


class gold
{
public:
    gold();
    gold(int x,int y);

    void draw(QPainter *painter);
    bool eatable(int player_x,int player_y);

private:
    QPixmap pic;
    int _x,_y;
};

#endif // GOLD_H
