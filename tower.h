#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QPainter>
#include <QObject>
#include <QTimer>

#include "bullet.h"
#include "enemy.h"

class MainWindow;  //与MainWindow相互包含头文件会报错。因此先在这里前置声明，再在cpp中包含
class MainWindow2;

class Tower : public QObject  //只有继承QObject才可用槽函数
{
    Q_OBJECT  //还需加这个才可用槽函数

public:
    Tower(){}
    Tower(QPoint pos, MainWindow *game);
    Tower(QPoint pos, MainWindow2 *game);
    void draw(QPainter *painter);

    void targetKilled();  //敌人已被消灭

    void beginAttackEnemy(Enemy *enemy);  //开始攻击敌人
    void loseEnemy();

    void clearTargetEnemy(){m_targetEnemy = NULL;}
    void stopFire(){m_fireRateTimer->stop();}

    int getPosX(){return m_pos.x();}
    int getPosY(){return m_pos.y();}
    QPoint getPos(){return m_pos;}
    int getAttackRange(){return m_attackRange[m_level];}
    int getDamage(){return m_damage[m_level];}
    Enemy *getTargetEnemy(){return m_targetEnemy;}
    MainWindow *getGame(){return m_game;}
    MainWindow2 *getGame2(){return m_game2;}

    void setDamage(int a, int b, int c){m_damage[0] = a;m_damage[1] = b;m_damage[2] = c;}
    void setSprite(QPixmap pixmap){m_sprite = pixmap;}
    QTimer *getFireRateTimer(){return m_fireRateTimer;}

    bool canLevelUp(){if(m_level<2) return true;
                      else return false;}
    virtual void levelUp();
    int getLevel(){return m_level;}
    void changeLevel(){m_level++;}
    void changeSprite(QPixmap pixmap){m_sprite = pixmap;}

public slots:

    virtual void shootWeapon();  //发射子弹 //改动

private:

    QPoint m_pos;
    int m_level;
    int m_attackRange[3];
    int m_damage[3];
    int m_fireRate[3];
    QPixmap m_sprite;

    //double m_rotationSpreite;  //旋转炮台，暂且不用
    Enemy *m_targetEnemy;
    QTimer *m_fireRateTimer;
    MainWindow *m_game;
    MainWindow2 *m_game2;
};

#endif // TOWER_H
