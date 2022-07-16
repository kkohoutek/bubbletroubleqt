#ifndef POWERUP_H
#define POWERUP_H

#include <QTimer>
#include <QObject>
#include "player.h"
#include "itembt.h"

/*
  Abstraktní třída pro speciální typy itemů - POWERUP.
  Item, který dočasně ovlivňuje atributy svého držitele.
*/

class Powerup : public ItemBT, public QObject
{
public:
    Powerup(QPointF startPos, QImage *image, int duration);
    virtual                ~Powerup();

    // spustí timeToLive, inicializuje atribut owner a zavolá enableEffect
    void                    onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles) override;

    // ItemBT interface
    virtual bool            canPickUp(Player *player) = 0;


protected:

    // spustí efekt powerupu
    virtual void            enableEffect() = 0; 

    // vypne efekt powerupu
    virtual void            disableEffect() = 0;

    Player                 *getOwner();


private:

    // timer pro životnost efektu powerupu
    QTimer                 *timeToLive;

    // pointer na vlastníka powerupu
    // inicializován v onPickedUp
    Player                 *owner;

private slots:

    // slot zavolaný po vypršení životnosti powerupu
    // volá metodu onExpired() a smaže this!
    void                    expire();

};

#endif // POWERUP_H
