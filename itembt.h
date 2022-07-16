#ifndef ITEMBT_H
#define ITEMBT_H

#include <qtimer>
#include <qimage>
#include <qgraphicsitem>
#include "player.h"
#include "bubble.h"


// Abstraktní třída pro hráčem zvednutelné předměty.

class ItemBT : public QGraphicsItem
{
public:
    const float             FALLSPEED = 1.5f;

    ItemBT(QPointF startPos, QImage *image);
    virtual                ~ItemBT();

    // co se stane hráčovi a score při zvednutí itemu
    virtual void            onPickedUp(Player *owner, unsigned int &score, QList<Bubble *> &bubbles) = 0;

    // true pokud hráč může item sebrat
    virtual bool            canPickUp(Player *player) = 0;

    // pohyb itemu
    void                    fall();



    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QImage                 *image;


};


#endif // ITEMBT_H
