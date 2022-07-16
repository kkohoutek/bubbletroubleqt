#include "itembt.h"
#include <QPainter>

ItemBT::ItemBT(QPointF startPos, QImage *image){

    setPos(startPos);
    this->image = image;
}

ItemBT::~ItemBT(){
    delete image;
}

void ItemBT::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawImage(0 ,0, *image);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void ItemBT::fall(){
    moveBy(0, FALLSPEED);
}

