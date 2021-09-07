#include "GameScene.h"
#include "GameProp.h"
#include "GameCharacter.h"
#include "item/MeowKnightItem.h"
#include "HUD.h"
#include "R.h"
#include <QAction>

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
    connect(ch, &GameCharacter::clicked, this, &GameScene::charClicked);

    addItem(ch->charItem());
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
        hud->setStatusAttack("-/-");
        hud->setStatusLucky(src->lucky());

        if(src->charRole() == GameCharacter::CharacterRole::Player1){
            hud->setActBtns(src->requestActionMenu());
        }
    }
}

void GameScene::init()
{
    initLevel();
    initPropItems();
    initChars();
    initHUD();
}


void GameScene::initLevel()
{
    mLevel = new Level();
    mLevel->initLevel(16, 12);
    mLevel->setStonePath(QRect(1, 2, 5, 4));
    mLevel->setWallRect(QRect(0, 0, 16, 12));
    mLevel->setScene(this);
}

void GameScene::initPropItems()
{
    auto chestItem = new PropItem(PropItem::PropType::Chest);
    auto chestProp = new GameProp(chestItem, this, GameProp::PropType::Chest);
    chestProp->setPos({3, 4});
    addProp(chestProp);

    auto magicItem = new PropItem(PropItem::PropType::Magic);
    auto magicProp = new GameProp(magicItem, this, GameProp::PropType::Magic);
    magicProp->setPos({1, 6});
    addProp(magicProp);
}

void GameScene::initChars()
{
    MeowKnightItem *meow = new MeowKnightItem("grey");
    GameCharacter *ch = new GameCharacter(meow, this, GameCharacter::CharacterRole::Player1);
    addChar(ch);
    ch->setName("喵");
    ch->setPos({8, 3});

    meow = new MeowKnightItem("grey");
    ch = new GameCharacter(meow, this, GameCharacter::CharacterRole::Player1);
    addChar(ch);
    ch->setName("喵~");
    ch->setPos({4, 3});
}

void GameScene::initHUD()
{
    hud = new HUD(this);

//    QVector<QPixmap> iconPixs;
//    for(int i = 0;i < 5;i++){
//        iconPixs.append(R::IconPixmap->copy(i*32, 0, 32, 32));
//    }
//    hud->setIcons(iconPixs);

//    QVector<QAction*> actions;
//    for(int i = 0;i < 4;i++){
//        QAction *act = new QAction();
//        act->setText(QString::number(i));
//        QObject::connect(act, &QAction::triggered, [i](bool t){
//            qDebug() << i;
//        });
//        actions.append(act);
//    }
//    hud->setActBtns(actions);
}

void GameScene::charClicked(GameCharacter *src)
{
    charClickedEvent(src);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_H){
        hud->toggleHUD();
    }
    QGraphicsScene::keyPressEvent(event);
}


