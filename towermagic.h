#ifndef TOWERMAGIC_H
#define TOWERMAGIC_H

#include "tower.h"

class TowerMagic : public Tower
{
    Q_OBJECT
public:
    TowerMagic(QPoint pos, MainWindow *game);
    TowerMagic(QPoint pos, MainWindow2 *game);
    void levelUp();
public slots:
    void shootWeapon();
};

#endif // TOWERMAGIC_H
