#include "GameCharacter.h"
#include "item/PopupTextItem.h"
#include <QtGlobal>
#include <QtCore>
#include <QtGui>

GameCharacter::GameCharacter(GameCharItem* item, QObject *parent) : QObject(parent)
{
    mCharItem = item;
    mCharItem->setFlag(QGraphicsItem::ItemIsSelectable);
    connect(mCharItem, &GameCharItem::selectedChange, this, &GameCharacter::selected);
}

void GameCharacter::attacked(const qreal power)
{
    bool canDodge = QRandomGenerator::global()->generate() % 100 < mLucky;
    if(canDodge){
        dodge();
        return;
    }

    const qreal hurt = qMax(power - mDefensivePower, (qreal)0);
    mHealth -= hurt;
    mCharItem->takeDamage(hurt);
}

void GameCharacter::healed(const qreal power)
{

}

void GameCharacter::moveTo(const QPoint pos)
{

}

void GameCharacter::setPos(QRect pos)
{

}

void GameCharacter::die()
{

}

void GameCharacter::dodge()
{
    mCharItem->dodge();
}

void GameCharacter::selected(bool slt)
{
    attacked(20);
}

QVector<CharAction *> GameCharacter::requestActionMenu()
{
    return {};
}

CharAction::CharAction(QObject *parent) : QObject(parent)
{

}
