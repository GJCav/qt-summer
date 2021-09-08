#include "GameScene.h"
#include "GameProp.h"
#include "GameCharacter.h"
#include "item/MeowKnightItem.h"
#include "item/CellIndicatorItem.h"
#include "HUD.h"
#include "EnemyAI.h"
#include "ai/BaseAI.h"
#include "R.h"
#include "special/OrangeMeow.h"
#include "special/AthleteMeow.h"
#include "special/DoctorMeow.h"
#include "special/BossMeow.h"
#include <QAction>
#include <QQueue>

GameScene::GameScene(QObject *parent) : QGraphicsScene(parent)
{
    setSceneRect(0, 0, 1024, 768);
}

Level *GameScene::level() const
{
    return mLevel;
}


const QVector<GameCharacter *> &GameScene::chars() const
{
    return mChars;
}

const QVector<GameProp *> &GameScene::props() const
{
    return mProps;
}

void GameScene::addProp(GameProp *prop)
{
    prop->setParent(this);
    mProps.append(prop);
    addItem(prop->propItem());

}

void GameScene::addChar(GameCharacter *ch)
{
    mChars.append(ch);
    ch->setParent(this);
    connect(ch, &GameCharacter::clicked, this, &GameScene::charClick);
    connect(ch, &GameCharacter::selectedChange, this, &GameScene::charSelectedChange);

    addItem(ch->charItem());
}

GameProp *GameScene::propAt(const QPoint h) const
{
    for(int i = 0;i < mProps.size();i++){
        //qDebug() << mProps[i]->pos() << ", is: " << mProps[i]->propType();
        if(mProps[i]->pos() == h) return mProps[i];
    }
    return nullptr;
}

GameCharacter *GameScene::charAt(const QPoint h) const
{
    for(int i = 0;i < mChars.size();i++){
        if(mChars[i]->pos() == h) return mChars[i];
    }
    return nullptr;
}

QVector<tuple<QPoint, GameScene::MoveDestType>>
GameScene::listMoveDestination(const QPoint origin, const int max, const int min)
{
    QVector<tuple<QPoint, MoveDestType>> rst;

    QVector<QVector<int>> dis;

    for(int i = 0;i < GameHeight;i++){
        dis.append(QVector<int>{});
        for(int j = 0;j < GameWidth;j++){
            dis[i].append(-1); // -1: unreached
        }
    }

    QPoint h = origin;
    QQueue<QPoint> que;
    que.append(h);
    dis[h.y()][h.x()] = 0;

    constexpr static int dirX[] = {-1, 0, 1, 0};
    constexpr static int dirY[] = {0, -1, 0, 1};

    while(que.size()){
        h = que.dequeue();

        MoveDestType destType = MoveDestType::Unreachable;

        // can stand at h?
        GameProp* prop = nullptr;
        if((prop = propAt(h)) != nullptr && dis[h.y()][h.x()] >= min){
            destType = MoveDestType::Invalid;
        }
        GameCharacter* gc = nullptr;
        if((gc = charAt(h)) != nullptr && gc->pos() != origin && dis[h.y()][h.x()] >= min){
            destType = MoveDestType::Invalid;
        }
        if(destType == MoveDestType::Invalid){
            rst.append({h, destType});
            continue;
        }

        // come to a new valid pos
        if(dis[h.y()][h.x()] >= min){
            destType = MoveDestType::Valid;
            rst.append({h, destType});
        }

        const int newDis = dis[h.y()][h.x()] + 1;
        if(newDis > max) continue;
        for(int i = 0;i < 4;i++){
            QPoint newPos = {h.x()+dirX[i], h.y()+dirY[i]};
            if(newPos.x() < 0 || newPos.x() >= GameWidth) continue;
            if(newPos.y() < 0 || newPos.y() >= GameHeight) continue;

            if(dis[newPos.y()][newPos.x()] != -1) continue;
            dis[newPos.y()][newPos.x()] = newDis;
            que.enqueue(newPos);
        }
    }

    return rst;
}

void GameScene::selectMoveDestination(const QPoint origin, const int len, const int min)
{
    deleteItemGroup(mSltIndicate);
    mSltIndicate = new QGraphicsItemGroup();
    mSltIndicate->setZValue(GroundEffect);
    mSltIndicate->setHandlesChildEvents(false);
    addItem(mSltIndicate);

    auto list = listMoveDestination(origin, len, min);
    for(int i = 0;i < list.size();i++){
        QPoint p;
        MoveDestType type;
        std::tie(p, type) = list[i];

        if(type == MoveDestType::Invalid){
            auto cellIdr = new CellIndicatorItem(p, mSltIndicate);
            cellIdr->setColor(Qt::red);
        }else if(type == MoveDestType::Valid){
            auto cellIdr = new CellIndicatorItem(p, mSltIndicate);
            cellIdr->setColor(Qt::blue);
            connect(cellIdr, &CellIndicatorItem::clicked, cellIdr, [this](CellIndicatorItem*src){
                emit moveDestSelected(src->gamePos());
                deleteItemGroup(mSltIndicate);
            }, Qt::SingleShotConnection);
        }
    }
}

void GameScene::selectReachableCharacter(
    const QPoint origin,
    const int max,
    const int min,
    QColor targetColor,
    QColor lightColor
)
{
    deleteItemGroup(mSltIndicate);
    mSltIndicate = new QGraphicsItemGroup();
    mSltIndicate->setZValue(GroundEffect);
    mSltIndicate->setHandlesChildEvents(false);
    addItem(mSltIndicate);

    for(int i = origin.y()-max;i <= origin.y()+max;i++){
        if(i < 0 || i >= GameHeight) continue;
        for(int j = origin.x()-max;j <= origin.x()+max;j++){
            if(j < 0 || j >= GameWidth) continue;
            const int dis = qAbs(j - origin.x()) + qAbs(i - origin.y());
            const QPoint h{j, i};
            if(dis < min || dis > max) continue;

            auto cellIdr = new CellIndicatorItem(h, mSltIndicate);

            GameCharacter* c = charAt(h);
            if(c != nullptr){
                cellIdr->setColor(targetColor);
                cellIdr->setHightLight(true);
                connect(cellIdr, &CellIndicatorItem::clicked, cellIdr, [this, c](CellIndicatorItem* src){
                    emit charSelected(c);
                    deleteItemGroup(mSltIndicate);
                }, Qt::SingleShotConnection);
            }else{
                cellIdr->setColor(lightColor);
                //do nothing
//                connect(cellIdr, &CellIndicatorItem::clicked, cellIdr, [this](CellIndicatorItem* src){
//                    deleteItemGroup(mSltIndicate);
//                }, Qt::SingleShotConnection);
            }
        }
    }
}

void GameScene::cancelSelectProcess()
{
    deleteItemGroup(mSltIndicate);
}

void GameScene::charClickedEvent(GameCharacter *src)
{
    if(mState == 0){
        if(!hud->visible()) hud->toggleHUD();
        hud->setTitle(src->name());
        hud->setIcons(src->requestIcons());
        hud->setStatusName(src->name());
        hud->setStatusHealth(src->health());
        hud->setStatusSpeed(src->speed());
        hud->setStatusDefensive(src->defensivePower());
        hud->setStatusAttack(src->attackPower());
        hud->setStatusLucky(src->lucky());

        if(src->charRole() == GameCharacter::CharacterRole::Player1){
            hud->setActBtns(src->requestActionMenu());
        }else{
            hud->setActBtns({});
        }
    }else if(mState == 3){
        if(!hud->visible()) hud->toggleHUD();
        hud->setTitle(src->name());
        hud->setIcons(src->requestIcons());
        hud->setStatusName(src->name());
        hud->setStatusHealth(src->health());
        hud->setStatusSpeed(src->speed());
        hud->setStatusDefensive(src->defensivePower());
        hud->setStatusAttack(src->attackPower());
        hud->setStatusLucky(src->lucky());

        hud->setActBtns({});
    }
}

void GameScene::endTurnEvent()
{
    mTurn++;
    for(int i = 0;i < mChars.size();i++){
        mChars[i]->endTurn();
    }
    clearSelection();
    mLastClickChar = nullptr;

    // now is AI's turn.
    beginAITurn();
}

void GameScene::beginAITurn()
{
    mState = 3;
    hud->setAllowEndTurn(false);
    hud->setActBtns({});
    hud->setActBtnVisible(false);

    mAI->start();
}

void GameScene::endAITurn()
{
    mState = 0;
    hud->setAllowEndTurn(true);
    hud->setActBtnVisible(true);
}

void GameScene::init()
{
    initLevel();
    initPropItems();
    initChars();
    initHUD();
    initAI();
}


void GameScene::initLevel()
{
    mLevel = new Level();
    mLevel->initLevel(GameWidth, GameHeight);
    mLevel->setStonePath(QRect(1, 2, 5, 4));
    mLevel->setWallRect(QRect(0, 0, 16, 12));
    mLevel->setScene(this);
}

void GameScene::initPropItems()
{
    auto chestProp = new GameProp(this, GameProp::PropType::Chest);
    chestProp->setPos({3, 4});
    addProp(chestProp);

    auto magicProp = new GameProp(this, GameProp::PropType::Magic);
    magicProp->setPos({1, 6});
    addProp(magicProp);

    auto stoneProp = new GameProp(this, GameProp::PropType::Stone);
    stoneProp->setPos(8, 8);
    addProp(stoneProp);
}

void GameScene::initChars()
{
    MeowKnightItem *meow = new MeowKnightItem("grey");
    GameCharacter *ch = new GameCharacter(meow, this, GameCharacter::CharacterRole::Player1);
    addChar(ch);
    ch->setPos({3, 3});

    meow = new MeowKnightItem("grey");
    ch = new OrangeMeow(meow, this, GameCharacter::CharacterRole::Player1);
    addChar(ch);
    ch->setPos({6, 6});

    meow = new MeowKnightItem("grey");
    ch = new AthleteMeow(meow, this, GameCharacter::CharacterRole::Player1);
    addChar(ch);
    ch->setPos({6, 2});

    meow = new MeowKnightItem("grey");
    ch = new DoctorMeow(meow, this, GameCharacter::CharacterRole::Player1);
    addChar(ch);
    ch->setPos({4, 2});

    ch = new BossMeow(this);
    ch->setPos({8, 3});
    ch->setTowards(false);
    addChar(ch);
}

void GameScene::initHUD()
{
    hud = new HUD(this);
    connect(hud, &HUD::clickedEndTurn, this, &GameScene::endTurn);
}

void GameScene::initAI()
{
    mAI = new BaseAI(this);
    connect(mAI, &EnemyAI::AITurnFinished, this, &GameScene::endAITurn);
}

void GameScene::charClick(GameCharacter *src)
{
    if(mProcessCharClick){
        if(mLastClickChar == src){
            //qDebug("click on same character..");
            return;
        }
        mLastClickChar = src;
        charClickedEvent(src);
        emit charClicked(src);
    }
}

void GameScene::endTurn()
{
    endTurnEvent();
}

void GameScene::AITurnEnded()
{
    endAITurn();
}

void GameScene::charSelectedChange(bool slt)
{
    if(mAllowUnselectChar && slt == false){
        //qDebug("cancel selection..");

        hud->setTitle("-/-");
        hud->setIcons({});
        hud->setStatusName("-/-");
        hud->setStatusHealth("-/-");
        hud->setStatusSpeed("-/-");
        hud->setStatusDefensive("-/-");
        hud->setStatusAttack("-/-");
        hud->setStatusLucky("-/-");
        hud->setActBtns({});

        mLastClickChar = nullptr;
    }
}

bool GameScene::allowOpenHUD() const
{
    return mAllowOpenHUD;
}

void GameScene::setAllowOpenHUD(bool newAllowOpenHUD)
{
    mAllowOpenHUD = newAllowOpenHUD;
}

bool GameScene::allowUnselectChar() const
{
    return mAllowUnselectChar;
}

void GameScene::setAllowUnselectChar(bool newAllowUnselectChar)
{
    mAllowUnselectChar = newAllowUnselectChar;
}

bool GameScene::processCharClick() const
{
    return mProcessCharClick;
}

void GameScene::setProcessCharClick(bool newEnableCharClick)
{
    mProcessCharClick = newEnableCharClick;
}

HUD *GameScene::getHUD() const
{
    return hud;
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_H){
        if(hud->visible() == false && mAllowOpenHUD == false){
            //qDebug("keyboard tried to open HUD but is stopped.");
            return;
        }
        hud->toggleHUD();
    }else if(event->key() == Qt::Key_Escape){
        emit escKeyPressed();
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::deleteItemGroup(QGraphicsItemGroup *&group)
{
    if(group == nullptr) return;
    auto list = group->childItems();
    destroyItemGroup(group);
    for(int i = 0;i < list.size();i++){
        removeItem(list[i]);
        delete list[i];
    }
    group = nullptr;
}


