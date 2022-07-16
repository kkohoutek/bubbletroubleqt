#ifndef GOLD_H
#define GOLD_H

#include "itembt.h"

// +50 score

class Gold : public ItemBT
{

public:
    Gold(QPointF startPos);

     // QGraphicsItem interface
    QRectF boundingRect() const override;

    // ItemBT interface
    void onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles) override;

    bool canPickUp(Player *player);

};

#endif // GOLD_H
