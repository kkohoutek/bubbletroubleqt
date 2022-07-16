#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QTime>

#include "bubbletrouble.h"
#include "bubble.h"
#include "shot.h"
#include "haste.h"
#include "invincibility.h"
#include "gold.h"
#include "silver.h"
#include "secret.h"
#include "detonator.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#define CHANCE_TO_DROP 28
#define SECRET_CHANCE_TO_DROP 1 // shummi
#define ITEMS_MAX_ONSCREEN 4


BubbleTrouble::BubbleTrouble(int numPlayers, int difficulty) {
    this->difficulty = difficulty;
    this->numPlayers = numPlayers;
    score = 0;
    isPaused = false;

    scene = new QGraphicsScene(this);
    bounds = new QRectF(0,0,800,550);

    bubblesGroup = new QGraphicsItemGroup();
    shotsGroup = new QGraphicsItemGroup();
    playersGroup = new QGraphicsItemGroup();
    textGroup = new QGraphicsItemGroup();

    scene->setBackgroundBrush(QBrush(QImage("../bubbletroubleqt/img/bg3.jpg")));
    scene->addRect(*bounds);
    scene->addPixmap(QPixmap("../bubbletroubleqt/img/spikes.png"));

    setUpDatabase();
    setUpText();
    setUpTimers();
    spawnPlayers();
    spawnBubbles();

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    if(numPlayers == 5) {
        setMouseTracking(true);
    }

    updateTimerID = startTimer(1000/60);
    setScene(scene);

}

BubbleTrouble::~BubbleTrouble(){
    delete bounds;
    delete scoreText;
    delete comboText;
    delete comboTextTimer;
    delete gameOverTimer;


    for(Bubble *b : bubbles){
        delete b;
    }
    for(ItemBT *i : items){
        delete i;
    }
    for(int i = 0; i < 5; i++){
        delete players[i];
        players[i] = NULL;
    }


}

void BubbleTrouble::spawnPlayers(){
    for(int i = 0; i < numPlayers; i++){
        players[i] = new Player(QPointF(525+i*20,513), (i+1));
        playersGroup->addToGroup(players[i]);
    }
}


void BubbleTrouble::spawnBubbles(){
    // fairplay
    for(Player *p : players){
        if(p == NULL) break;
        Invincibility *i = new Invincibility(QPointF(p->x(),150));
        //i->onPickedUp(p, score);
        items.append(i);
        scene->addItem(i);
    }

    qsrand(QTime::currentTime().msec());
    int count = qrand() % difficulty + 1;
    while(count > 0){
        QPointF pos;
        int divisions = qrand() % 5 + 1;

        pos.setX(qrand() % 700);
        pos.setY(qrand() % 60 + (divisions+1)*12);
        int dirs[2] = {-1,1}; // 2 možné směry na ose x

        Qt::GlobalColor bubbleColors[4] = {Qt::red, Qt::blue, Qt::yellow, Qt::green};

        Bubble *bubble = new Bubble(pos, dirs[qrand()%2], divisions, bubbleColors[qrand()%4]);
        bubbles.append(bubble);
        bubblesGroup->addToGroup(bubble);
        count--;
    }
}



void BubbleTrouble::divideBubble(QMutableListIterator<Bubble *> &bubble_i){
    Bubble *bubble = bubble_i.previous();
    scene->removeItem(bubble);
    bubblesGroup->removeFromGroup(bubble);
    bubble_i.remove();

    addToScore(bubble, false);
    if(bubble->getDivisions() == 0) return;

    if(items.size() < ITEMS_MAX_ONSCREEN && bubble->getDivisions() > 1){
        spawnRandomItem(bubble->pos());
    }

    QList<Bubble *> children = bubble->makeChildren();
    bubblesGroup->addToGroup(children.at(0));
    bubblesGroup->addToGroup(children.at(1));
    bubbles.append(children.at(0));
    bubbles.append(children.at(1));

    delete bubble;
}

void BubbleTrouble::comboBubble(QMutableListIterator<Bubble *> &bubble_i){
    Bubble *bubble = bubble_i.previous();
    bubble_i.remove();
    scene->removeItem(bubble);
    bubblesGroup->removeFromGroup(bubble);

    addToScore(bubble, true);

    comboText->show();
    comboTextTimer->start();
    delete bubble;
}

void BubbleTrouble::spawnRandomItem(QPointF pos){
    if(CHANCE_TO_DROP <= 0) return;

    ItemBT *item;
    int randomness = qrand() % (100/CHANCE_TO_DROP);
    if(randomness == 0){
        int itemId = qrand() % 4;
        switch(itemId){
            case 0:
                item = new Gold(pos);
                break;
            case 1:
                item = new Silver(pos);
                break;
            case 2:
                item = new Haste(pos);
                break;
            case 3:
                item = new Invincibility(pos);
                break;

        }
        scene->addItem(item);
        items.append(item);

    } else {
        if(SECRET_CHANCE_TO_DROP <= 0) return;

        qsrand(QTime::currentTime().msec());
        randomness = qrand() % (100/SECRET_CHANCE_TO_DROP);

        if(randomness == 0){
            item = new Secret(pos);
            scene->addItem(item);
            items.append(item);
        }
    }
}


void BubbleTrouble::timerEvent(QTimerEvent *event) {
    if(isPaused) return;

    updatePlayers();
    updateBubbles();
    updateItems();
    viewport()->update();

    Q_UNUSED(event)
}
void BubbleTrouble::updateBubbles(){
    if(bubbles.size() == 0) spawnBubbles();

    QMutableListIterator<Bubble *> bubble_i(bubbles);
    while(bubble_i.hasNext()){
        Bubble *bubble = bubble_i.next();

        QPointF bubbleNextPos(bubble->pos() + bubble->velocity()->toPointF());
        if(bubbleNextPos.x() + bubble->rect().width() >= bounds->right() || bubbleNextPos.x() <= bounds->left()){
            bubble->bounceX();
        }
        if (bubbleNextPos.y() + bubble->rect().height() >= bounds->bottom()){
            bubble->bounceY();

        }
        bubble->move(GRAVITY);
        if (bubbleNextPos.y() <= bounds->top()){
            comboBubble(bubble_i);
        }
    }
}

void BubbleTrouble::updateItems(){
    for(ItemBT *item : items){
        if (bounds->contains(item->boundingRect().translated(item->pos() + QPointF(0,item->FALLSPEED)))){
            item->fall();
        }
    }
}

void BubbleTrouble::updatePlayers(){
    for(Player *player : players){
        if(player == NULL) break;

        if(!bounds->contains(player->boundingRect().translated(player->pos() + QPointF(player->getSpeed()*player->getDirection(),0)))){
            player->stop();
        } else {
            player->move();
        }
        if(player->shot != NULL){
            if(!bounds->contains(player->shot->line().p2() - QPointF(0,player->shot->getSpeed()))){
                scene->removeItem(player->shot);
                shotsGroup->removeFromGroup(player->shot);
                delete player->shot;
                player->shot = NULL;

            } else {
                player->shot->fly();
            }
        }

        QMutableListIterator<Bubble *> bubble_i(bubbles);
        while(bubble_i.hasNext()){
            Bubble *bubble = bubble_i.next();

            if(!player->isInvincible() && player->collidesWithItem(bubble)){
                gameOver();
                return;
            }
            if(player->shot != NULL && player->shot->collidesWithItem(bubble)){
                divideBubble(bubble_i);
                scene->removeItem(player->shot);
                shotsGroup->removeFromGroup(player->shot);
                player->shot = NULL;
                break;
            }

        }

        QMutableListIterator<ItemBT *> item_i(items);
        while(item_i.hasNext()){
            ItemBT *item = item_i.next();

            if(item->canPickUp(player) && player->collidesWithItem(item)){
                scene->removeItem(item);
                item_i.remove();
                item->onPickedUp(player, score, bubbles);
                updateScoreText();
            }
        }
    }
}

void BubbleTrouble::addToScore(Bubble *strickenBubble, bool combo){
    int add = strickenBubble->getDivisions()+1;
    if(combo) add *= 3;
    score += add;
    updateScoreText();
}
void BubbleTrouble::addToScore(const int amount){
    score += amount;
    updateScoreText();
}


void BubbleTrouble::gameOver(){
    QObject::killTimer(updateTimerID);
    saveScore();
    gameOverTimer->start();
    gameOverText->show();
}

void BubbleTrouble::restart(){
    for(Bubble *b : bubbles){
        scene->removeItem(b);
        bubblesGroup->removeFromGroup(b);
        delete b;
    }
    for(Player *p : players){
        if(p != NULL){
            scene->removeItem(p);
            playersGroup->removeFromGroup(p);
            if(p->shot != NULL){
                scene->removeItem(p->shot);
                shotsGroup->removeFromGroup(p->shot);
                delete p->shot;
            }
        }
    }
    for(ItemBT *i : items){
        scene->removeItem(i);
        delete i;
    }
    items.clear();
    bubbles.clear();

    gameOverText->hide();
    score = 0;
    scoreText->setText(QString("Score: 0"));
    highestScoreText->setText(QString("Highest score: ") + QString::number(highestScore()));

    spawnPlayers();
    spawnBubbles();
    updateTimerID = startTimer(16);
}

void BubbleTrouble::updateScoreText(){
    scoreText->setText(QString("Score: ") + QString::number(score));
}

void BubbleTrouble::setUpText(){
    scoreText = new QGraphicsSimpleTextItem(QString("Score: 0"));
    scoreText->setPos(18,18);
    scoreText->setScale(2);
    textGroup->addToGroup(scoreText);

    highestScoreText = new QGraphicsSimpleTextItem(QString("Highest score: ")+QString::number(highestScore()));
    highestScoreText->setPos(18,36);
    highestScoreText->setScale(2);
    textGroup->addToGroup(highestScoreText);

    gameOverText = new QGraphicsSimpleTextItem(QString("GAME OVER!"));
    gameOverText->setScale(4);
    gameOverText->setPos(290,230);
    gameOverText->hide();
    textGroup->addToGroup(gameOverText);

    comboText = new QGraphicsSimpleTextItem(QString("Combo!"));
    comboText->setScale(1.5f);
    comboText->setPos(bounds->center().x(),38);
    comboText->hide();
    textGroup->addToGroup(comboText);

    diffText = new QGraphicsSimpleTextItem(QString("Difficulty ")+QString::number(difficulty));
    diffText->setPos(680, 18);
    diffText->setScale(2);
    textGroup->addToGroup(diffText);
}

void BubbleTrouble::setUpTimers(){
    comboTextTimer = new QTimer(this);
    comboTextTimer->setSingleShot(true);
    comboTextTimer->setInterval(1000);

    gameOverTimer = new QTimer(this);
    gameOverTimer->setSingleShot(true);
    gameOverTimer->setInterval(3000);

    connect(comboTextTimer, &QTimer::timeout, this, &hideComboText);
    connect(gameOverTimer, &QTimer::timeout, this, &restart);

    scene->addItem(shotsGroup);
    scene->addItem(playersGroup);
    scene->addItem(bubblesGroup);
    scene->addItem(textGroup);
}


void BubbleTrouble::hideComboText(){
    comboText->hide();
}



/* ================ CONTROLS ================ */
void BubbleTrouble::keyPressEvent(QKeyEvent *event) {
    if(isPaused) return;


    Player *p1 = players[0];

    switch(event->key()){
        case Qt::Key_A:
            p1->goLeft();
            break;
        case Qt::Key_D:
            p1->goRight();
            break;
        case Qt::Key_S:
            p1->stop();
            break;
        case Qt::Key_W:
            if(p1->shoot())
                shotsGroup->addToGroup(p1->shot);
            break;
    }

    Player *p2 = players[1];
    if(p2 != NULL) {
        switch(event->key()){
            case Qt::Key_Right:
                p2->goRight();
                break;
            case Qt::Key_Left:
                p2->goLeft();
                break;
            case Qt::Key_Down:
                p2->stop();
                break;
            case Qt::Key_Up:
                if(p2->shoot())
                shotsGroup->addToGroup(p2->shot);
                break;
        }
    } else {
        return;
    }

    Player *p3 = players[2];
    if(p3 != NULL){
        switch(event->key()){
            case Qt::Key_3:
                p3->goRight();
                break;
            case Qt::Key_1:
                p3->goLeft();
                break;
            case Qt::Key_2:
                p3->stop();
                break;
            case Qt::Key_5:
                if(p3->shoot())
                shotsGroup->addToGroup(p3->shot);
                break;
        }
    } else {
        return;
    }

    Player *p4 = players[3];
    if(p4 != NULL){
        switch(event->key()){
            case Qt::Key_L:
                p4->goRight();
                break;
            case Qt::Key_J:
                p4->goLeft();
                break;
            case Qt::Key_K:
                p4->stop();
                break;
            case Qt::Key_I:
                if(p4->shoot())
                shotsGroup->addToGroup(p4->shot);
                break;
        }

    } else {
        return;
    }
}

void BubbleTrouble::mouseMoveEvent(QMouseEvent *event){
    if(isPaused) return;

    Player *p5 = players[4];

    if(p5 != NULL){

        if(event->x() - p5->pos().x() > 0){
            p5->goRight();
        } else {
            p5->goLeft();
        }
    }

}

void BubbleTrouble::mousePressEvent(QMouseEvent *event){
    if(isPaused) return;

    Player *p5 = players[4];

    if(p5 != NULL){

        if(event->button() == Qt::MouseButton::RightButton){
            p5->stop();
        } else if (event->button() == Qt::MouseButton::LeftButton){
            if(p5->shoot())
            shotsGroup->addToGroup(p5->shot);
        }
    }
}

/* ================== DATABASE =================== */
void BubbleTrouble::setUpDatabase(){
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("../bubbletroubleqt/bt.db");
    database.open();
    query = QSqlQuery(database);

    query.prepare("create table scores (score int unsigned, difficulty int)");
    query.exec();
}


bool BubbleTrouble::saveScore(){
    query.prepare("insert into scores values(:sc, :dif)");
    query.bindValue(":sc", score);
    query.bindValue(":dif", difficulty);
    query.exec();
}

unsigned int BubbleTrouble::highestScore(){
    query.prepare("select max(score) from scores where difficulty=:diff");
    query.bindValue(":diff", difficulty);
    query.exec();
    query.first();

    return query.value(0).toUInt();

}




