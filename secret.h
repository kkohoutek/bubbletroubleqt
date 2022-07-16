#ifndef SECRET_H
#define SECRET_H

#include "itembt.h"

// double the score

class Secret : public ItemBT
{
public:
    Secret(QPointF pos);

    // QGraphicsItem interface
    QRectF boundingRect() const override;

    // ItemBT interface
    void onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles) override;

    bool canPickUp(Player *player);
};


#endif // SECRET_H
