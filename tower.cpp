#include "tower.h"
#include "mainwindow.h"
#include "mainwindow2.h"

#include <QTimer>

Tower::Tower(QPoint pos, MainWindow *game)
{
    m_level = 0;
    m_pos = pos;
    m_attackRange[0] = 200; m_attackRange[1] = 250; m_attackRange[2] = 300;
    m_damage[0] = 5; m_damage[1] = 10; m_damage[2] = 15;
    m_fireRate[0] = 1500; m_fireRate[1] = 1000; m_fireRate[2] = 800;
    m_sprite = QPixmap(":/pic/picture/towerS.png");
    m_targetEnemy = NULL;
    m_game = game;
    m_game2 = NULL;
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::Tower(QPoint pos, MainWindow2 *game)
{
    m_level = 0;
    m_pos = pos;
    m_attackRange[0] = 150; m_attackRange[1] = 200; m_attackRange[2] = 250;
    m_damage[0] = 5; m_damage[1] = 10; m_damage[2] = 15;
    m_fireRate[0] = 1500; m_fireRate[1] = 1000; m_fireRate[2] = 800;
    m_sprite = QPixmap(":/pic/picture/towerS.png");
    m_targetEnemy = NULL;
    m_game2 = game;
    m_game = NULL;
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

void Tower::draw(QPainter *painter){
    painter->save();
    painter->setPen(Qt::white);
    // 绘制攻击范围
    painter->drawEllipse(m_pos, m_attackRange[m_level], m_attackRange[m_level]);
    // 绘制偏转坐标,由中心+偏移=左上
    // 尺寸大小派上用场了,当然也可以直接获取图片大小,是一样的
    static const QPoint offsetPoint(-40,-40);
    // 绘制炮塔并选择炮塔
    // 这里将坐标原点移到m_pos,绘制的适合,就要加上那个偏移点到左上角
    painter->translate(m_pos);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Tower::beginAttackEnemy(Enemy *enemy){
    m_targetEnemy = enemy;
    shootWeapon();
    m_fireRateTimer->start(m_fireRate[m_level]);
    m_targetEnemy->getAttacked(this);
}

void Tower::shootWeapon(){
    if( m_game != NULL)
    {
        Bullet *bullet = new Bullet(m_pos, m_targetEnemy->getPos(), m_damage[m_level], m_targetEnemy,m_game);
        bullet->move();
        m_game->addBullet(bullet);
    }
    else
    {
        Bullet *bullet = new Bullet(m_pos, m_targetEnemy->getPos(), m_damage[m_level], m_targetEnemy,m_game2);
        bullet->move();
        m_game2->addBullet(bullet);
    }
}

void Tower::targetKilled()
{
    // 目标死亡时,也需要取消关联
    // 取消攻击
    if (m_targetEnemy)
        m_targetEnemy = NULL;
    m_fireRateTimer->stop();
    //m_rotationSprite = 0.0;
}

void Tower::loseEnemy()
{
    // 当敌人脱离炮塔攻击范围,要将炮塔攻击的敌人关联取消
    // 同时取消攻击
    m_targetEnemy = NULL;
    m_fireRateTimer->stop();
    //m_rotationSprite = 0.0;
}

void Tower::levelUp()
{
    m_level ++;
    if(m_level == 1)
        m_sprite = QPixmap(":/pic/picture/towerM.png");
    else if(m_level == 2)
        m_sprite = QPixmap(":/pic/picture/towerL.png");
}
