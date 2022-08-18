#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QList>

#include "towerposition.h"
#include "tower.h"
#include "towermagic.h"
#include "towerfreeze.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "ray.h"
#include "ice.h"
#include "one.h"
#include "player.h"
#include "poison.h"
#include "gold.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int m_iconWidth
               READ currentIconWidth
               WRITE setCurrentIconWidth)

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *);            //绘图，每类的show()都用在这里
    //void mousePressEvent(QMouseEvent *event);  //鼠标点击，购塔
    void keyPressEvent(QKeyEvent *e);

    void loadTowerPositions();  //初始化塔位，用在mainwindow的构造函数中
    void loadWayPoints();       //初始化航点，用在mainwindow的构造函数中

    void drawWave(QPainter *painter);  //绘制一波敌人
    void drawHP(QPainter *painter);    //显示城堡血量
    void drawGold(QPainter *painter);  //显示金钱
    void drawBar(QPainter *painter);   //绘制状态栏
    void drawTime(QPainter *painter);  //绘制时间

    bool canBuyTower() const;            //判断该点是否可以买塔
    void getHpDamage(int damage = 1);    //城堡减血
    void awardGold(int gold);            //获得金钱
    void removedBullet(Bullet *bullet);  //移除子弹
    void removeRay(Ray *ray);
    void removeIce(Ice *ice);
    void removePoison(Poison *poison);

    void rayEffect(Ray *ray);
    void iceEffect(Ice *ice);
    void poisonEffect(Poison *posion);
    void removedEnemy(Enemy *enemy);     //移除敌人
    void addBullet(Bullet *bullet);      //增加子弹
    void addRay(Ray *ray);
    void addIce(Ice *ice);
    bool findEnemy(Enemy *enemy);        //在List中找到该敌人，用于bullet的hitTartget()

    void doGameOver();  //游戏结束，判断胜负

    int currentIconWidth(){return m_iconWidth;}
    void setCurrentIconWidth(int iconWidth){m_iconWidth =iconWidth;}
    void iconMove();

public slots:

    void updateMap();  //定时刷新界面
    bool loadWave();            //加载下一波敌人，数目与间隔，由人预先制定
    void canPoison(){m_canPoison = true;}

private slots:
    void on_pushButton_clicked();

private:

    Ui::MainWindow *ui;

    QTimer *timer;  //计时器
    QTimer *totalTimer;

    //当前界面上显示内容的管理列表
    QList<TowerPosition> m_towerPositionsList;  //塔位
    QList<Tower *>       m_towersList;          //塔
    QList<WayPoint *>    m_wayPointsList;	    //航点（敌人移动路线）
    QList<Enemy *>       m_enemyList;           //敌人
    QList<Bullet *>      m_bulletList;          //子弹
    QList<Ray *>         m_rayList;
    QList<Ice *>         m_iceList;
    Poison *             m_poison;
    QList<gold *>        m_goldList;                //金币

    player * playerme;  //玩家

    int m_waves;  //已有波数
    int m_gold;   //金钱
    int m_HP;     //城堡生命值
    int goldtime;

    bool m_gameLose;  //是否失败
    bool m_gameWin;   //是否胜利
    bool m_canPoison;

    int m_iconWidth;
    int losttime;//游戏失败后界面转换的借助参数

};

#endif // MAINWINDOW_H

