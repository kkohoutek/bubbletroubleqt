#include "player.h"
#include <QPainter>
#include <QObject>
#include <QDebug>

Player::Player(QPointF startPos, const int id) : QObject(), QGraphicsItem() {
    currentFrame = 0;
    dir_x = 0;
    speed = 1.25f;
    invincible = false;

    QString folder("../bubbletroubleqt/img/player" + QString::number(id) + "/");

    idle = new QPixmap(folder + "IDLE.png");
    walkLeft = new QPixmap(folder + "WALKLEFT.png");
    walkRight = new QPixmap(folder + "WALKRIGHT.png");

    switch(id){
    case 1:
        shotColor = Qt::red;
        break;
    case 2:
        shotColor = Qt::blue;
        break;
    case 3:
        shotColor = Qt::black;
        break;
    case 4:
        shotColor = Qt::yellow;
        break;
    case 5:
        shotColor = Qt::green;
        break;
    }

    spritesheet = idle;

    animationTimer = new QTimer(this);
    shootHandicapTimer = new QTimer(this);

    connect(animationTimer, &QTimer::timeout, this, &nextFrame);
    connect(shootHandicapTimer, &QTimer::timeout, this, &resume);
    animationTimer->start(220);

    setPos(startPos);
}

Player::~Player(){
    delete animationTimer;
    delete shootHandicapTimer;
    delete shot;
    delete idle;
    delete walkLeft;
    delete walkRight;
}

QRectF Player::boundingRect() const {
    return QRectF(4,2, 14,35);
}

void Player::move(){
    moveBy(speed*dir_x, 0);
    if      (dir_x ==  0 && spritesheet != idle)      spritesheet = idle;
    else if (dir_x == -1 && spritesheet != walkLeft)  spritesheet = walkLeft;
    else if (dir_x ==  1 && spritesheet != walkRight) spritesheet = walkRight;

}

void Player::stop(){
    dir_x_previous = dir_x;
    dir_x = 0;
}

void Player::unstop(){
    if(dir_x == 0){
        dir_x = dir_x_previous;
    }
}

void Player::goLeft(){
    dir_x = -1;
}
void Player::goRight(){
    dir_x = 1;
}

bool Player::shoot(){
    if(shot == NULL){
        shot = new Shot(pos(), boundingRect(), 6, shotColor);
        stop();
        shootHandicapTimer->start(110);
        return true;
    }
    return false;

}

bool Player::isInvincible(){
    return invincible;
}

int Player::getDirection(){
    return dir_x;
}

float Player::getSpeed(){
    return speed;
}

void Player::setSpeed(float newSpeed){
    speed = newSpeed;
}

void Player::setInvincible(bool invincible){
    this->invincible = invincible;

}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(spritesheet == idle){
        currentFrame = 0;
    }
    painter->drawPixmap(0,0, *spritesheet, currentFrame, 0, 23, 37);
    //painter->drawRect(boundingRect());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Player::nextFrame(){
    if(currentFrame >= 23){
        currentFrame = 0;
    } else {
        currentFrame += 23;
    }
}

void Player::resume(){
    unstop();
    shootHandicapTimer->stop();
}
