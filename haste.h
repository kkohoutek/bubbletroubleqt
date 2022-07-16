#ifndef HASTE_H
#define HASTE_H

#include "powerup.h"

// 2x rychlost

class Haste : public Powerup
{
public:
    Haste(QPointF startPos);

    QRectF boundingRect() const override;

    bool canPickUp(Player *player);

protected:
    void enableEffect() override;
    void disableEffect() override;

};

#endif // HASTE_H
