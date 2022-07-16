#include "haste.h"

Haste::Haste(QPointF startPos) : Powerup(startPos, new QImage("../bubbletroubleqt/img/items/haste.png"), 10000) {
}

QRectF Haste::boundingRect() const {
    return QRectF(4,0,28,32);
}

void Haste::enableEffect(){
    getOwner()->setSpeed(getOwner()->getSpeed()*2);
}

void Haste::disableEffect(){
    getOwner()->setSpeed(getOwner()->getSpeed()*0.5f);
}

bool Haste::canPickUp(Player *player){
    return player->getSpeed()*2 < 5;
}
