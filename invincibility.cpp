#include "invincibility.h"

Invincibility::Invincibility(QPointF startPos) : Powerup(startPos, new QImage("../bubbletroubleqt/img/items/shield.png"), 7000){}

QRectF Invincibility::boundingRect() const {
    return QRectF(4,0, 44,40);
}


void Invincibility::enableEffect(){
    getOwner()->setInvincible(true);
}

void Invincibility::disableEffect(){
    getOwner()->setInvincible(false);
}

bool Invincibility::canPickUp(Player *player){
    return !player->isInvincible();
}
