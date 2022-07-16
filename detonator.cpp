
#include "detonator.h"

Detonator::Detonator(QPointF startPos) : ItemBT(startPos, new QImage("../bubbletroubleqt/img/items/trigger.png")){
}

QRectF Detonator::boundingRect() const{
    return QRectF(0,0,32,48);
}

void Detonator::onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles){
    boom(bubbles);
}

bool Detonator::canPickUp(Player *player){
    return true;
}

void Detonator::boom(QList<Bubble *> &bubbles){
    for(Bubble *b : bubbles){
        delete b;
    }


}
