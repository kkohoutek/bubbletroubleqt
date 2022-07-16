#ifndef DETONATOR_H
#define DETONATOR_H

#include "itembt.h"



class Detonator : public ItemBT
{
public:
    Detonator(QPointF startPos);

    // QGraphicsItem interface
    QRectF boundingRect() const;

    // ItemBT interface
    void onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles);
    bool canPickUp(Player *player);

private:
    void boom(QList<Bubble *> &bubbles);
};

#endif // DETONATOR_H
