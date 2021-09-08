#include "GameScene.h"
#include "GameProp.h"
#include "GameCharacter.h"
#include "item/MeowKnightItem.h"
#include "item/CellIndicatorItem.h"
#include "item/TextBoxItem.h"
#include "HUD.h"
#include "EnemyAI.h"
#include "ai/BaseAI.h"
#include "R.h"
#include "special/OrangeMeow.h"
#include "special/AthleteMeow.h"
#include "special/DoctorMeow.h"
#include "special/BossMeow.h"
#include "scene/HelloScene.h"
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
        if(!mLevel->canPlaceGameModel(h)){
            destType = MoveDestType::Invalid;
        }
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

QVector<tuple<QPoint, GameScene::ReachCharType> > GameScene::listReachableCharacterPos(
    const QPoint origin,
    const int max,
    const int min
)
{
    QVector<tuple<QPoint, ReachCharType> > rst;

    for(int i = origin.y()-max;i <= origin.y()+max;i++){
        if(i < 0 || i >= GameHeight) continue;
        for(int j = origin.x()-max;j <= origin.x()+max;j++){
            if(j < 0 || j >= GameWidth) continue;
            const int dis = qAbs(j - origin.x()) + qAbs(i - origin.y());
            const QPoint h{j, i};
            if(dis < min || dis > max) continue;

            auto type = ReachCharType::Invalid;

            GameCharacter* c = charAt(h);
            if(c != nullptr){
                type = ReachCharType::Valid;
            }else{
                type = ReachCharType::Invalid;
            }

            rst.append({{j, i}, type});
        }
    }

    return rst;
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

    auto list = listReachableCharacterPos(origin, max, min);
    for(int i = 0;i < list.size();i++){
        QPoint p; ReachCharType type;
        std::tie(p, type) = list[i];

        auto cellIdr = new CellIndicatorItem(p, mSltIndicate);
        if(type == ReachCharType::Invalid){
            cellIdr->setColor(lightColor);
        }else if(type == ReachCharType::Valid){
            cellIdr->setColor(targetColor);
            cellIdr->setHightLight(true);
            auto c = charAt(p);
            connect(cellIdr, &CellIndicatorItem::clicked, cellIdr, [this, c](CellIndicatorItem* src){
                emit charSelected(c);
                deleteItemGroup(mSltIndicate);
            }, Qt::SingleShotConnection);
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

    auto code = successOrFailed();
    if(code == 1){
        gameSuccess();
    }else if(code == 2){
        gameFailed();
    }

    // now is AI's turn.
    if(code == 0)
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
    auto code = successOrFailed();
    if(code == 1){
        gameSuccess();
    }else if(code == 2){
        gameFailed();
    }

    if(code == 0){
        mState = 0;
        hud->setAllowEndTurn(true);
        hud->setActBtnVisible(true);
    }
}

void GameScene::init()
{
    initLevel();
    initPropItems();
    initChars();
    initHUD();
    initAI();
    initChore();
}


void GameScene::initLevel()
{
    mLevel = new Level();
    mLevel->initLevel(GameWidth, GameHeight);
    //mLevel->setStonePath(QRect(1, 2, 5, 4));
    mLevel->setWallRect(QRect(0, 0, 16, 12));
    mLevel->setScene(this);
}

void GameScene::initPropItems()
{
//    auto chestProp = new GameProp(this, GameProp::PropType::Chest);
//    chestProp->setPos({3, 4});
//    addProp(chestProp);

//    auto magicProp = new GameProp(this, GameProp::PropType::Magic);
//    magicProp->setPos({1, 6});
//    addProp(magicProp);

//    auto stoneProp = new GameProp(this, GameProp::PropType::Stone);
//    stoneProp->setPos(8, 8);
//    addProp(stoneProp);

//    auto vase = new GameProp(this, GameProp::PropType::Vase);
//    vase->setPos(9, 8);
//    addProp(vase);
}

void GameScene::initChars()
{
//    auto ch = createPlayerChar<GameCharacter>();
//    addChar(ch);
//    ch->setPos({3, 3});

//    ch = createEnemyChar<BossMeow>();
//    ch->setPos({8, 3});
//    ch->setTowards(false);
//    addChar(ch);
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

void GameScene::initChore()
{
    // nothing here
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

void GameScene::txtBoxSeries(QVector<TextBoxItem *> arr)
{
    if(arr.empty()) return;
    arr[0]->setUseAnimation(true);
    connect(arr[0], &TextBoxItem::clicked, arr[0], &TextBoxItem::close);
    for(int i = 1;i < arr.size();i++){
        arr[i]->setUseAnimation(true);
        connect(arr[i], &TextBoxItem::clicked, arr[i], &TextBoxItem::close);
        connect(arr[i-1], &TextBoxItem::clicked, arr[i], &TextBoxItem::show);
    }
}

int GameScene::successOrFailed()
{
    bool hasPlayer = false;
    bool hasEnemy = false;
    auto chs = chars();
    for(int i = 0;i < chs.size();i++){
        auto c = chs[i];
        if(c->charRole() == GameCharacter::CharacterRole::Player1 && c->health() > 0){
            hasPlayer = true;
        }
        if(c->charRole() == GameCharacter::CharacterRole::Enemy && c->health() > 0){
            hasEnemy = true;
        }
        if(hasPlayer && hasEnemy) break;
    }
    if(!hasPlayer) return 2;
    if(!hasEnemy) return 1;
    return 0;
}

void GameScene::gameSuccess()
{
    TextBoxItem *box = new TextBoxItem();
    box->setFontPointSize(24);
    box->setSize(450, 300);
    box->setPos(200, 160);
    box->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\
    <html>\
    <head></head>\
    <body style=\" font-family:'Microsoft YaHei UI';\">\
    <p style=\"margin-left:100px; font-size: 50px\">~~胜利啦~~</p>\
    <p style=\"margin-left:10px; \">恭喜~恭喜~</p>\
    </body></html>");
    box->setVisible(false);
    box->setUseAnimation(true);
    addItem(box);

    box->show();
    connect(box, &TextBoxItem::clicked, this, [this](){
        auto view = this->views()[0];
        HelloScene *s = new HelloScene();
        s->init();
        view->setScene(s);
        this->deleteLater();
    });
}

void GameScene::gameFailed()
{
    TextBoxItem *box = new TextBoxItem();
    box->setFontPointSize(24);
    box->setSize(450, 300);
    box->setPos(200, 160);
    box->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\
    <html>\
    <head></head>\
    <body style=\" font-family:'Microsoft YaHei UI';\">\
    <p style=\"margin-left:100px; font-size: 50px\">惜败 QAQ</p>\
    <p style=\"margin-left:10px; \">再接再厉吧。</p>\
    </body></html>");
    box->setVisible(false);
    box->setUseAnimation(true);
    addItem(box);

    box->show();
    connect(box, &TextBoxItem::clicked, this, [this](){
        auto view = this->views()[0];
        HelloScene *s = new HelloScene();
        s->init();
        view->setScene(s);
        this->deleteLater();
    });
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
