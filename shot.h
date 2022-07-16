#ifndef SHOT_H
#define SHOT_H
#include <QGraphicsLineItem>

class Shot : public QGraphicsLineItem
{
public:
    Shot(QPointF playerPos, QRectF playerBoundingRect, int speed, Qt::GlobalColor color);
    void fly();
    int getSpeed();

private:
    int speed;

};

#endif // SHOT_H
