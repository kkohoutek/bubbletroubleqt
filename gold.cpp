#include "gold.h"


Gold::Gold(QPointF startPos) : ItemBT(startPos, new QImage("../bubbletroubleqt/img/items/gold.png")) {

}

QRectF Gold::boundingRect() const {
    return QRectF(0,0,20,20);
}

void Gold::onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles) {
    Q_UNUSED(owner);
    score += 50;
    delete this;
}

bool Gold::canPickUp(Player *player){
    return true;
}
