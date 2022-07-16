#ifndef SILVER_H
#define SILVER_H

#include "itembt.h"

// + 10 score

class Silver : public ItemBT
{
public:
    Silver(QPointF startPos);

    // QGraphicsItem interface
    QRectF boundingRect() const override;

    // ItemBT interface
    void onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles) override;

    bool canPickUp(Player *player);
};

#endif // SILVER_H
