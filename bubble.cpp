
#include <QBrush>
#include <QPainter>
#include "bubble.h"

Bubble::Bubble(QPointF startPos, int dir_x, int divisions, Qt::GlobalColor color) {
    this->divisions = divisions;
    this->color = color;
    setPos(startPos);
    setRect(0,0,((divisions+1)*12),((divisions+1)*12));
    setBrush(QBrush(color));

    vel = new QVector2D(dir_x, 0);
}

Bubble::Bubble(QPointF startPos, QVector2D *vel, int divisions, Qt::GlobalColor color) {
    this->divisions = divisions;
    this->color = color;
    setPos(startPos);
    setRect(0,0,((divisions+1)*12),((divisions+1)*12));
    setBrush(QBrush(color));

    this->vel = vel;
}

Bubble::~Bubble(){
    delete vel;
}


void Bubble::move(const float GRAVITY){
    moveBy(vel->x(), vel->y());
    vel->setY(vel->y() + GRAVITY);
}

void Bubble::bounceX(){
    vel->setX(-vel->x());
}

void Bubble::bounceY(){
    if(vel->y() > 0){
        vel->setY(-divisions-1-1.6f);
    } else {
        vel->setY(-vel->y());
    }
}

QList<Bubble *> Bubble::makeChildren(){
    QList<Bubble *> children;
    Bubble *left = new Bubble(pos() + QPointF(-1,0), new QVector2D(-1, BUBBLE_DIVISION_KNOCKBACK), divisions-1, color);
    Bubble *right = new Bubble(pos() + QPointF(1,0), new QVector2D(1, BUBBLE_DIVISION_KNOCKBACK), divisions-1, color);

    children.append(left);
    children.append(right);
    return children;
}

Qt::GlobalColor Bubble::getColor() {
    return color;
}

QVector2D *Bubble::velocity(){
    return vel;
}

int Bubble::getDivisions(){
    return divisions;
}

