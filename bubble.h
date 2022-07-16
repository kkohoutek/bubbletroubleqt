#ifndef BUBBLE_H
#define BUBBLE_H

#define BUBBLE_DIVISION_KNOCKBACK -3.325f

#include <QGraphicsEllipseItem>
#include <QVector2D>

class Bubble : public QGraphicsEllipseItem
{
public:
    Bubble(QPointF startPos, int dir_x, int divisions, Qt::GlobalColor color);
    Bubble(QPointF startPos, QVector2D *vel, int divisions, Qt::GlobalColor color);
    ~Bubble();


    void                    move(const float GRAVITY);
    void                    bounceX();
    void                    bounceY();
    QList<Bubble *>         makeChildren();


    QVector2D              *velocity();
    int                     getDivisions();
    Qt::GlobalColor         getColor();


protected:
    int                     divisions;
    Qt::GlobalColor         color;
    QVector2D              *vel;


};

#endif // BUBBLE_H
