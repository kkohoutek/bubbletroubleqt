#include "powerup.h"
#include "bubble.h"

Powerup::Powerup(QPointF startPos, QImage *image, int duration) :  ItemBT(startPos, image), QObject() {
    timeToLive = new QTimer(this);
    timeToLive->setInterval(duration);
    timeToLive->setSingleShot(true);

    connect(timeToLive, &QTimer::timeout, this, &expire);

}

Powerup::~Powerup(){
    delete timeToLive;
}

void Powerup::onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles){
    this->owner = owner;
    enableEffect();
    timeToLive->start();
    score++;
}

void Powerup::expire(){
    disableEffect();
    delete this;
}

Player *Powerup::getOwner(){
    return owner;
}
