#include "GameCharacter.h"
#include "item/PopupTextItem.h"
#include "R.h"
#include "GameCharAction.h"
#include "action/MoveAct.h"
#include <QtGlobal>
#include <QtCore>
#include <QtGui>
#include <QtConcurrent/QtConcurrent>

GameCharacter::GameCharacter(GameCharItem* item, GameScene* game, int role)
    : QObject(game)
{
    mRole = role;
    mGame = game;

    mCharItem = item;
    mCharItem->setScale(3.5);
    mCharItem->setFlag(QGraphicsItem::ItemIsSelectable);
    connect(mCharItem, &GameCharItem::selectedChange, this, &GameCharacter::selected);
    connect(mCharItem, &GameCharItem::clicked, this, &GameCharacter::click);

    initDefaultAction();
}

void GameCharacter::attacked(const qreal power)
{
    if(mHealth <= 0) return;

    bool canDodge = QRandomGenerator::global()->generate() % 100 < mLucky;
    if(canDodge){
        dodge();
        return;
    }

    const qreal hurt = qMax(power - mDefensivePower, (qreal)0);
    mHealth -= hurt;
    mCharItem->takeDamage(hurt);

    if(mHealth <= 0){
        QTimer::singleShot(500, this, &GameCharacter::die);
    }
}

void GameCharacter::healed(const qreal power)
{
    if(mHealth <= 0) return;
    mHealth += power;
    mCharItem->healed(power);
}

void GameCharacter::moveTo(const QPoint newPos)
{
    const QPoint dest = {newPos.x() * 64, newPos.y() * 64};
    mPos = newPos;
    mCharItem->moveTo(dest);
}

void GameCharacter::setPos(const QPoint newPos)
{
    const QPoint dest = {newPos.x() * 64, newPos.y() * 64};
    mCharItem->setTowards(newPos.x() > mPos.x());
    mPos = newPos;
    mCharItem->setPos(dest);
}

void GameCharacter::die()
{
    this->mCharItem->death();
}

void GameCharacter::dodge()
{
    mCharItem->dodge();
}

void GameCharacter::setTowards(bool towardRight)
{
    mCharItem->setTowards(towardRight);
}

QVector<QPixmap> GameCharacter::requestIcons()
{
    QVector<QPixmap> rtn;
    for(int i = 0;i < 5;i++){
        rtn.append(R::IconPixmap->copy(32*i, 0, 32, 32));
    }
    return rtn;
}

void GameCharacter::setCharRole(const int role)
{
    mRole = role;
}

void GameCharacter::selected(bool slt)
{

}

void GameCharacter::click(GameCharItem *src)
{
    Q_UNUSED(src);
    emit clicked(this);
}

qreal GameCharacter::health() const
{
    return mHealth;
}

qreal GameCharacter::speed() const
{
    return mSpeed;
}

qreal GameCharacter::defensivePower() const
{
    return mDefensivePower;
}

qreal GameCharacter::lucky() const
{
    return mLucky;
}

GameScene *GameCharacter::game() const
{
    return mGame;
}

void GameCharacter::initDefaultAction()
{
    mMoveAct = new MoveAct(this, this);
    mAttackAct = new GameCharAction(this, this);
    mAttackAct->setText("攻击");
}

QVector<GameCharAction *> GameCharacter::requestActionMenu()
{
    return {mMoveAct, mAttackAct};
}

const QString &GameCharacter::name() const
{
    return mName;
}

void GameCharacter::setName(const QString &newName)
{
    mName = newName;
}

GameCharItem *GameCharacter::charItem() const
{
    return mCharItem;
}
