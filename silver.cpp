#include "silver.h"


Silver::Silver(QPointF startPos) : ItemBT(startPos, new QImage("../bubbletroubleqt/img/items/silver.png")){

}

QRectF Silver::boundingRect() const {
    return QRectF(0,0,20,20);
}

void Silver::onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles) {
    Q_UNUSED(owner);
    score += 10;
    delete this;
}

bool Silver::canPickUp(Player *player){
    return true;
}
