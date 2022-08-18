#include "poison.h"
#include "enemy.h"
#include "mainwindow.h"

#include <QAnimationDriver>
#include <QPropertyAnimation>
#include <QList>

using namespace std;

Poison::Poison(QPoint position, int targetRadius, int damage, MainWindow *game)
    : m_pos(position)
    , m_game(game)
    , m_damage(damage)
    , m_targetRadius(targetRadius)
{
    m_currentRadius = 0;
    m_game2 = NULL;
}

Poison::Poison(QPoint position, int targetRadius, int damage, MainWindow2*game)
    : m_pos(position)
    , m_game2(game)
    , m_damage(damage)
    , m_targetRadius(targetRadius)
{
    m_currentRadius = 0;
    m_game = NULL;
}

void Poison::move()
{
    static const int duration = 800;

    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentRadius");
    animation->setDuration(duration);
    animation->setStartValue(0);
    animation->setEndValue(m_targetRadius);

    connect(animation, SIGNAL(finished()),this,SLOT(hitTarget()));

    animation->start();
}

void Poison::hitTarget()
{
    if( m_game != NULL)
    {
        m_game->poisonEffect(this);
    }
    else m_game2->poisonEffect(this);
}

void Poison::draw(QPainter *painter)
{
    painter->save();

    painter->setPen(QColor(128,0,128));
    QPen pen = painter->pen();
    pen.setWidth(40);
    painter->setPen(pen);
    painter->drawEllipse(m_pos, m_currentRadius,m_currentRadius);

    pen.setColor(QColor(128,0,128));
    pen.setWidth(60);
    painter->setPen(pen);
    painter->setOpacity(0.75);
    painter->drawEllipse(m_pos, m_currentRadius-50,m_currentRadius-50);

    painter->restore();
}
