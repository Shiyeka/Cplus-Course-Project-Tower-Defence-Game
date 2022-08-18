#include "towermagic.h"
#include "QTimer"
#include "mainwindow.h"
#include "ray.h"

TowerMagic::TowerMagic(QPoint pos, MainWindow *game)
    :Tower(pos,game)
{
    setDamage(3,6,9);
    setSprite(QPixmap(":/pic/picture/magicS.png"));
}

TowerMagic::TowerMagic(QPoint pos, MainWindow2 *game)
    :Tower(pos,game)
{
    setDamage(3,6,9);
    setSprite(QPixmap(":/pic/picture/magicS.png"));
}

void TowerMagic::shootWeapon()
{
    if(Tower::getGame() != NULL)
    {
        Ray *ray = new Ray(Tower::getPos(), Tower::getAttackRange(),Tower::getDamage(),Tower::getGame());
        ray->move();
        Tower::getGame()->addRay(ray);
    }
    else
    {
        Ray *ray = new Ray(Tower::getPos(), Tower::getAttackRange(),Tower::getDamage(),Tower::getGame2());
        ray->move();
        Tower::getGame2()->addRay(ray);
    }

}

void TowerMagic::levelUp()
{
    changeLevel();
    if(getLevel() == 1)
        changeSprite(QPixmap(":/pic/picture/magicM.png"));
    else if(getLevel() == 2)
        changeSprite(QPixmap(":/pic/picture/magicL.png"));
}
