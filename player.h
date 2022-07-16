#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QObject>
#include "shot.h"



class Player : public QObject, public QGraphicsItem
{
public:
    Shot *shot = NULL;

    Player(QPointF startPos, const int id);
    ~Player();

    void move();
    void stop();
    void unstop();
    void goLeft();
    void goRight();

    bool shoot(); // vystřel a vrat true jestli byl výstřel úspěšný

    bool isInvincible();

    int getDirection();
    float getSpeed();
    void setSpeed(float newSpeed);
    void setInvincible(bool invincible);


    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private slots:
    void nextFrame();
    void resume();

private:
    // sprite
    int currentFrame;
    QTimer *animationTimer;
    QTimer *shootHandicapTimer;
    QPixmap *spritesheet;
    QPixmap *walkLeft;
    QPixmap *walkRight;
    QPixmap *idle;

    float speed;
    int dir_x;
    int dir_x_previous;

    bool invincible;

    Qt::GlobalColor shotColor;

};

#endif // PLAYER_H
