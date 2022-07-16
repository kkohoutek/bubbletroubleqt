#ifndef INVINCIBILITY_H
#define INVINCIBILITY_H

#include "powerup.h"

// Nesrmtelnost

class Invincibility : public Powerup
{
public:
    Invincibility(QPointF startPos);

    QRectF boundingRect() const override;

    // ItemBT interface
    bool canPickUp(Player *player) override;


protected:
    void enableEffect() override;
    void disableEffect() override;


};

#endif // INVINCIBILITY_H
