#include "towerfreeze.h"
#include "QTimer"
#include "mainwindow.h"
#include "ice.h"

TowerFreeze::TowerFreeze(QPoint pos, MainWindow *game)
    :Tower(pos,game)
{
    m_deceleration = 1.0;
    setSprite(QPixmap(":/pic/picture/freezeS.png"));
}


TowerFreeze::TowerFreeze(QPoint pos, MainWindow2 *game)
    :Tower(pos,game)
{
    m_deceleration = 1.0;
    setSprite(QPixmap(":/pic/picture/freezeS.png"));
}

void TowerFreeze::shootWeapon()
{
    if(Tower::getGame() != NULL)
    {
        Ice *ice = new Ice(Tower::getPos(), Tower::getAttackRange(), m_deceleration, Tower::getGame());
        ice->move();
        Tower::getGame()->addIce(ice);
    }
    else
    {
        Ice *ice = new Ice(Tower::getPos(), Tower::getAttackRange(), m_deceleration, Tower::getGame2());
        ice->move();
        Tower::getGame2()->addIce(ice);
    }
}

void TowerFreeze::levelUp()
{
    changeLevel();
    if(getLevel() == 1)
        changeSprite(QPixmap(":/pic/picture/freezeM.png"));
    else if(getLevel() == 2)
        changeSprite(QPixmap(":/pic/picture/freezeL.png"));
}
