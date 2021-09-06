#include "GameCharacter.h"

GameCharacter::GameCharacter(GameCharItem* item, QObject *parent) : QObject(parent)
{
    mCharItem = item;
    mCharItem->setFlag(QGraphicsItem::ItemIsSelectable);
    connect(mCharItem, &GameCharItem::selectedChange, this, &GameCharacter::selected);
}

void GameCharacter::attacked(const qreal power)
{

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

void GameCharacter::selected(bool slt)
{

}

QVector<CharAction *> GameCharacter::requestActionMenu()
{
    return {};
}

CharAction::CharAction(QObject *parent) : QObject(parent)
{

}
