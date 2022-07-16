#include "shot.h"
#include <QPen>


Shot::Shot(QPointF playerPos, QRectF playerBoundingRect, int speed, Qt::GlobalColor color){
    this->speed = speed;
    setPen(QPen(color));
    setLine(playerPos.x() + playerBoundingRect.width()/2 + 4, playerPos.y() + playerBoundingRect.height(), playerPos.x() + playerBoundingRect.width()/2 + 4, playerPos.y()-1);
}


void Shot::fly() {
    setLine(line().x1(), line().y1(), line().x2(), line().y2() - speed);
}

int Shot::getSpeed(){
    return speed;
}
