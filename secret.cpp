#include "secret.h"


Secret::Secret(QPointF startPos) : ItemBT(startPos, new QImage("../bubbletroubleqt/img/items/shummi.png")){}

QRectF Secret::boundingRect() const{
    return QRectF(0,0,64,64);
}

void Secret::onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles){
    Q_UNUSED(owner);
    Q_UNUSED(bubbles);
    score *= 2;
    delete this;
}

bool Secret::canPickUp(Player *player){
    return true;
}


