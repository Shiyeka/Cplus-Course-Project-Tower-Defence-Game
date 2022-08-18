#ifndef TOWERFREEZE_H
#define TOWERFREEZE_H

#include "tower.h"

class TowerFreeze : public Tower
{
    Q_OBJECT
public:
    TowerFreeze(QPoint pos, MainWindow *game);
    TowerFreeze(QPoint pos, MainWindow2 *game);
    void levelUp();

public slots:

    void shootWeapon();

private:

    double m_deceleration;

};

#endif // TOWERFREEZE_H
