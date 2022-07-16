#ifndef BUBBLETROUBLE_H
#define BUBBLETROUBLE_H

#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include <QGraphicsItemGroup>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "player.h"
#include "bubble.h"
#include "shot.h"
#include "itembt.h"


class BubbleTrouble : public QGraphicsView
{
public:
    BubbleTrouble(int numPlayers, int difficulty);
    ~BubbleTrouble();

    bool                     isPaused;

private:
    const float              GRAVITY         =  0.078f;

    int                      updateTimerID;
    int                      difficulty;
    int                      numPlayers;
    unsigned int             score;
    bool                     running;

    Player                  *players[5]      = {NULL, NULL, NULL, NULL, NULL};
    QGraphicsScene          *scene;
    QRectF                  *bounds;

    QList<Bubble *>          bubbles;
    QList<ItemBT *>          items;

    // timers
    QTimer                  *comboTextTimer;
    QTimer                  *gameOverTimer;

    // text items
    QGraphicsSimpleTextItem *scoreText;
    QGraphicsSimpleTextItem *highestScoreText;
    QGraphicsSimpleTextItem *gameOverText;
    QGraphicsSimpleTextItem *comboText;
    QGraphicsSimpleTextItem *diffText;

    // item groups pro zachování pořadí vykreslování
    QGraphicsItemGroup      *bubblesGroup;
    QGraphicsItemGroup      *textGroup;
    QGraphicsItemGroup      *playersGroup;
    QGraphicsItemGroup      *shotsGroup;

    // rozděl bublinu při iteraci qlistem
    void                     divideBubble(QMutableListIterator<Bubble *> &bubble_i);

    // combo při iteraci qlistem
    void                     comboBubble (QMutableListIterator<Bubble *> &bubble_i);

    // přidání do score na základě trefené bubliny
    void                     addToScore  (Bubble *strickenBubble, bool combo);

    // přidání do score
    void                     addToScore  (const int amount);

    // spawnuj random bubliny na základě obtížnosti
    void                     spawnBubbles();

    // updates
    void                     updateBubbles();
    void                     updateItems();
    void                     updatePlayers();

    void                     spawnRandomItem(QPointF pos);
    void                     spawnPlayers();

    void                     gameOver();
    void                     updateScoreText();
    void                     setUpText();
    void                     setUpTimers();


    // Score database

    QSqlDatabase database;
    QSqlQuery query;

    void                     setUpDatabase();
    bool                     saveScore();
    unsigned int             highestScore();


private slots:
    void                     hideComboText();
    void                     restart();

protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // BUBBLETROUBLE_H
