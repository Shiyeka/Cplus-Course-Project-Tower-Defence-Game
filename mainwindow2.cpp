#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "qmath.h"
#include "QTime"
#include "QTimer"
#include "one.h"
#include <QPainter>
#include <QPoint>
#include <QAnimationDriver>
#include <QPropertyAnimation>

extern bool ifInRange(QPoint point1, int radius1, QPoint point2, int radius2);

using namespace std;

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);

    m_waves = 0;           //初始时已有波数为零
    m_gameLose = false;
    m_gameWin = false;
    m_canPoison = true;
    m_iconWidth = 0;
    m_HP = 10;
    m_gold = 900;

    playerme=new player(50,50);//初始化玩家位置

    //设置计时器
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));  //关联时间与updateMap()函数
    timer->start(10);  //每多少毫秒传递一次时间信号 //帧数

    totalTimer = new QTimer(this);
    totalTimer->start(5*60*1000);

    loadTowerPositions();  //初始化塔位
    loadWayPoints();       //初始化航点
    QTimer::singleShot( 10 * 1000 , this , SLOT(loadWave()));//加载第一波敌人

    m_poison = NULL;
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::paintEvent(QPaintEvent *)
{
    //判断游戏是否结束
    if (m_gameLose || m_gameWin)
    {
        QString text = m_gameWin ? "YOU WIN!!!" : "YOU LOST!!!";
        QPainter painter;
        painter.begin(this);
        QFont font = painter.font();
        font.setPixelSize(50);
        painter.setFont(font);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        painter.end();
        return;
    }

    QPainter *pt = new QPainter();
    pt->begin(this);  //就是一定要加painter的begin()和end()，我也不知道为什么

    //画地图
    pt->drawPixmap(0, 0,1200,900,QPixmap(":/pic/picture/map2.jpg"));
    //画施毒图标
    if(m_canPoison){pt->drawPixmap(1100, 100, QPixmap(":/pic/picture/poisonbottle.png"));}
    else
    {
        pt->drawPixmap(1100, 100, QPixmap(":/pic/picture/poisonbottle2.png"));
        pt->save();
        pt->setBrush(QColor(128,0,128));
        pt->setOpacity(0.5);
        pt->drawRect(1100, 100, m_iconWidth,100);
        pt->restore();
    }

    //画背景装饰物

    //画塔位
    int i;
    for(i=0;i<12;i++) { m_towerPositionsList[i].draw(pt); }  //有12个塔位
    //画塔、航点、敌人
    foreach (Tower *tower, m_towersList) { tower->draw(pt); } //把draw的参数都改成指针了，否则报错。网上说什么深拷贝浅拷贝，不懂。
    //foreach (WayPoint *waypoint, m_wayPointsList[0]) { waypoint->draw(pt); }
    //foreach (WayPoint *waypoint, m_wayPointsList[1]) { waypoint->draw(pt); }
    foreach (Enemy *enemy, m_enemyList) { enemy->draw(pt); }
    foreach (Bullet *bullet, m_bulletList) { bullet->draw(pt);}
    foreach (Ray *ray, m_rayList) { ray->draw(pt);}
    foreach (Ice *ice, m_iceList) { ice->draw(pt);}
    foreach (gold *gold,m_goldList){gold->draw(pt);}
    if(m_poison!=NULL) {m_poison->draw(pt);}
    //显示已有波数、城堡血量、金钱以及状态栏
    //设置字体大小
    QFont font = pt->font();
    font.setPixelSize(25);
    pt->setFont(font);
    drawBar(pt);
    drawWave(pt);
    drawHP(pt);
    drawGold(pt);
    drawTime(pt);

    //画玩家
    playerme->draw(pt);

    pt->end();
    delete pt;
}

void MainWindow2::loadTowerPositions(){
    QPoint pos[] =
        {
        //共12个点
        QPoint(100, 200),
        QPoint(300, 200),
        QPoint(800, 200),
        QPoint(1000, 200),

        QPoint(100, 600),
        QPoint(300, 600),
        QPoint(800, 600),
        QPoint(1000, 600),

        QPoint(450, 400),
        QPoint(650, 400),

        QPoint(550, 100),
        QPoint(550, 700),
        };

        int len	= sizeof(pos) / sizeof(pos[0]);

        for (int i = 0; i < len; ++i){
            m_towerPositionsList.push_back(pos[i]);
        }
}

static const int TowerCost = 300;

bool MainWindow2::canBuyTower() const
{
    if (m_gold >= TowerCost)
    { return true; }
    return false;
}

void MainWindow2::addBullet(Bullet *bullet){
    m_bulletList.push_back(bullet);

}

void MainWindow2::addRay(Ray *ray)
{
    m_rayList.push_back(ray);
}

void MainWindow2::addIce(Ice *ice)
{
    m_iceList.push_back(ice);
}

void MainWindow2::loadWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(1125,460));
    m_wayPointsList[0].push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1125,350));
    m_wayPointsList[0].push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(740,350));
    m_wayPointsList[0].push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(740,50));
    m_wayPointsList[0].push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(465,50));
    m_wayPointsList[0].push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(465,350));
    m_wayPointsList[0].push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(65,350));
    m_wayPointsList[0].push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);
    ////////////////////////////////////////////////////////////
    WayPoint *wayPoint8 = new WayPoint(QPoint(1125,460));
    m_wayPointsList[1].push_back(wayPoint8);

    WayPoint *wayPoint9 = new WayPoint(QPoint(1125,570));
    m_wayPointsList[1].push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(740,570));
    m_wayPointsList[1].push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(740,840));
    m_wayPointsList[1].push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);

    WayPoint *wayPoint12 = new WayPoint(QPoint(465,840));
    m_wayPointsList[1].push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint13 = new WayPoint(QPoint(465,570));
    m_wayPointsList[1].push_back(wayPoint13);
    wayPoint13->setNextWayPoint(wayPoint12);

    WayPoint *wayPoint14 = new WayPoint(QPoint(65,570));
    m_wayPointsList[1].push_back(wayPoint14);
    wayPoint14->setNextWayPoint(wayPoint13);
}

void MainWindow2::getHpDamage(int damage/* = 1*/)
{
    //m_audioPlayer->playSound(LifeLoseSound);  //音乐，暂未使用
    m_HP -= damage;
    if (m_HP <= 0)
    { doGameOver(); }
}

void MainWindow2::removedBullet(Bullet *bullet)
{
    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow2::removeRay(Ray *ray)
{
    m_rayList.removeOne(ray);
    delete ray;
}

void MainWindow2::removePoison(Poison *poison)
{
    delete poison;
    m_poison = NULL;
}

void MainWindow2::removeIce(Ice *ice)
{
    m_iceList.removeOne(ice);
    delete ice;
}

void MainWindow2::removedEnemy(Enemy *enemy)
{
    m_enemyList.removeOne(enemy);
    delete enemy;
    //如果屏幕上没有敌人
    if (m_enemyList.empty())
    {
        ++this->m_waves; // 当前波数加1
        // 然后，继续读取下一波
        if (!loadWave())
        {
            // 当没有下一波时，游戏胜利
            // 设置游戏胜利标志为true
            m_gameWin = true;
        }
    }
}

bool MainWindow2::loadWave()
{
    //一共6波，每波6个敌人
    if (m_waves >= 6){return false;}
    if(m_waves % 2 == 0)
    {
        WayPoint *startWayPoint = m_wayPointsList[0].back(); // 这里是个逆序的，末项是起点
        int enemyStartInterval = 1000;  //敌人出现间隔
        for (int i = 0; i < m_waves*2+6; i++)
        {
            if( i % 2 ==0 )
            {
                Enemy *enemy = new Enemy(startWayPoint, this, QPixmap(":/pic/picture/enemy1.png"),40,1,100);
                m_enemyList.push_back(enemy);
                QTimer::singleShot( i * enemyStartInterval, enemy, SLOT(doActivate()));
                    //singleShot相当于定时器，好处在于不需使用timer，在设置时间到后自动触发SLOT中的函数
            }
            else
            {
                Enemy *enemy = new Enemy(startWayPoint, this, QPixmap(":/pic/picture/enemy2.png"),80,2,200);
                m_enemyList.push_back(enemy);
                QTimer::singleShot( i * enemyStartInterval, enemy, SLOT(doActivate()));
            }
        }
    }
    else
    {
        WayPoint *startWayPoint = m_wayPointsList[1].back(); // 这里是个逆序的，末项是起点
        int enemyStartInterval = 1000;  //敌人出现间隔
        for (int i = 0; i < m_waves*2+6; i++)
        {
            if( i % 2 ==0 )
            {
                Enemy *enemy = new Enemy(startWayPoint, this, QPixmap(":/pic/picture/enemy1.png"),40,1,100);
                m_enemyList.push_back(enemy);
                QTimer::singleShot( i * enemyStartInterval, enemy, SLOT(doActivate()));
                    //singleShot相当于定时器，好处在于不需使用timer，在设置时间到后自动触发SLOT中的函数
            }
            else
            {
                Enemy *enemy = new Enemy(startWayPoint, this, QPixmap(":/pic/picture/enemy2.png"),80,2,200);
                m_enemyList.push_back(enemy);
                QTimer::singleShot( i * enemyStartInterval, enemy, SLOT(doActivate()));
            }
        }
    }

    return true;
}

void MainWindow2::updateMap()  //更新界面：移动敌人，判断tower与enemy的距离
{
    //1.移动敌人
    foreach (Enemy *enemy, m_enemyList)
    {
        enemy->move();
    }

    //2.判断tower与enemy的距离
    foreach (Tower *tower, m_towersList)
    {
        //如果tower没有攻击
        if(tower->getTargetEnemy() == NULL)
        {
            foreach  (Enemy *enemy, m_enemyList)
            {
                if(ifInRange(tower->getPos(), tower->getAttackRange(), enemy->getPos(), 1))
                {
                    tower->beginAttackEnemy(enemy);
                    break;
                }
            }
        }
        //如果tower正在攻击
        else
        {
            if( !ifInRange(tower->getPos(), tower->getAttackRange(), tower->getTargetEnemy()->getPos(), 1))
            {
                tower->loseEnemy();
            }
        }
    }

    //3.移动玩家
    update();

    //4.随机产生金币
    this->goldtime++;
    if(this->goldtime%1000==0)
    {
            int x,y;
            srand((unsigned)time(NULL));
                x=(rand() % (1100-100))+ 100 + 1;
                y=(rand() % (800-100))+ 100 + 1; //生产随机数
                gold *gold1 =new gold(x,y);
                m_goldList.push_back(gold1);
    }

    foreach(gold *gold,m_goldList)
    {
        if(gold->eatable(playerme->getx(),playerme->gety())==true)
        {
                m_goldList.removeOne(gold);
                delete gold;
                awardGold(50);
                update();
        }
    }
}

void MainWindow2::doGameOver()
{
    if (!m_gameLose)
    {
        m_gameLose = true;
    }
}

void MainWindow2::awardGold(int gold)
{
    m_gold += gold;
    update();
}

void MainWindow2::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(400, 5, 200, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void MainWindow2::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(0, 5, 200, 25), QString("HP : %1").arg(m_HP));
}

void MainWindow2::drawGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(m_gold));
}

void MainWindow2::drawTime(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    int msec = 5*60*1000 - totalTimer->remainingTime();
    int muni = msec/(60*1000);
    int sec = (msec - muni*(60*1000))/1000;
    painter->drawText(QRect(600, 5, 200, 25), QString("TIME : %1").arg(muni)+QString(":%1").arg(sec));
}

void MainWindow2::drawBar(QPainter *painter)
{
    painter->setPen(QPen(Qt::green));
    painter->drawRect(QRect(0, 0, 1000, 35));
}

bool MainWindow2::findEnemy(Enemy *enemy)
{
    if(m_enemyList.indexOf(enemy) != -1)
        //indexOf()查找，未找到则返回-1
        return true;
    return false;
}

void MainWindow2::rayEffect(Ray *ray)
{
    foreach(Enemy *enemy, m_enemyList)
    {
        if(ifInRange(enemy->getPos(),1,ray->getPos(),ray->getTargetRadius()))
        {
            enemy->getDamaged(ray->getDamage());
        }

    }
    removeRay(ray);
}

void MainWindow2::iceEffect(Ice *ice)
{
    foreach(Enemy *enemy, m_enemyList)
    {
        if(ifInRange(enemy->getPos(),1,ice->getPos(),ice->getTargetRadius())
                && ! enemy->ifDecelerated())
        {
            enemy->getDecelerated(ice->getDeceleration());
        }
    }
    removeIce(ice);
}

void MainWindow2::on_pushButton_clicked()
{
    one *back =new one;
    back->show();

    qDeleteAll(m_towersList.begin(),m_towersList.end());
    qDeleteAll(m_wayPointsList[1].begin(),m_wayPointsList[1].end());
    qDeleteAll(m_wayPointsList[2].begin(),m_wayPointsList[2].end());
    qDeleteAll(m_enemyList.begin(),m_enemyList.end());
    qDeleteAll(m_bulletList.begin(),m_bulletList.end());
    qDeleteAll(m_rayList.begin(),m_rayList.end());
    qDeleteAll(m_iceList.begin(),m_iceList.end());
    delete m_poison;
    qDeleteAll(m_goldList.begin(),m_goldList.end());
    delete playerme;

    delete this;
}

void MainWindow2::keyPressEvent(QKeyEvent *e)
{
    //direction = 1,2,3,4 for 上下左右;操控玩家
    if(e->key() == Qt::Key_W)
    {
        this->playerme->move(1);
    }
    else if(e->key() == Qt::Key_S)
    {
        this->playerme->move(2);
    }
    else if(e->key() == Qt::Key_A)
    {
        this->playerme->move(3);
    }
    else if(e->key() == Qt::Key_D)
    {
         this->playerme->move(4);
    }
    else if(e->key() == Qt::Key_J ||e->key() == Qt::Key_K ||e->key() == Qt::Key_L )
    {
    //操控塔防放置
        int xpos = this->playerme->getx();
        int ypos = this->playerme->gety();//得到玩家所在的位置坐标
        auto it = m_towerPositionsList.begin();
        QPoint player_position(xpos,ypos);

        while (it != m_towerPositionsList.end())
        {
            //如果金额足够，点击位置在范围中，未有塔
            if (canBuyTower()
                    && it->containPoint(player_position)
                    && ! it->hasTower())
            {
                m_gold -= TowerCost;
                if(e->key() == Qt::Key_J)
                {
                    Tower *tower = new Tower(it->centerPos(), this); //生成新塔对象
                    m_towersList.push_back(tower); //将新塔添入塔列表中
                    it->setHasTower(tower); //将塔位状态修改为已有塔
                }
                else if(e->key() == Qt::Key_K)
                {
                    TowerMagic *tower = new TowerMagic(it->centerPos(), this);
                    m_towersList.push_back(tower); //将新塔添入塔列表中
                    it->setHasTower(tower); //将塔位状态修改为已有塔
                }
                else if(e->key() == Qt::Key_L)
                {
                    TowerFreeze *tower = new TowerFreeze(it->centerPos(), this);
                    m_towersList.push_back(tower); //将新塔添入塔列表中
                    it->setHasTower(tower); //将塔位状态修改为已有塔
                }
                update(); //更新mainwindow
                break;
            }
            else if(canBuyTower()
                    && it->hasTower()
                    && it->containPoint(player_position)
                    && it->getTower()->canLevelUp())
            {
                m_gold -= TowerCost;
                it->getTower()->levelUp();
            }
            it++;
        }
    }
    else if(e->key() == Qt::Key_P
              && m_canPoison)
    {
        m_poison = new Poison(playerme->getPos()+QPoint(30,30),360,5,this);
        m_poison->move();
        iconMove();
        m_canPoison = false;
        QTimer::singleShot(30*1000,this,SLOT(canPoison()));
    }
}

void MainWindow2::iconMove()
{
    static const int duration = 30*1000;

    QPropertyAnimation *animation = new QPropertyAnimation(this,"m_iconWidth");
    animation->setDuration(duration);
    animation->setStartValue(0);
    animation->setEndValue(100);

    //connect(animation, SIGNAL(finished()),this,SLOT(hitTarget()));

    animation->start();
}

void MainWindow2::poisonEffect(Poison *poison)
{
    foreach(Enemy *enemy, m_enemyList)
    {
        if(ifInRange(enemy->getPos(),1,poison->getPos(),poison->getTargetRadius()))
        {
            enemy->getPoisoned();
        }
    }
    removePoison(poison);
}
